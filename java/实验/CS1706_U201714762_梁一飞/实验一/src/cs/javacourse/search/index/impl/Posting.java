package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractPosting;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.List;

public class Posting extends AbstractPosting {
    /**
     * 缺省构造函数
     */
    public Posting() {
    }

    /**
     * 构造函数
     *
     * @param docId     ：包含单词的文档id
     * @param freq      ：单词在文档里出现的次数
     * @param positions ：单词在文档里出现的位置
     */
    public Posting(int docId, int freq, List<Integer> positions) {
        super(docId, freq, positions);
    }

    /**
     * 判断二个Posting内容是否相同
     *
     * @param obj ：要比较的另外一个Posting
     * @return 如果内容相等返回true，否则返回false
     */
    @Override
    public boolean equals(Object obj) {
        if(!(obj instanceof Posting)) return false;
        Posting newobj=(Posting) obj;
        this.sort();
        newobj.sort();
        boolean res=false;
        if(this.positions==null&&newobj.positions==null){
            res=this.docId==newobj.docId&&this.freq==newobj.freq;
        }
        else if(this.positions!=null&&newobj.positions!=null){
            res=this.docId==newobj.docId
                    &&this.freq==newobj.freq
                    &&this.positions.equals(newobj.positions);

        }
        return res;
    }

    @Override
    public String toString() {
        return "Posting{" +
                "docId=" + docId +
                ", freq=" + freq +
                ", positions=" + positions +
                '}';
    }

    /**
     * 返回包含单词的文档id
     *
     * @return ：文档id
     */
    @Override
    public int getDocId() {
        return this.docId;
    }

    /**
     * 设置包含单词的文档id
     *
     * @param docId ：包含单词的文档id
     */
    @Override
    public void setDocId(int docId) {
        this.docId=docId;
    }

    /**
     * 返回单词在文档里出现的次数
     *
     * @return ：出现次数
     */
    @Override
    public int getFreq() {
        return this.freq;
    }

    /**
     * 设置单词在文档里出现的次数
     *
     * @param freq :单词在文档里出现的次数
     */
    @Override
    public void setFreq(int freq) {
        this.freq=freq;
    }

    /**
     * 返回单词在文档里出现的位置列表
     *
     * @return ：位置列表
     */
    @Override
    public List<Integer> getPositions() {
        return this.positions;
    }

    /**
     * 设置单词在文档里出现的位置列表
     *
     * @param positions ：单词在文档里出现的位置列表
     */
    @Override
    public void setPositions(List<Integer> positions) {
        this.positions=positions;
    }

    /**
     * 比较二个Posting对象的大小（根据docId）
     *
     * @param o ： 另一个Posting对象
     * @return ：二个Posting对象的docId的差值
     */
    @Override
    public int compareTo(AbstractPosting o) {
        return this.docId-((Posting)o).getDocId();
    }

    /**
     * 对内部positions从小到大排序
     */
    @Override
    public void sort() {
        this.positions.sort(Integer::compareTo);
    }

    /**
     * 写到二进制文件
     *
     * @param out :输出流对象
     */
    @Override
    public void writeObject(ObjectOutputStream out) {
        try {
            out.writeObject(this.positions);
            out.writeObject(this.docId);
            out.writeObject(this.freq);
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
        try {

            this.positions=(ArrayList<Integer>)in.readObject();
            this.docId=(int)in.readObject();
            this.freq=(int)in.readObject();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
