package dao;

import entity.Order;
import util.DBUtil;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class OrderDao {
    public List<Order> findAll(String cnum){
        List<Order> list = new ArrayList<>();
        Connection connection = DBUtil.getConnection();
        String sql = "select * from `order` where cnum = ?";
        PreparedStatement ps = null;
        try {
            ps = connection.prepareStatement(sql);
            ps.setString(1,cnum);
            ResultSet rs = ps.executeQuery();
            while(rs.next()){
                Order order = new Order();
                order.setAllprice(rs.getDouble("allprice"));
                order.setCnum(rs.getString("cnum"));
                order.setMnum(rs.getString("mnum"));
                order.setOnum(rs.getString("onum"));
                order.setTotalprice(rs.getDouble("totalprice"));
                order.setOdate(rs.getDate("odate"));
                list.add(order);
            }
            return list;
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            DBUtil.close(connection);
        }
        return list;
    }
    public int insert(Order order){
        Connection connection = DBUtil.getConnection();
        String sql = "INSERT INTO `order`(onum, mnum, cnum, allprice, totalprice, odate) " +
                "VALUES(?,?,?,?,?,?) ";
        PreparedStatement ps = null;
        try {
            ps = connection.prepareStatement(sql);
            ps.setString(1,order.getOnum());
            ps.setString(2,order.getMnum());
            ps.setString(3,order.getCnum());
            ps.setDouble(4,order.getAllprice());
            ps.setDouble(5,order.getTotalprice());
            ps.setDate(6,new Date(order.getOdate().getTime()));
            int i = ps.executeUpdate();
            return i;
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            DBUtil.close(connection);
        }
        return 0;
    }
}
