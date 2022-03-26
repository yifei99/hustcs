package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.index.impl.TermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleScanner;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StringSplitter;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class TermTupleScanner extends AbstractTermTupleScanner {
    List<String> stringList=new ArrayList<>();
    int curpos=0;

    /**
     * 缺省构造函数
     */
    public TermTupleScanner() {
    }

    /**
     * 构造函数
     *
     * @param input ：指定输入流对象，应该关联到一个文本文件
     */
    public TermTupleScanner(BufferedReader input) {
        super(input);
    }

    /**
     * 获得下一个三元组
     *
     * @return: 下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() {
        StringSplitter stringSplitter=new StringSplitter();
        stringSplitter.setSplitRegex(Config.STRING_SPLITTER_REGEX);
        while(stringList.size()==0){
            try {
                String string=this.input.readLine();
                if(string!=null){
                    if(string!="")
                        stringList.addAll(stringSplitter.splitByRegex(string));
                }
                else {
                    return null;
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        String string=this.stringList.get(0);
        AbstractTerm term;
        if(Config.IGNORE_CASE){
            term=new Term(string.toLowerCase());
        }
        else{
            term=new Term(string);
        }

        stringList.remove(0);
        AbstractTermTuple termTuple=new TermTuple(term,curpos++);
        return termTuple;

    }

}
