package dao;

import entity.Goods;
import util.DBUtil;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class GoodsDao {
    public List<Goods> findAll(){
        List<Goods> list = new ArrayList<>();
        Connection connection = DBUtil.getConnection();
        String sql = "select * from goods";
        PreparedStatement ps = null;
        try {
            ps = connection.prepareStatement(sql);

            ResultSet rs = ps.executeQuery();
            while(rs.next()){
                Goods goods = new Goods();
                goods.setGname(rs.getString("gname"));
                goods.setGnum(rs.getString("gnum"));
                goods.setGpoint(rs.getInt("gpoint"));
                goods.setGprice(rs.getDouble("gprice"));
                list.add(goods);
            }
            return list;
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            DBUtil.close(connection);
        }
        return list;
    }
}
