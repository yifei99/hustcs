package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractIndex;
import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractPostingList;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.impl.Index;
import hust.cs.javacourse.search.index.impl.PostingList;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.Sort;

import java.io.File;
import java.lang.reflect.Array;
import java.util.*;

import static hust.cs.javacourse.search.query.AbstractIndexSearcher.LogicalCombination.*;

public class IndexSearcher extends AbstractIndexSearcher {
    public IndexSearcher() {
    }

    /**
     * 从指定索引文件打开索引，加载到index对象里. 一定要先打开索引，才能执行search方法
     *
     * @param indexFile ：指定索引文件
     */
    @Override
    public void open(String indexFile) {

        index.load(new File(indexFile));
    }

    /**
     * 根据单个检索词进行搜索
     *
     * @param queryTerm ：检索词
     * @param sorter    ：排序器
     * @return ：命中结果数组
     */
    @Override
    public AbstractHit[] search(AbstractTerm queryTerm, Sort sorter) {
        AbstractPostingList postingList= this.index.search(queryTerm);//postinglist
        AbstractPosting posting;
        AbstractHit[] hit=new  Hit[postingList.size()];
        for(int i=0;i<postingList.size();i++){
            posting=postingList.get(i);
            Map<AbstractTerm,AbstractPosting> map=  new TreeMap<>();
            map.put(queryTerm,posting);
            hit[i]=new Hit(
                    posting.getDocId(),
                    index.getDocName(posting.getDocId()),
                    map
            );
        }
        sorter.sort(Arrays.asList(hit));
        return hit;
    }

    /**
     * 根据二个检索词进行搜索
     *
     * @param queryTerm1 ：第1个检索词
     * @param queryTerm2 ：第2个检索词
     * @param sorter     ：    排序器
     * @param combine    ：   多个检索词的逻辑组合方式
     * @return ：命中结果数组
     */
    @Override
    public AbstractHit[] search(AbstractTerm queryTerm1,
                                AbstractTerm queryTerm2,
                                Sort sorter,
                                LogicalCombination combine) {
        AbstractHit[] hit1= this.search(queryTerm1,sorter);
        AbstractHit hit2[]= this.search(queryTerm2,sorter);
        List<AbstractHit> res=new ArrayList<>();
        if(combine==AND){
            for(int i=0;i<hit1.length;i++){
                for(int j=0;j<hit2.length;j++){
                    if (hit2[j].getDocId()==hit1[i].getDocId() ){
                        hit1[i].getTermPostingMapping().putAll(
                                hit2[j].getTermPostingMapping());
                        res.add(hit1[i]);

                    }
                }

            }
        }
        else    if(combine==OR){
            res.addAll(List.of(hit1));
            for(int i=0;i<hit2.length;i++){
                for(int j=0;j<hit2.length;j++){
                    if (hit2[j].getDocId()==hit1[i].getDocId() ){
                        hit1[i].getTermPostingMapping().putAll(
                                hit2[j].getTermPostingMapping());
                        res.add(hit1[i]);

                    }
                    else {
                        res.add(hit2[j]);
                    }
                }
            }
        }
        return  res.toArray(AbstractHit[]::new);
    }
}
