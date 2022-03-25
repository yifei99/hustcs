asmlinkage int sys_mysyscall(char* sourceFile,char* destinationFile){
     int source=sys_open(sourceFile,O_RDONLY,0);
     int destination=sys_open(destinationFile,O_WRONLY|O_CREAT|O_TRUNC,0600);
     char buff[4096];
     mm_segment_t fs;
     fs = get_fs();
     set_fs(get_ds());
     int i;
     if(source>0 && destination>0){
         do{
             i=sys_read(source,buf,4096);
             sys_write(destination,buf,i);
         }while(i);
     }
     sys_close(source);
     sys_close(destination);
     set_fs(fs);
     return 10;
     }
