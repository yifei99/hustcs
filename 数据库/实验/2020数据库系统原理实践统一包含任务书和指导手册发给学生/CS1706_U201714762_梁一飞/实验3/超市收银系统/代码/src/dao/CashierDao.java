package dao;

import entity.Cashier;
import util.DBUtil;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class CashierDao {
    public Cashier login(String username,String password){
        Connection connection = DBUtil.getConnection();
        String sql = "select * from cashier where cuser=? and cpassword = ?";
        PreparedStatement ps = null;
        try {
            ps = connection.prepareStatement(sql);
            ps.setString(1, username);
            ps.setString(2, password);
            ResultSet rs = ps.executeQuery();
            while(rs.next()){
                Cashier c = new Cashier();
                c.setCnum(rs.getString("cnum"));
                c.setCname(rs.getString("cname"));
                return c;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            DBUtil.close(connection);
        }
        return null;
    }
}
