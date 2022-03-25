package util;

import org.apache.commons.dbcp.BasicDataSource;

import java.io.IOException;
import java.sql.Connection;
import java.sql.SQLException;
import java.util.Properties;
import java.util.UUID;

public class DBUtil {
    public static String  getUUID(){
        String uuid = UUID.randomUUID().toString();
        //去掉“-”符号
        return uuid.replaceAll("-", "");
    }
    //初始化连接池
    private static BasicDataSource dbs;
    static{
        Properties p = new Properties();
        try {
            p.load(DBUtil.class.getClassLoader().getResourceAsStream("db.properties"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        String driver = p.getProperty("jdbc.driver");
        String url = p.getProperty("jdbc.url");
        String username = p.getProperty("jdbc.username");
        String password = p.getProperty("jdbc.password");
        //初始化连接池
        dbs = new BasicDataSource();
        dbs.setDriverClassName(driver);//设置驱动
        dbs.setUrl(url);//设置数据库信息
        dbs.setUsername(username);//设置用户名
        dbs.setPassword(password);//设置密码
        dbs.setInitialSize(3);//设置连接池里面正常维护的连接数量
        dbs.setMaxActive(5);//设置连接池最大连接数量
    }
    //获取连接
    public static Connection getConnection(){
        try {
            Connection connection = dbs.getConnection();
            return connection;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }
    //关闭连接
    public static void close(Connection connection){
        if(connection!=null){
            try {
                connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}
