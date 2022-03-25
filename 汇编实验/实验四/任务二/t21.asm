.386
stack segment use16 stack
         db 200 dup(0)
stack ends
code segment use16
         assume cs:code,ss:stack
old_int dw ?,?
new16h:cmp ah,0
             je quit
             cmp ah,10h
             je quit
             jmp dword ptr old_int
quit:pushf
       call dword ptr old_int
       mov ah,'A'
       cmp al,ah
       jl exit
       mov ah,'Z'
       cmp al,ah
       jg exit
       add al,32
exit:iret
       

start: xor ax,ax
         mov ds,ax
         mov ax,ds:[16h*4];
         mov old_int,ax
         mov ax,ds:[16h*4+2]
         mov old_int+2,ax
         ;保存旧中断

         cli

         mov word ptr ds:[16h*4],offset new16h
         ;新偏移地址
         mov ds:[16h*4+2],cs

         sti

         mov dx,offset start+15
         shr dx,4
         add dx,10h
         mov al,0;退出码为0
         mov ah,31h
         int 21h
code ends
         end start