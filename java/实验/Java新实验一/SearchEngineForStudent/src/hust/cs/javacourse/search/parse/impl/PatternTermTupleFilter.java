package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;

public class PatternTermTupleFilter extends AbstractTermTupleFilter {
    public PatternTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
    }

    /**
     * 获得下一个三元组
     *
     * @return: 下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() {
        AbstractTermTuple termTuple=input.next();
        if(termTuple==null) return  null;
        boolean num=false;
        for(int i=0;i<termTuple.term.getContent().length();i++){
            if(termTuple.term.getContent().charAt(i)<='9'
                    &&termTuple.term.getContent().charAt(i)>='0'){
                num=true;
                break;
            }
        }
        if(num==true
        ){

            return this.next();
        }

        else {
            return  termTuple;
        }
    }
}
