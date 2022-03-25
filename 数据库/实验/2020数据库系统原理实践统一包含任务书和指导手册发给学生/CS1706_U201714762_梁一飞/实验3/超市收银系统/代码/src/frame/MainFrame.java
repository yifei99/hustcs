package frame;

import entity.Cashier;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainFrame extends JFrame{
    private Cashier c;
    private JButton order;
    private JButton shouyin;
    private JButton product;
    private JButton member;
    private JButton logOut;
    private JLabel ts;
    public MainFrame(Cashier cuser) {
        this.c = cuser;
        order = new JButton("订单信息");
        shouyin = new JButton("收银");
        product = new JButton("商品信息");
        member = new JButton("会员信息");
        logOut = new JButton("退出登录");
        ts = new JLabel("欢迎" + c.getCname() + "登陆收银系统");

        ts.setBounds(new Rectangle(10,10,200,40));
        shouyin.setBounds(new Rectangle(10,50,150,40));
        product.setBounds(new Rectangle(10,90,150,40));
        order.setBounds(new Rectangle(10,130,150,40));
        member.setBounds(new Rectangle(10,170,150,40));
        logOut.setBounds(new Rectangle(10,210,150,40));
        JPanel j = new JPanel();
        j.add(ts);
        j.add(shouyin);
        j.add(product);
        j.add(order);
        j.add(member);
        j.add(logOut);
        this.setLocationRelativeTo(null);//窗体居中显示
        j.setLayout(null);
        this.setSize(200,300);
        this.setContentPane(j);
        this.setVisible(true);
        shouyin.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new ShouyinFrame(c);
                dispose();
            }
        });
        order.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new OrderFrame(c);
                dispose();
            }
        });
        product.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new ProductFrame(c);
                dispose();
            }
        });
        member.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new MemberFrame(c);
                dispose();
            }
        });
        logOut.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new LoginMain();
                dispose();
            }
        });

    }

    public static void main(String[] args) {
        Cashier c = new Cashier();
        c.setCname("猪八戒");
        new MainFrame(c);
    }
}
