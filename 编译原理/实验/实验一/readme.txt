//在命令行输入以下命令

flex lex.l
bison -d -v parser.y
gcc display.c parser.tab.c lex.yy.c -lfl -o test
./test test.c