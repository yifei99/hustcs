package entity;


import java.util.Date;

public class Member {

  private String mnum;
  private String mname;
  private String msex;
  private long mpoint;
  private Date mdate;


  public String getMnum() {
    return mnum;
  }

  public void setMnum(String mnum) {
    this.mnum = mnum;
  }


  public String getMname() {
    return mname;
  }

  public void setMname(String mname) {
    this.mname = mname;
  }


  public String getMsex() {
    return msex;
  }

  public void setMsex(String msex) {
    this.msex = msex;
  }


  public long getMpoint() {
    return mpoint;
  }

  public void setMpoint(long mpoint) {
    this.mpoint = mpoint;
  }


  public Date getMdate() {
    return mdate;
  }

  public void setMdate(Date mdate) {
    this.mdate = mdate;
  }

}
