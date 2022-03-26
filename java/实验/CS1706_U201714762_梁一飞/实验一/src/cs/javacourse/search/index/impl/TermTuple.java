package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.AbstractTermTuple;

public class TermTuple extends AbstractTermTuple {
    public TermTuple(AbstractTerm term,int curpos) {
        this.term=term;
        this.curPos=curpos;

    }

    public TermTuple() {
    }

    /**
     * 判断二个三元组内容是否相同
     *
     * @param obj ：要比较的另外一个三元组
     * @return 如果内容相等（三个属性内容都相等）返回true，否则返回false
     */
    @Override
    public boolean equals(Object obj) {
        if(!(obj instanceof TermTuple)) return  false;
        TermTuple newobj=(TermTuple) obj;
        return this.curPos==newobj.curPos
                &&this.freq==newobj.freq
                &&this.term.equals(newobj.term);
    }

    @Override
    public String toString() {
        return "TermTuple{" +
                "term=" + term +
                ", freq=" + freq +
                ", curPos=" + curPos +
                '}';
    }
}
