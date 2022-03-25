package util;

import entity.Detail;
import entity.Goods;

import java.util.ArrayList;
import java.util.List;

public class OrderUtil {
    public static List<Detail> detailsList = new ArrayList<>();
    public static List<Goods> goodsList = new ArrayList<>();
    public static List<Detail> getGoodsList(){
        return detailsList;
    }
    public static void addGoods(Goods g,int count){
        Detail d = new Detail();
        d.setGnum(g.getGnum());
        d.setQuantity(count);
        goodsList.add(g);
        detailsList.add(d);
    }
    public static void clear(){
        goodsList.clear();
        detailsList.clear();
    }
}
