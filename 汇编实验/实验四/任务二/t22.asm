.386
stack segment use16 stack
         db 200 dup(0)
stack ends
code segment use16
         assume cs:code,ss:stack
start: push bx
         xor ax,ax
         mov ds,ax

         cli
         mov bx,11e0h
         mov ds:[16h*4],bx

         mov bx,0f000h
         mov ds:[16h*4+2],bx
         ;还原旧中断

         sti

         mov dx,offset start+15
         shr dx,4
         pop bx
         add dx,10h
         mov al,0;退出码为0
         mov ah,31h
         int 21h
code ends
         end start