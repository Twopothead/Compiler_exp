%{
#include <stdio.h>
#include <stdlib.h>
#include <iostream>/*由于用到了C++,要用g++来编译，不应用gcc*/
#include <string>
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
	/*Boolean expression SLR实验相关*/
	notsym,andsym,orsym,truesym,falsesym,

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
/*以下为SLR实验相关*/



%}

%%
not 		{/*SLR boolean expression*/printf("%s:非\n",yytext);mytoken[total_token]=notsym;total_token++;/*notsym*/}
and 		{/*SLR*/printf("%s:与\n",yytext);mytoken[total_token]=andsym;total_token++;/*andsym*/}
or 		{/*SLR*/printf("%s:或\n",yytext);mytoken[total_token]=orsym;total_token++;/*orsym*/}
true 		{/*SLR*/printf("%s:真\n",yytext);mytoken[total_token]=truesym;total_token++;/*truesym*/}
false		{/*SLR*/printf("%s:假\n",yytext);mytoken[total_token]=falsesym;total_token++;/*falsesym*/}




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
using namespace std;
string globalstr[1000];/*全局字符串比如id rop id 这种依次放进去*/
string cast_sym(int i)/*这里把SLR 布尔表达式文法里用到的符号进行转换*/
{//enum -> string 
	string a="";
	if(i==ident){a="id";}
	else if(i==relationop){a="rop";}
	else if(i==neg){a="#";}
	else if(i==lparen){a="(";}
	else if(i==rparen){a=")";}
	else if(i==notsym){a="not";}
	else if(i==andsym){a="and";}
	else if(i==orsym){a="or";}
	else if(i==truesym){a="true";}
	else if(i==falsesym){a="false";}
/*这里只列举了本次实验布尔表达式文法里用到的符号，和SLR分析表中对应*/
	return a;
}
#include "MySLRparser.cpp"
/*这里把SLR的代码包括进来了*/
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
	cout<<"共有"<<total_token<<"个符号";
	for(int i=0;i<total_token;i++){
	 /*cout<<mytoken[i]<<" ";*/	
	 cout<<cast_sym(mytoken[i])<<" ";
	 globalstr[i]=cast_sym(mytoken[i]);/*把分析好的存入全局符号串，例如x>y#转为id rop id #存入*/
	}
	//for(int i=0;i<total_token;i++)cout<<globalstr[i];
	SLR_parser();/*进行SLR分析判断是否是，本次最重要的内容*/
	
	return 0;
}
