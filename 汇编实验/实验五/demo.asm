.386
.model   flat,stdcall
option   casemap:none

WinMain  proto :DWORD,:DWORD,:DWORD,:DWORD
WndProc  proto :DWORD,:DWORD,:DWORD,:DWORD
Display  proto :DWORD

include      menuID.INC

include      windows.inc
include      user32.inc
include      kernel32.inc
include      gdi32.inc
include      shell32.inc

includelib   user32.lib
includelib   kernel32.lib
includelib   gdi32.lib
includelib   shell32.lib
good	     struct
	     myname   db  10 dup(0)
	     discount  db  0
	     buyingprice     dw  0
	     sellingprice  dw  0
	     total  dw  0
	     sale    dw  0
		 recommodation   dw 0
good      ends

.data
I  db 0
ClassName    db       'TryWinClass',0
AppName      db       'My First Window',0
MenuName     db       'MyMenu',0
DlgName	     db       'MyDialog',0
AboutMsg     db       'I am student LYF',0
hInstance    dd       0
CommandLine  dd       0
buf	     good  <>
	     good  <'PEN',10,35,56,70,25,?>
		 good  <'NOTE',9,12,30,25,5,?>
		 good  <'BOOK',8,15,20,30,2,?>
		 good  <'EARASER',9,2,3,80,60,?>
		 good  <'CARD',9,40,50,30,10,?>
	     good  3 dup(<>)
msg_myname     db       '商品名称',0
msg_discount  db       '折扣',0
msg_buyingprice     db       '进货价',0
msg_sellingprice  db       '销售价',0
msg_total  db       '进货总数',0
msg_sale    db       '已售数量',0
msg_recommodation    db       '推荐度',0
discount1 db 2,'10'
buyingprice1 db 2,'35'
sellingprice1 db 2,'56'
total db 2,'70'
sale1 db 2,'25'
discount2 db 1,'9'
buyingprice2 db 2,'12'
sellingprice2 db 2,'30'
tota2 db 2,'25'
sale2 db 1,'5'
discount3 db 1,'8'
buyingprice3 db 2,'15'
sellingprice3 db 2,'20'
tota3 db 2,'30'
sale3 db 1,'2'
discount4 db 1,'9'
buyingprice4 db 1,'2'
sellingprice4 db 1,'3'
tota4 db 2,'80'
sale4 db 2,'60'
discount5 db 1,'9'
buyingprice5 db 2,'40'
sellingprice5 db 2,'50'
tota5 db 2,'30'
sale5 db 2,'10'
re1 db 10 dup(' ')
re2 db 10 dup(' ')
re3 db 10 dup(' ')
re4 db 10 dup(' ')
re5 db 10 dup(' ')
menuItem     db       0  ;当前菜单状态, 1=处于list, 0=Clear
.stack
.code
Start:	     invoke GetModuleHandle,NULL
	     mov    hInstance,eax
	     invoke GetCommandLine
	     mov    CommandLine,eax
	     invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	     invoke ExitProcess,eax
	     ;;
WinMain      proc   hInst:DWORD,hPrevInst:DWORD,CmdLine:DWORD,CmdShow:DWORD
	     LOCAL  wc:WNDCLASSEX
	     LOCAL  msg:MSG
	     LOCAL  hWnd:HWND
             invoke RtlZeroMemory,addr wc,sizeof wc
	     mov    wc.cbSize,SIZEOF WNDCLASSEX
	     mov    wc.style, CS_HREDRAW or CS_VREDRAW
	     mov    wc.lpfnWndProc, offset WndProc
	     mov    wc.cbClsExtra,NULL
	     mov    wc.cbWndExtra,NULL
	     push   hInst
	     pop    wc.hInstance
	     mov    wc.hbrBackground,COLOR_WINDOW+1
	     mov    wc.lpszMenuName, offset MenuName
	     mov    wc.lpszClassName,offset ClassName
	     invoke LoadIcon,NULL,IDI_APPLICATION
	     mov    wc.hIcon,eax
	     mov    wc.hIconSm,0
	     invoke LoadCursor,NULL,IDC_ARROW
	     mov    wc.hCursor,eax
	     invoke RegisterClassEx, addr wc
	     INVOKE CreateWindowEx,NULL,addr ClassName,addr AppName,\
                    WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
                    CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,\
                    hInst,NULL
	     mov    hWnd,eax
	     INVOKE ShowWindow,hWnd,SW_SHOWNORMAL
	     INVOKE UpdateWindow,hWnd
	     ;;
MsgLoop:     INVOKE GetMessage,addr msg,NULL,0,0
             cmp    EAX,0
             je     ExitLoop
             INVOKE TranslateMessage,addr msg
             INVOKE DispatchMessage,addr msg
	     jmp    MsgLoop 
ExitLoop:    mov    eax,msg.wParam
	     ret
WinMain      endp

WndProc      proc   hWnd:DWORD,uMsg:DWORD,wParam:DWORD,lParam:DWORD
	     LOCAL  hdc:HDC
	     LOCAL  ps:PAINTSTRUCT
     .IF     uMsg == WM_DESTROY
	     invoke PostQuitMessage,NULL
     .ELSEIF uMsg == WM_KEYDOWN
	    .IF     wParam == VK_F1
             ;;your code
	    .ENDIF
     .ELSEIF uMsg == WM_COMMAND
	    .IF     wParam == IDM_FILE_EXIT
		    invoke SendMessage,hWnd,WM_CLOSE,0,0
		.ELSEIF wParam == ID_ACTION_RECOMMODATION
		   MOV ESI,OFFSET buf+21
		   call CACUL
		   MOV EDI,OFFSET buf+21
		   MOV ESI,OFFSET re1
		   call F2T10
	    .ELSEIF wParam == ID_ACTION_LIST
		    mov menuItem, 1
		    invoke InvalidateRect,hWnd,0,1  ;擦除整个客户区
		    invoke UpdateWindow, hWnd
	    .ELSEIF wParam == IDM_HELP_ABOUT
		    invoke MessageBox,hWnd,addr AboutMsg,addr AppName,0
	    .ENDIF
     .ELSEIF uMsg == WM_PAINT
             invoke BeginPaint,hWnd, addr ps
             mov hdc,eax
	     .IF menuItem == 1
		 invoke Display,hdc
	     .ENDIF
	     invoke EndPaint,hWnd,addr ps
     .ELSE
             invoke DefWindowProc,hWnd,uMsg,wParam,lParam
             ret
     .ENDIF
  	     xor    eax,eax
	     ret
WndProc      endp
CACUL  PROC
     PUSH AX
     PUSH BX
     PUSH CX
     PUSH DX
     ADD ESI,-21
     MOV I,5
LOPA5:ADD I,-1
    JS  CAUEND
    ADD ESI,21
    MOV AX,WORD PTR [ESI+11]
	ADD AX,10
    MOV BX,0080H
    MUL BX
    MOV BX,WORD PTR [ESI+13]
    DIV BX
    MOV BX,000AH
    MUL BX
    MOV BL,[ESI+10]
    MOV BH,00H
    DIV BX
    MOV CX,AX
    MOV AX,WORD PTR [ESI+17]
    MOV BX,0040H
    MUL BX
    MOV BX,WORD PTR [ESI+15]
    DIV BX
    ADD AX,CX 
	MOV [ESI+19],AX
	MOV AX,0
	MOV BX,0
	MOV CX,0
	JMP LOPA5
CAUEND: POP DX
        POP CX
		POP BX
		POP AX
		RET
CACUL	ENDP
RADIX_S PROC NEAR STDCALL USES EBX EDX ESI,LpResult,Radix:DWORD,NUM:DWORD
      LOCAL COUNT:WORD
	  MOV COUNT,0
	  MOV EAX,NUM
	  MOV ESI,LpResult
	  mov EBX,Radix
LOP1:MOV EDX,0
     DIV  EBX
	 PUSH DX
	 INC  COUNT
	 OR EAX,EAX
	 JNZ LOP1
LOP2:POP  AX
     CMP AL,10
	 JB L1
	 ADD AL,7
L1:  ADD AL,30H
    MOV [ESI],AL
	 INC ESI
	 DEC COUNT
	 JNZ LOP2
     MOV AX,SI
	 RET
RADIX_S ENDP
F2T10 PROC
PUSH EAX
PUSH EBX
SUB EDI,21
SUB ESI,10
MOV I,5
LOPA3:ADD I,-1
     JS FEND
	 ADD EDI,21
	  ADD ESI,10
	  MOV EAX,[EDI+19]
	  invoke RADIX_S,ESI,10,EAX
	  JMP LOPA3
FEND:
      POP EBX
      POP EAX
      RET
F2T10 ENDP
Display      proc   hdc:HDC
             XX     equ  10
             YY     equ  10
	     XX_GAP equ  100
	     YY_GAP equ  30
             invoke TextOut,hdc,XX+0*XX_GAP,YY+0*YY_GAP,offset msg_myname,8
             invoke TextOut,hdc,XX+1*XX_GAP,YY+0*YY_GAP,offset msg_discount,4
             invoke TextOut,hdc,XX+2*XX_GAP,YY+0*YY_GAP,offset msg_buyingprice,6
             invoke TextOut,hdc,XX+3*XX_GAP,YY+0*YY_GAP,offset msg_sellingprice,6
             invoke TextOut,hdc,XX+4*XX_GAP,YY+0*YY_GAP,offset msg_total,8
             invoke TextOut,hdc,XX+5*XX_GAP,YY+0*YY_GAP,offset msg_sale,8
			 invoke TextOut,hdc,XX+6*XX_GAP,YY+0*YY_GAP,offset msg_recommodation,6
             ;;
             invoke TextOut,hdc,XX+0*XX_GAP,YY+1*YY_GAP,offset buf[1*21].myname,3
             invoke TextOut,hdc,XX+1*XX_GAP,YY+1*YY_GAP,offset discount1+1,discount1
             invoke TextOut,hdc,XX+2*XX_GAP,YY+1*YY_GAP,offset buyingprice1+1,buyingprice1
             invoke TextOut,hdc,XX+3*XX_GAP,YY+1*YY_GAP,offset sellingprice1+1,sellingprice1
             invoke TextOut,hdc,XX+4*XX_GAP,YY+1*YY_GAP,offset total+1,total
			 invoke TextOut,hdc,XX+5*XX_GAP,YY+1*YY_GAP,offset sale1+1,sale1
             invoke TextOut,hdc,XX+6*XX_GAP,YY+1*YY_GAP,offset re1,3
			 invoke TextOut,hdc,XX+0*XX_GAP,YY+2*YY_GAP,offset buf[2*21].myname,4
             invoke TextOut,hdc,XX+1*XX_GAP,YY+2*YY_GAP,offset discount2+1,discount2
             invoke TextOut,hdc,XX+2*XX_GAP,YY+2*YY_GAP,offset buyingprice2+1,buyingprice2
             invoke TextOut,hdc,XX+3*XX_GAP,YY+2*YY_GAP,offset sellingprice2+1,sellingprice2
             invoke TextOut,hdc,XX+4*XX_GAP,YY+2*YY_GAP,offset tota2+1,tota2
			 invoke TextOut,hdc,XX+5*XX_GAP,YY+2*YY_GAP,offset sale2+1,sale2
             invoke TextOut,hdc,XX+6*XX_GAP,YY+2*YY_GAP,offset re2,3
			 invoke TextOut,hdc,XX+0*XX_GAP,YY+3*YY_GAP,offset buf[3*21].myname,4
             invoke TextOut,hdc,XX+1*XX_GAP,YY+3*YY_GAP,offset discount3+1,discount3
             invoke TextOut,hdc,XX+2*XX_GAP,YY+3*YY_GAP,offset buyingprice3+1,buyingprice3
             invoke TextOut,hdc,XX+3*XX_GAP,YY+3*YY_GAP,offset sellingprice3+1,sellingprice3
             invoke TextOut,hdc,XX+4*XX_GAP,YY+3*YY_GAP,offset tota3+1,tota3
			 invoke TextOut,hdc,XX+5*XX_GAP,YY+3*YY_GAP,offset sale3+1,sale3
             invoke TextOut,hdc,XX+6*XX_GAP,YY+3*YY_GAP,offset re3,3
			 invoke TextOut,hdc,XX+0*XX_GAP,YY+4*YY_GAP,offset buf[4*21].myname,7
             invoke TextOut,hdc,XX+1*XX_GAP,YY+4*YY_GAP,offset discount4+1,discount4
             invoke TextOut,hdc,XX+2*XX_GAP,YY+4*YY_GAP,offset buyingprice4+1,buyingprice4
             invoke TextOut,hdc,XX+3*XX_GAP,YY+4*YY_GAP,offset sellingprice4+1,sellingprice4
             invoke TextOut,hdc,XX+4*XX_GAP,YY+4*YY_GAP,offset tota4+1,tota4
			 invoke TextOut,hdc,XX+5*XX_GAP,YY+4*YY_GAP,offset sale4+1,sale4
             invoke TextOut,hdc,XX+6*XX_GAP,YY+4*YY_GAP,offset re4,3
			 invoke TextOut,hdc,XX+0*XX_GAP,YY+5*YY_GAP,offset buf[5*21].myname,4
             invoke TextOut,hdc,XX+1*XX_GAP,YY+5*YY_GAP,offset discount5+1,discount5
             invoke TextOut,hdc,XX+2*XX_GAP,YY+5*YY_GAP,offset buyingprice5+1,buyingprice5
             invoke TextOut,hdc,XX+3*XX_GAP,YY+5*YY_GAP,offset sellingprice5+1,sellingprice5
             invoke TextOut,hdc,XX+4*XX_GAP,YY+5*YY_GAP,offset tota5+1,tota5
			 invoke TextOut,hdc,XX+5*XX_GAP,YY+5*YY_GAP,offset sale5+1,sale5
             invoke TextOut,hdc,XX+6*XX_GAP,YY+5*YY_GAP,offset re5,3
             ret
Display      endp

             end  Start
