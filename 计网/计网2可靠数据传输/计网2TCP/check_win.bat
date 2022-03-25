@echo off
:: appname 程序名
:: inputname 输入文件名
:: outputname 输出文件名
:: resultname 程序控制台输出重定向文件名

set appname="C:\Users\dell\source\repos\计网2TCP\Debug\计网2.exe"
set inputname="C:\Users\dell\source\repos\计网2TCP\input.txt"
set outputname="C:\Users\dell\source\repos\计网2TCP\output.txt"
set resultname="C:\Users\dell\source\repos\计网2TCP\result.txt"

for /l %%i in (1,1,10) do (
    echo Test %appname% %%i:
    %appname% > %resultname% 2>&1
    fc /N %inputname% %outputname%
)
pause