#命令行输入
chcp 65001
flex lex.l
bison -d -v parser.y
gcc display.c parser.tab.c lex.yy.c  semantic_analysis.c -lfl -o test
./test test3.c