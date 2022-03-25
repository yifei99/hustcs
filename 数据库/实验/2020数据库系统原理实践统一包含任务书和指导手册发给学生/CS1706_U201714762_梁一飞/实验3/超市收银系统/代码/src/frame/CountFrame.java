package frame;

import entity.Cashier;
import entity.Goods;
import util.OrderUtil;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CountFrame extends JFrame{
    private Goods g;
    private JLabel count;
    private JTextField countT;
    private JButton q;
    public CountFrame(Goods g, Cashier c){
        this.g = g;
        count = new JLabel("购买数量");
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
                    JOptionPane.showMessageDialog(CountFrame.this, "数量不正确", "失败",
                            JOptionPane.ERROR_MESSAGE);
                }else{
                    try{
                        int count = Integer.valueOf(counts);
                        OrderUtil.addGoods(g,count);
                        new ShouyinFrame(c);
                        dispose();
                    }catch (Exception ex){
                        JOptionPane.showMessageDialog(CountFrame.this, "数量不正确", "失败",
                                JOptionPane.ERROR_MESSAGE);
                    }

                }
            }
        });
    }

    public static void main(String[] args) {
        new CountFrame(null,null);
    }
}
