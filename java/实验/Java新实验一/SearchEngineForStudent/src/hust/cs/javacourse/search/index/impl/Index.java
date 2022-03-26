package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.*;

import java.io.*;
import java.lang.management.PlatformLoggingMXBean;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

/**
 * AbstractIndex的具体实现类
 */
public class Index extends AbstractIndex {
    public Index() {

    }

    /**
     * 返回索引的字符串表示
     *
     * @return 索引的字符串表示
     */
    @Override
    public String toString() {
        StringBuffer stringBuffer=new StringBuffer();
        stringBuffer.append("Index{" + "docIdToDocPathMapping="+"{"+"\n");
        for(Map.Entry<Integer,String> stringSet:this.docIdToDocPathMapping.entrySet()){
            stringBuffer.append(stringSet.getKey()+"          ------>           ");
            stringBuffer.append(this.docIdToDocPathMapping.get(stringSet.getKey())+"\n");
        }
        stringBuffer.append("}"+", termToPostingListMapping="+"{\n");
        for(Map.Entry<AbstractTerm,AbstractPostingList> termPostingListEntry:this.termToPostingListMapping.entrySet()){
            stringBuffer.append(termPostingListEntry.getKey()+"         ------>         ");
            stringBuffer.append(this.termToPostingListMapping.get(termPostingListEntry.getKey())+"\n");
        }

        stringBuffer.append("}") ;
        return stringBuffer.toString();
    }

    /**
     * 添加文档到索引，更新索引内部的HashMap
     *
     * @param document ：文档的AbstractDocument子类型表示
     */
    @Override
    public void addDocument(AbstractDocument document) {
        this.docIdToDocPathMapping.put(document.getDocId(),document.getDocPath());
        Map<AbstractTerm,AbstractPosting> termPostingMap=new TreeMap<>();
        for(int i=0;i<document.getTupleSize();i++){
            AbstractTermTuple termTuple=document.getTuple(i)  ;
            if(termPostingMap.containsKey(termTuple.term)){
                AbstractPosting posting= termPostingMap.get(termTuple.term);
                posting.getPositions().add(termTuple.curPos);
                posting.setFreq(posting.getFreq()+termTuple.freq);
                posting.sort();
            }
            else {
                AbstractPosting posting=new Posting();
                posting.setFreq(termTuple.freq);
                posting.setDocId(document.getDocId());
                posting.getPositions().add(termTuple.curPos);
                termPostingMap.put(termTuple.term,posting);
            }
        }//建立了对应的posting
        //加入map中
        for(Map.Entry<AbstractTerm,AbstractPosting> entry:termPostingMap.entrySet()){
            if(this.termToPostingListMapping.containsKey(entry.getKey())){
                termToPostingListMapping.get(entry.getKey()).add(entry.getValue());
            }else
            {
                PostingList postingList=new PostingList();
                postingList.add(entry.getValue());
                termToPostingListMapping.put(entry.getKey(),postingList);
            }
        }
    }

    /**
     * <pre>
     * 从索引文件里加载已经构建好的索引.内部调用FileSerializable接口方法readObject即可
     * @param file ：索引文件
     * </pre>
     */
    @Override
    public void load(File file) {
        //文件=》readobject；
        try {
            ObjectInputStream input=new ObjectInputStream(new FileInputStream(file));
            try {
                this.termToPostingListMapping=(Map<AbstractTerm,AbstractPostingList>)input.readObject();
                this.docIdToDocPathMapping=(Map<Integer, String>)input.readObject();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * <pre>
     * 将在内存里构建好的索引写入到文件. 内部调用FileSerializable接口方法writeObject即可
     * @param file ：写入的目标索引文件
     * </pre>
     */
    @Override
    public void save(File file) {
        try {
            ObjectOutputStream output=new ObjectOutputStream(new FileOutputStream(file));
            output.writeObject(this.termToPostingListMapping);
            output.writeObject(this.docIdToDocPathMapping);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    /**
     * 返回指定单词的PostingList
     *
     * @param term : 指定的单词
     * @return ：指定单词的PostingList;如果索引字典没有该单词，则返回null
     */
    @Override
    public AbstractPostingList search(AbstractTerm term) {
        return this.termToPostingListMapping.get(term);
    }

    /**
     * 返回索引的字典.字典为索引里所有单词的并集
     *
     * @return ：索引中Term列表
     */
    @Override
    public Set<AbstractTerm> getDictionary() {
        return this.termToPostingListMapping.keySet();
    }

    /**
     * <pre>
     * 对索引进行优化，包括：
     *      对索引里每个单词的PostingList按docId从小到大排序
     *      同时对每个Posting里的positions从小到大排序
     * 在内存中把索引构建完后执行该方法
     * </pre>
     */
    @Override
    public void optimize() {
        Iterator<Map.Entry<AbstractTerm,AbstractPostingList>> it
                =this.termToPostingListMapping.entrySet().iterator();
        while (it.hasNext()){
            AbstractPostingList postinglist=it.next().getValue();
            postinglist.sort();
            for(int i=0;i<postinglist.size();i++){
                AbstractPosting posting= postinglist.get(i);
                posting.sort();
            }
        }

    }

    /**
     * 根据docId获得对应文档的完全路径名
     *
     * @param docId ：文档id
     * @return : 对应文档的完全路径名
     */
    @Override
    public String getDocName(int docId) {
        return this.docIdToDocPathMapping.get(docId);
    }

    /**
     * 写到二进制文件
     *
     * @param out :输出流对象
     */
    @Override
    public void writeObject(ObjectOutputStream out) {
        try {out.writeObject(this.docIdToDocPathMapping);
            out.writeObject(this.termToPostingListMapping);

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    /**
     * 从二进制文件读
     *
     * @param in ：输入流对象
     */
    @Override
    public void readObject(ObjectInputStream in) {
        try {this.docIdToDocPathMapping=(Map<Integer, String>)in.readObject();
            this.termToPostingListMapping=(Map<AbstractTerm,AbstractPostingList>)in.readObject();

        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
