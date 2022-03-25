package service;
import dao.DetailDao;
import dao.MemberDao;
import dao.OrderDao;
import entity.*;
import util.DBUtil;
import util.OrderUtil;

import java.util.Date;
import java.util.List;

public class OrderService {
    private OrderDao orderDao = new OrderDao();
    private MemberDao memberDao = new MemberDao();
    private DetailDao detailDao = new DetailDao();
    public int addOrder(Cashier c, Member m){
        List<Detail> list = OrderUtil.getGoodsList();
        Order o = new Order();
        o.setOnum(DBUtil.getUUID());
        o.setOdate(new Date());
        o.setCnum(c.getCnum());
        o.setMnum(m.getMnum());
        double allprice = 0;
        double totalprice = 0;
        for (Goods goods : OrderUtil.goodsList) {
            if(goods.getGname().equals("会员卡")){
                memberDao.update(m.getMnum(),950);
            }
            for (Detail detail : list) {
                detail.setOnum(o.getOnum());
                if(detail.getGnum().equals(goods.getGnum())){
                    allprice += goods.getGprice()*detail.getQuantity();
                    System.out.println("计算结果:"+allprice);
                }
            }
        }
        m = memberDao.findByNum(m.getMnum());
        if(m.getMpoint()+allprice>=1000){
            totalprice = allprice * 0.9;
            memberDao.update(m.getMnum(),(int)allprice);
        }else{
            totalprice = allprice;
        }
        o.setTotalprice(totalprice);
        o.setAllprice(allprice);
        orderDao.insert(o);
        for (Detail detail : list) {
            detailDao.insert(detail);
        }
        OrderUtil.clear();
        return 0;
    }
}
