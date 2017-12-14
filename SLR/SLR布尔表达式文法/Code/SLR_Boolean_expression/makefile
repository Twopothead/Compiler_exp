EXE=pl0parser
ok:
	@echo "SLR_boolean_expression_parser 待分析语句如下:\n"
	@cat test.pl0
	@echo "\n以上为待分析语句\n"
	flex pl0lex.cpp
	g++ -o mypl0lex lex.yy.c -ll
	@echo "\n我的词法分析器正在分析程序test.pl0...\n"
	./mypl0lex < test.pl0
