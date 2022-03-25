package entity;


import java.util.Date;

public class Order {

  private String onum;
  private String mnum;
  private String cnum;
  private double allprice;
  private double totalprice;
  private Date odate;


  public String getOnum() {
    return onum;
  }

  public void setOnum(String onum) {
    this.onum = onum;
  }


  public String getMnum() {
    return mnum;
  }

  public void setMnum(String mnum) {
    this.mnum = mnum;
  }


  public String getCnum() {
    return cnum;
  }

  public void setCnum(String cnum) {
    this.cnum = cnum;
  }


  public double getAllprice() {
    return allprice;
  }

  public void setAllprice(double allprice) {
    this.allprice = allprice;
  }


  public double getTotalprice() {
    return totalprice;
  }

  public void setTotalprice(double totalprice) {
    this.totalprice = totalprice;
  }


  public Date getOdate() {
    return odate;
  }

  public void setOdate(Date odate) {
    this.odate = odate;
  }

}
