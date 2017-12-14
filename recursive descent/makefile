EXE=pl0parser
ok:
	flex pl0lex.c
	gcc -o mypl0lex lex.yy.c -ll
	@echo "我的词法分析器正在分析程序test.pl0...\n"
	./mypl0lex < test.pl0
