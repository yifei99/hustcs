package dao;

import entity.Detail;
import util.DBUtil;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class DetailDao {
    public int insert(Detail detail){
        Connection connection = DBUtil.getConnection();
        String sql = "insert into detail(onum,gnum,quantity) VALUES(?,?,?)";
        PreparedStatement ps = null;
        try {
            ps = connection.prepareStatement(sql);
            ps.setString(1, detail.getOnum());
            ps.setString(2, detail.getGnum());
            ps.setLong(3, detail.getQuantity());
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
