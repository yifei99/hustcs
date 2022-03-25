package frame;

import dao.MemberDao;
import entity.Cashier;
import entity.Goods;
import entity.Member;
import service.OrderService;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MnameFrame extends JFrame {
    private Goods g;
    private JLabel count;
    private JTextField countT;
    private JButton q;
    public MnameFrame(Cashier c){
        count = new JLabel("输入会员编号");
        countT = new JTextField();
        q = new JButton("确定");

        count.setBounds(new Rectangle(10,10,100,40));
        countT.setBounds(new Rectangle(10,50,100,40));
        q.setBounds(new Rectangle(10,100,80,40));

        JPanel j = new JPanel();
        j.add(count);
        j.add(countT);
        j.add(q);
        this.setLocationRelativeTo(null);//窗体居中显示
        j.setLayout(null);
        this.setSize(150,200);
        this.setContentPane(j);
        this.setVisible(true);
        q.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String counts = countT.getText();
                if(counts==null||counts.equals("")){
                    JOptionPane.showMessageDialog(MnameFrame.this, "会员编号不正确", "失败",
                            JOptionPane.ERROR_MESSAGE);
                }else{
                    MemberDao memberDao = new MemberDao();
                    Member member = memberDao.findByNum(counts);
                    if(member==null){
                        JOptionPane.showMessageDialog(MnameFrame.this, "此会员不存在", "失败",
                                JOptionPane.ERROR_MESSAGE);
                    }else{
                        OrderService service = new OrderService();
                        service.addOrder(c,member);
                        new MainFrame(c);
                        dispose();
                    }

                }
            }
        });
    }

    public static void main(String[] args) {
        new MnameFrame(null);
    }
}
