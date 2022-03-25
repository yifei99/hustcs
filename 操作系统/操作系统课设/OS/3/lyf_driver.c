#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/uaccess.h>

#define DEVICE_NUM 0       
//打开，关闭，读，写
static int my_open(struct inode *inode, struct file *f);
static int my_release(struct inode *inode, struct file *f);
static ssize_t my_read(struct file *file, char __user *buf, size_t count, loff_t *f_pos);
static ssize_t my_write(struct file *file, const char __user *buf, size_t count, loff_t *f_pos);

static struct file_operations my_fops = {
    .read = my_read,
    .write = my_write,
    .open = my_open,
    .release = my_release,
};

static char buffer[1024] = "U201714762\n"; 
static int device_num = 0;             //用来保存设备号
static int device_open  = 0;                //打开设备的进程数，用于内核互斥


//打开设备
static int my_open(struct inode *inode, struct file *f){
    printk("<1>Main device number is %d \n ",MAJOR(inode->i_rdev));
    printk("<1>Slave device number is %d \n",MINOR(inode->i_rdev));
    printk("Now the device has opened!\n");
    //未被占用
    if(device_open == 0){
        device_open++;
        try_module_get(THIS_MODULE);
        return 0;
    }
    //被占用
    else{
        printk("Another process has opened the device.\n");
        return -1;
    }
}

//释放设备
static int my_release(struct inode *inode, struct file *f){
    device_open--;//解除占用
    printk("The device has beenreleased!\n");
    module_put(THIS_MODULE);
    return 0;
}

//读
static ssize_t my_read(struct file *file, char __user *buf, size_t count, loff_t *f_pos){
    if(copy_to_user(buf,buffer,sizeof(buffer))){
            return -1;
    }
    return sizeof(buffer);
}

//写
static ssize_t my_write(struct file *file, const char __user *buf, size_t count, loff_t *f_pos){
    if(copy_from_user(buffer,buf,sizeof(buffer))){
        return -1;
    }
    return sizeof(buffer);
}

static int __init my_init(void){
     int result;
   result=register_chrdev(DEVICE_NUM,"mydev",&my_fops);
   if(result<0){
       printk("error:can not register the device\n");
       return -1;
   }
   else{//注册成功
       device_num = result;
       printk("<1>hehe,the device has been registered!\n");
       printk("<1>the virtual device was assigned major number %d.\n",device_num);
       printk("<1>To talk to the driver,create a dev file with\n");
       printk("<1>'mknod/dev/my c %d 0'\n",device_num);
       printk("<1>Remove the dev and the file when done\n");
      return 0;
   }
}

static void __exit my_exit(void){
    printk("<1>unloading the device\n");
    unregister_chrdev(device_num,"mydev");
    printk("mydev:unregister success!\n");
}

  module_init(my_init);
  module_exit(my_exit);
  MODULE_LICENSE("GPL");