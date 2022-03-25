编译命令
gcc -o parser ast.c parser.tab.c lex.yy.c semantic.c code.c semantic_case.c exp.c objectCode.c
运行命令
./parser test.c
