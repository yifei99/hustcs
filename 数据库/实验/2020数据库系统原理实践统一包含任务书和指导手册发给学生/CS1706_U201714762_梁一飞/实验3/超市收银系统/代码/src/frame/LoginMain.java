package frame;

import dao.CashierDao;
import entity.Cashier;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginMain extends JFrame{
    private JLabel usernameL;
    private JLabel passwordL;
    private JTextField usernameT;
    private JPasswordField passwordT;
    private JButton loginB;
    private JButton cansle;
    public LoginMain(){
        usernameL = new JLabel("用户名");
        passwordL = new JLabel("密  码");
        usernameT = new JTextField();
        passwordT = new JPasswordField();
        loginB = new JButton("登陆");
        cansle = new JButton("退出");

        usernameL.setBounds(new Rectangle(10,10,40,40));
        usernameT.setBounds(new Rectangle(60,10,100,40));
        passwordL.setBounds(new Rectangle(10,60,40,40));
        passwordT.setBounds(new Rectangle(60,60,100,40));
        loginB.setBounds(new Rectangle(10,110,60,40));
        cansle.setBounds(new Rectangle(80,110,60,40));


        JPanel j = new JPanel();
        j.add(usernameL);
        j.add(passwordL);
        j.add(usernameT);
        j.add(passwordT);
        j.add(loginB);
        j.add(cansle);


        cansle.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });
        loginB.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameT.getText();
                String password = new String(passwordT.getPassword());
                if (username.equals("") || password.equals("")) {
                    JOptionPane.showMessageDialog(LoginMain.this, "用户名与密码无法登录", "登录失败",
                            JOptionPane.ERROR_MESSAGE);// 弹出“登录失败”对话框
                }else{
                    CashierDao cashierDao = new CashierDao();
                    Cashier cuser = cashierDao.login(username, password);
                    if(cuser!=null){
                        new MainFrame(cuser);
                        dispose();
                    }else{
                        JOptionPane.showMessageDialog(LoginMain.this, "用户名与密码无法登录", "登录失败",
                                JOptionPane.ERROR_MESSAGE);// 弹出“登录失败”对话框
                    }
                }
            }
        });

        this.setLocationRelativeTo(null);//窗体居中显示
        j.setLayout(null);
        this.setSize(200,200);
        this.setContentPane(j);
        this.setVisible(true);
    }
}
