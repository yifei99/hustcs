package frame;

import dao.GoodsDao;
import entity.Cashier;
import entity.Goods;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class ProductFrame extends JFrame{
    public ProductFrame(Cashier c) {
        GoodsDao dao = new GoodsDao();
        List<Goods> list = dao.findAll();
        Object[][] o = new Object[list.size()][4];
        System.out.println(list);
        for (int i = 0; i < o.length; i++) {
            o[i][0] = list.get(i).getGnum();
            o[i][1] = list.get(i).getGname();
            o[i][2] = list.get(i).getGprice();
            o[i][3] = list.get(i).getGpoint();
        }
        String[] cols = {"商品编号","商品名称","价格","积分"};
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
