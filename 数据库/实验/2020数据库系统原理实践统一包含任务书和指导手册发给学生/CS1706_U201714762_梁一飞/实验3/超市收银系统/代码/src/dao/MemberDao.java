package dao;

import entity.Member;
import util.DBUtil;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class MemberDao {
    public List<Member> findAll(){
        List<Member> list = new ArrayList<>();
        Connection connection = DBUtil.getConnection();
        String sql = "select * from member";
        PreparedStatement ps = null;
        try {
            ps = connection.prepareStatement(sql);

            ResultSet rs = ps.executeQuery();
            while(rs.next()){
                Member m = new Member();
                m.setMnum(rs.getString(1));
                m.setMname(rs.getString(2));
                m.setMsex(rs.getString(3));
                m.setMpoint(rs.getLong(4));
                m.setMdate(new Date(rs.getDate(5).getTime()));
                list.add(m);
            }
            return list;
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            DBUtil.close(connection);
        }
        return list;
    }

    public Member findByNum(String mnum){
        Connection connection = DBUtil.getConnection();
        String sql = "select * from member where mnum = ?";
        PreparedStatement ps = null;
        try {
            ps = connection.prepareStatement(sql);
            ps.setString(1,mnum);
            ResultSet rs = ps.executeQuery();
            while(rs.next()){
                Member m = new Member();
                m.setMnum(rs.getString(1));
                m.setMname(rs.getString(2));
                m.setMsex(rs.getString(3));
                m.setMpoint(rs.getLong(4));
                m.setMdate(new Date(rs.getDate(5).getTime()));
                return m;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            DBUtil.close(connection);
        }
        return null;
    }

    public int update(String mnum,int gpoint){
        Connection connection = DBUtil.getConnection();
        String sql = "update member set mpoint = mpoint + ? where mnum = ?";
        PreparedStatement ps = null;
        try {
            ps = connection.prepareStatement(sql);
            ps.setInt(1, gpoint);
            ps.setString(2,mnum);
            int i = ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            DBUtil.close(connection);
        }
        return 0;
    }

}
