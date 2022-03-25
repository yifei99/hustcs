package frame;

import dao.OrderDao;
import entity.Cashier;
import entity.Order;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class OrderFrame extends JFrame{
    public OrderFrame(Cashier c) {
        OrderDao dao = new OrderDao();
        List<Order> list = dao.findAll(c.getCnum());
        Object[][] o = new Object[list.size()][6];
        System.out.println(list);
        for (int i = 0; i < o.length; i++) {
            o[i][0] = list.get(i).getOnum();
            o[i][1] = list.get(i).getAllprice();
            o[i][2] = list.get(i).getTotalprice();
            o[i][3] = list.get(i).getCnum();
            o[i][4] = list.get(i).getMnum();
            o[i][5] = list.get(i).getOdate();
        }
        String[] cols = {"订单编号","订单价格","实收价格","收银员编号","顾客编号","订单时间"};
        JTable table = new JTable(o, cols);
        JScrollPane scrollPane = new JScrollPane(table);
        JMenuBar jm = new JMenuBar();
        JMenuItem add = new JMenuItem("返回主菜单");
        jm.add(add);
        add.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new MainFrame(c);
                dispose();
            }
        });
        this.setJMenuBar(jm);
        this.getContentPane().add(scrollPane);
        this.setVisible(true);
        this.setLocationRelativeTo(null);//窗体居中显示
        this.setSize(500,500);
    }
}
