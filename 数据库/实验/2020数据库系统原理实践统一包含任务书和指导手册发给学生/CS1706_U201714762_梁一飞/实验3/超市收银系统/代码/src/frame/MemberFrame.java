package frame;

import dao.MemberDao;
import entity.Cashier;
import entity.Member;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class MemberFrame extends JFrame{
    public MemberFrame(Cashier c) {
        MemberDao dao = new MemberDao();
        List<Member> list = dao.findAll();
        Object[][] o = new Object[list.size()][4];
        System.out.println(list);
        for (int i = 0; i < o.length; i++) {
            o[i][0] = list.get(i).getMnum();
            o[i][1] = list.get(i).getMname();
            o[i][2] = list.get(i).getMsex();
            o[i][3] = list.get(i).getMpoint();
        }
        String[] cols = {"编号","姓名","性别","积分"};
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
