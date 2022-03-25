package frame;

import dao.GoodsDao;
import entity.Cashier;
import entity.Goods;
import util.OrderUtil;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.JTableHeader;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

public class ShouyinFrame extends JFrame
{
    /**
     *
     */
    private static final long serialVersionUID = 1L;

    private JTable table;
    List<String[]> dataList;
    public static List<Goods> list;
    public static Cashier c;

    public ShouyinFrame(Cashier c)
    {
        this.c = c;
        this.setTitle("选择购买商品");
        this.setSize(1000, 600);
        Container container = getContentPane();
        container.setLayout(null);


        dataList = new ArrayList<String[]>();
        list = new GoodsDao().findAll();
        for (Goods g : list) {
            dataList.add(new String[]{g.getGname()+"",g.getGprice()+"",g.getGpoint()+"","购买"});
        }
        String[] cols = {"名称","价格","积分",""};
        table = new JTable();

        JScrollPane scrollPane = new JScrollPane();
        scrollPane.setBounds(0, 0, 1000, 600);
        scrollPane.setViewportView(table);

        JPanel panel = new JPanel();
        panel.setBounds(20, 20, 1000, 600);
        panel.setLayout(null);
        panel.add(scrollPane);

        JTableHeader head = this.table.getTableHeader();

        this.table.setModel(new DefaultTableModel()
        {
            /**
             *
             */
            private static final long serialVersionUID = 1L;

            @Override
            public Object getValueAt(int row, int column)
            {
                return dataList.get(row)[column];
            }

            @Override
            public int getRowCount()
            {
                return dataList.size();
            }

            @Override
            public int getColumnCount()
            {
                return dataList.get(0).length;
            }

            @Override
            public void setValueAt(Object aValue, int row, int column)
            {
                // 这里有时能触发，有时不能触发，情况未知
                //System.out.println(aValue + "  setValueAt");
            }

            @Override
            public boolean isCellEditable(int row, int column)
            {
                // 带有按钮列的功能这里必须要返回true不然按钮点击时不会触发编辑效果，也就不会触发事件。
                if (column == dataList.get(0).length-1 )
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        });
        DefaultTableModel model = (DefaultTableModel) table.getModel();
        model.setColumnIdentifiers(cols);
        table.getColumnModel().getColumn(dataList.get(0).length-1).setCellEditor(new MyButtonEditor(this));

        table.getColumnModel().getColumn(dataList.get(0).length-1).setCellRenderer(new MyButtonRender());

        table.setRowSelectionAllowed(false);// 禁止表格的选择功能。不然在点击按钮时表格的整行都会被选中。也可以通过其它方式来实现。

        container.add(panel);

        JMenuBar jm = new JMenuBar();
        JMenuItem add = new JMenuItem("返回主菜单");
        JMenuItem js = new JMenuItem("结算");
        jm.add(js);
        jm.add(add);
        add.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new MainFrame(c);
                dispose();
            }
        });
        js.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(OrderUtil.getGoodsList().size()<1){
                    JOptionPane.showMessageDialog(ShouyinFrame.this, "还没有购买商品呢", "失败",
                            JOptionPane.ERROR_MESSAGE);
                }else{
                    new MnameFrame(c);
                    dispose();
                }
            }
        });
        this.setJMenuBar(jm);
        this.setVisible(true);
        this.setLocationRelativeTo(null);//窗体居中显示
    }
}
