#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <gtk/gtk.h>

long long i=0,tt=0,tt0=0,idle=0,idle0=0;
gint Cpu(gpointer label){
FILE *fp;
 char ch[100],cpu[10]; 
 char string[1000];
 fp=fopen("/proc/stat","r"); 
 fgets(ch,sizeof(ch),fp); 
 fclose(fp);
 long user,nice,sys,idle,iowait,irq,softirq;
 float usage;
 sscanf(ch,"%s%ld%ld%ld%ld%ld%ld%ld",cpu,&user,&nice,&sys,&idle,&iowait,&irq,&softirq);
 tt=user+nice+sys+idle+iowait+irq+softirq;
 if(i>0)usage=(float)((tt-tt0)-(idle-idle0))*100/(tt-tt0);
 sprintf(string,"CPU利用率为%f%%",usage);
 idle0=idle;
 tt0=tt;
 i++;
gtk_label_set_text(label, string);
}
int main(int argc, char *argv[])
{
    //初始化GTK
    GtkWidget *window;
    GtkWidget *vbox;  
    GtkWidget *label;
    GtkWidget *text_label;
    // 初始化整个GTK
    gtk_init(&argc, &argv);
    // 生成窗口
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // 窗口属性
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "CPU利用率");
    gtk_container_set_border_width(GTK_CONTAINER(window), 20); //边界宽度
    g_signal_connect_swapped(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit), NULL);
    // 创建盒装容器并添加
    vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_border_width(GTK_CONTAINER(vbox), 150);
    gtk_widget_show(vbox);
    // 标签
    text_label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), text_label, FALSE, FALSE, 10);
    label = gtk_label_new("CPU利用率为");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 10);
    gtk_label_set_markup( GTK_LABEL(text_label), "<span font_desc='18'>CPU利用率</span>");
    gtk_widget_show(text_label);
    gtk_widget_show(label);
    // 显示窗口
    gtk_widget_show(window);
    // 延时1000ms 循环调用函数
    g_timeout_add(2000, Cpu, (gpointer)label);
    gtk_main();
}