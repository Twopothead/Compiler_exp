%{
#include <stdio.h>
#include <stdlib.h>
int num_lines = 0, num_chars = 0;
/*
typedef enum{
beginsym,callsym,constsym,dosym,endsym,ifsym,
oddsym,procsym,readsym,thensym,varsym,whilesym,
Writesym,plus,minus,times,slash,lparen,rparen,
eql,comma,period,neg,semicolon
}TerminalSet;
*/
/*终结符集合*/
/*
typedef enum{
block ,factor, expression,//分程序，因子，表达式
term,condition,//项，条件语句
}NonTerminalSet;
*/
/*非终结符集合*/
typedef enum{
	/*VN*/
	beginsym,callsym,constsym,dosym,endsym,ifsym,
	oddsym,procsym,readsym,thensym,varsym,whilesym,
	writesym,plus,minus,times,slash,lparen,rparen,
	eql,comma,period,neg,semicolon,
	/*VT*/
	ident,/*标识符*/
	number,/*数字*/
	block ,factor, expression,
	term,condition,
	relationop,/*关系运算符号*/
	become/*赋值符号 :=*/
}Token;
Token mytoken[1000];
Token CurrentToken;/*当前的那个Token*/
int total_token=0;
int i_Global=0;
%}
%%

begin		{	printf("%s:开始\n",yytext);mytoken[total_token]=beginsym;total_token++;/*beginsym*/}
call		{	printf("%s:调用\n",yytext);mytoken[total_token]=callsym;total_token++;/*callsym*/}
const		{	printf("%s:常量\n",yytext);mytoken[total_token]=constsym;total_token++;/*constsym*/}
do		{	printf("%s:做\n",yytext);mytoken[total_token]=dosym;total_token++;/*dosym*/}
end		{	printf("%s:结束\n",yytext);mytoken[total_token]=endsym;total_token++; /*endsym*/}
if		{	printf("%s:如果\n",yytext);mytoken[total_token]=ifsym;total_token++; /*ifsym*/}
odd		{	printf("%s:ODD\n",yytext);mytoken[total_token]=oddsym;total_token++; /*oddsym*/}
procedure	{	printf("%s:过程\n",yytext);mytoken[total_token]=procsym;total_token++; /*procsym*/}
read		{	printf("%s:读\n",yytext);mytoken[total_token]=readsym;total_token++; /*readsym*/}
then		{	printf("%s:然后\n",yytext);mytoken[total_token]=thensym;total_token++;/*thensym*/}
var		{	printf("%s:变量声明\n",yytext);mytoken[total_token]=varsym;total_token++;/*var*/}
while		{	printf("%s:当\n",yytext);mytoken[total_token]=whilesym;total_token++;/*whilesym*/}
write		{	printf("%s:写\n",yytext);mytoken[total_token]=writesym;total_token++;/*writesym*/}
[+]		{	printf("%s:加\n",yytext);mytoken[total_token]=plus;total_token++;/*plus*/}
[-]		{	printf("%s:减\n",yytext);mytoken[total_token]=minus;total_token++;/*minus*/}
[*]		{	printf("%s:乘\n",yytext);mytoken[total_token]=times;total_token++;/*times*/}
[/]		{	printf("%s:除\n",yytext);mytoken[total_token]=slash;total_token++;/*slash*/}
[(]		{	printf("%s:左括号\n",yytext);mytoken[total_token]=lparen;total_token++;/*lparen*/}
[)]		{	printf("%s:右括号\n",yytext);mytoken[total_token]=rparen;total_token++;/*rparen*/}
[=]		{	printf("%s:等于号\n",yytext);mytoken[total_token]=eql;total_token++;/*eql*/}
[,]		{	printf("%s:逗号\n",yytext);mytoken[total_token]=comma;total_token++;/*comma*/}
[.]		{	printf("%s:点！程序结束\n",yytext);mytoken[total_token]=period;total_token++;/*period*/}
[#]		{	printf("%s:井号\n",yytext);mytoken[total_token]=neg;total_token++;/*neg*/}
[;]		{	printf("%s:分号\n",yytext);mytoken[total_token]=semicolon;total_token++;/*semicolon*/}


[<>]|>=|<=|==	{ 	printf("%s:关系运算符\n",yytext);mytoken[total_token]=relationop;total_token++;/*relationop*/}
[*|/]		{ 	printf("%s:乘法运算符\n",yytext);}
[0-9][0-9]*|^-?\d+$  {	printf("%s:数字\n",yytext);mytoken[total_token]=number;total_token++;/*number*/}
:=  		{ 	printf("%s:赋值\n",yytext);mytoken[total_token]=relationop;total_token++;/*become*/
/*
[0-9][0-9]*	{ 	printf("%s:无符号整数\n",yytext);}
^-?\d+$		{ 	printf("%s:整数\n",yytext);}
*/
}
[A-Za-z]|[A-Za-z][A-Za-z0-9]* { printf("%s:标识符\n",yytext);mytoken[total_token]=ident;total_token++;/*ident*/}
\n		{ /*printf("%s:换行符\n",yytext);*/ ++num_lines; ++num_chars;}
[\t\r]		{ /*printf("%s:制表符\n",yytext);*//*过滤空白*/}
[ ]		{ /*printf("%s:空白\n",yytext);*/}
 .      	{ ++num_chars;}
%%
void showlineinfo();
void GetToken();
void readnext();
int ACC(Token token);
int Expect(Token token);
void Condition();
void Statement();
void Expression();
void Factor();
void Term();
void Block();
void PL0();
void showTokentype();

void showlineinfo()
{
	printf( "您的pl0代码有%d行, 有%d个标记符号\n",
	 num_lines, total_token );
}

void GetToken(){}
int i_current=0;
void readnext()
{
	CurrentToken=mytoken[i_current];
	if(i_current<500)i_current++;
	if(i_current==500){
		printf("您的代码太长了");
		exit(1);
	}
}

int ACC(Token token)
{
	if(CurrentToken==token){
		readnext();
		return 1;/*pass*/
	}
	return 0;/*不接受*/
}

/*ACC函数用来判断是否接受，Expect还要打印出错信息*/
int Expect(Token token)
{
	if(ACC(token)){
		return 1;
		/*ERRORMSG*/
		//printf("不是该有的符号");
	}
	return 0;
}

void Condition()
{/*根据课本P14 条件语法描述图*/
/*
 *condition = "odd" expression |
 *	            expression ("="|"#"|"<"|"<="|">"|">=")
 *其中("="|"#"|"<"|"<="|">"|">=")属于关系运算符号
 */
	if(ACC(oddsym)){
		Expression();
	}
	else{
		Expression();
		if(CurrentToken==relationop||CurrentToken==neg){//("="|"#"|"<"|"<="|">"|">=")
		readnext();
		Expression();
		}
		else{
			printf("条件语句的运算符出错！ ");exit(1);
			readnext();
		}
	}
}//~

void Statement()
{/*根据课本P14 语句语法描述图*/
/*
<语句> ::=<赋值语句>|<条件语句>|<当循环语句>|<过程调用语句>
                |<复合语句>|<读语句><写语句>|<空>
<赋值语句> ::=<标识符>:=<表达式>
<复合语句> ::=BEGIN <语句> {;<语句> }END
<条件语句> ::= <表达式> <关系运算符> <表达式> |ODD<表达式>
<条件语句> ::= IF <条件> THEN <语句>
<过程调用语句> ::= CALL 标识符
<当循环语句> ::= WHILE <条件> DO <语句>
<读语句> ::= READ‘(’<标识符>{,<标识符>}‘)’
<写语句> ::= WRITE‘(’<表达式>{,<表达式>}‘)’
*/
	if(ACC(ident)){
/*赋值语句： ident := Expression*/
		Expect(become);
		Expression();
	}else if(ACC(callsym)){
/*过程调用语句： call ident */
		Expect(ident);
	}else if (ACC(beginsym)){
/*复合语句： begin statement {;<statement>} end */
		do{
			Statement();
		}while(ACC(semicolon));
		Expect(endsym);
	}else if (ACC(ifsym)){
/*条件语句： if condition then statement */
		Condition();
		Expect(thensym);
		Statement();
	}else if (ACC(whilesym)){
/*当循环语句： while condition do statement */
		Condition();
		Expect(dosym);
		Statement();
	}else if (ACC(readsym)){
/*读语句： read ( {<Statement>, })*/
		Expect(lparen);
		do{
			Expect(ident);
		}while(ACC(comma));//comma ,
		Expect(rparen);

	}else if (ACC(writesym)) {
/*写语句： write ( {<Statement>, })*/
		Expect(lparen);
		do{
			Statement();
		}while(ACC(comma));//comma ,
		Expect(rparen);
	}else{
		readnext();
	}
}//~

void Expression()
{/*根据课本P14 表达式语法描述图 */
/*<表达式> ::= [+|-]<项>{<加法运算符> <项>}
 *expression = [ "+"|"-"] term { ("+"|"-") term}.
 */
	if(CurrentToken==plus||CurrentToken==minus){
		readnext();
	}
	Term();
	while(CurrentToken==plus||CurrentToken==minus){
		readnext();
		Term();
	}
}


void Factor()
{/*根据课本P15 因子语法描述图*/
/*<因子> ::= <标识符>|<无符号整数>| ‘(’<表达式>‘)’
 *factor = ident | number | "(" expression ")".
 */
	if(ACC(ident)){
		;
	}else if (ACC(number)){
		;
	}else if (ACC(lparen)){
		Expression();
		Expect(rparen);
	}else{/*报错信息*/
		//printf("因子错误");
		readnext();
	}
}

void Term()
{/*根据课本P15 项语法描述图*/
/*<项> ::= <因子>{<乘法运算符> <因子>}
 *term = factor {("*"|"/") factor} .
 */
 	Factor();
	while(CurrentToken==times || CurrentToken==slash){
		readnext();
		Factor();
	}
}//~

void Block()
{/*分程序 根据课本P13 分程序语法描述图*/
/*
 *<分程序> ::=[<常量说明>][<变量说明>][<过程说明>]<语句>
 *	<常量说明> ::=CONST<常量定义>{，<常量定义>};
 *	<变量说明> ::=VAR <标识符>{, <标识符>};
 *	<过程说明> ::=<过程首部><分程序>{; <过程说明> };
 *		     <过程首部> ::=PROCEDURE <标识符>;
 */
	if(ACC(constsym)){
/*常量说明 const {<ident = number>,}*/
		do {
			Expect(ident);
			Expect(eql);
			Expect(number);
		}while(ACC(comma)); //遇到逗号
	}
	if(ACC(varsym)){
/*变量说明 var {ident , } ;*/
		do {
			Expect(ident);
		}while(ACC(comma));
		Expect(semicolon);
	}
/*过程说明 {procedure ident ; Block; }statement*/
	while (ACC(procsym)) {
		Expect(ident);
		Expect(semicolon);
		Block();
		Expect(semicolon);
	}
	Statement();
}//~

void PL0()
{//<程序>::=<分程序>.
	readnext();/*开始先读，启动*/
	Block();/*分程序*/
	Expect(period);/*以点结束*/
	printf("#########################\n ");
	printf("恭喜您通过邱日的PL0语法分析! \n");
	printf("#########################\n ");
}

void showTokentype()
{
	printf("状态转移: *");
	for(int i=0;i<total_token;i++){
		printf("->");
		printf("%d",mytoken[i]);
	}
	printf("#\n");
}

int main( int argc, char **argv )
{
	printf("准备打开文件\n");
	++argv, --argc;  /* skip over program name */
        if ( argc > 0 )
                 yyin = fopen( argv[0], "r" );
         else
                 yyin = stdin;
	 printf("打开文件成功！，正在词法分析\n");
         yylex();
	printf("词法分析完成！\n");
	showlineinfo();
	showTokentype();
	PL0();
	return 0;
}
