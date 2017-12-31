%{
#include <stdio.h>
#include <stdlib.h>
#include <iostream>/*由于用到了C++,要用g++来编译，不应用gcc*/
#include <string>
#include <fstream>
using namespace std;
int num_lines = 0, num_chars = 0;
/*
typedef enum{
beginsym,callsym,constsym,dosym,endsym,ifsym,
oddsym,procsym,readsym,thensym,varsym,whilesym,
Writesym,pplus,pminus,times,slash,lparen,rparen,
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
	writesym,pplus,pminus,times,slash,lparen,rparen,
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
const char* Tokenstr[]={
	/*Boolean expression SLR实验相关*/
	"notsym","andsym","orsym","truesym","falsesym",

	/*VN*/
	"beginsym","callsym","constsym","dosym","endsym","ifsym",
	"oddsym","procsym","readsym","thensym","varsym","whilesym"","
	"writesym","pplus","pminus","times","slash","lparen","rparen",
	"eql","comma","period","neg","semicolon",
	/*VT*/
	"ident",/*标识符*/
	"number",/*数字*/
	"block","factor","expression",
	"term","condition",
	"relationop",/*关系运算符号*/
	"become"/*赋值符号 :=*/
};


string rawstr[1000];/*用来存原始的串*/
%}

%%
not 		{/*SLR boolean expression*/printf("%s:非\n",yytext);mytoken[total_token]=notsym;
		rawstr[total_token]=yytext;
		total_token++;/*notsym*/}
and 		{/*SLR*/printf("%s:与\n",yytext);mytoken[total_token]=andsym;
		rawstr[total_token]=yytext;
		total_token++;/*andsym*/}
or 		{/*SLR*/printf("%s:或\n",yytext);mytoken[total_token]=orsym;
		rawstr[total_token]=yytext;
		total_token++;/*orsym*/}
true 		{/*SLR*/printf("%s:真\n",yytext);mytoken[total_token]=truesym;
		rawstr[total_token]=yytext;
		total_token++;/*truesym*/}
false		{/*SLR*/printf("%s:假\n",yytext);mytoken[total_token]=falsesym;
		rawstr[total_token]=yytext;
		total_token++;/*falsesym*/}


begin		{	printf("%s:开始\n",yytext);mytoken[total_token]=beginsym;
		rawstr[total_token]=yytext;
		total_token++;/*beginsym*/}
call		{	printf("%s:调用\n",yytext);mytoken[total_token]=callsym;
		rawstr[total_token]=yytext;
		total_token++;/*callsym*/}
const		{	printf("%s:常量\n",yytext);mytoken[total_token]=constsym;
		rawstr[total_token]=yytext;
		total_token++;/*constsym*/}
do		{	printf("%s:做\n",yytext);mytoken[total_token]=dosym;
		rawstr[total_token]=yytext;
		total_token++;/*dosym*/}
end		{	printf("%s:结束\n",yytext);mytoken[total_token]=endsym;
		rawstr[total_token]=yytext;
		total_token++; /*endsym*/}
if		{	printf("%s:如果\n",yytext);mytoken[total_token]=ifsym;
		rawstr[total_token]=yytext;
		total_token++; /*ifsym*/}
odd		{	printf("%s:ODD\n",yytext);mytoken[total_token]=oddsym;
		rawstr[total_token]=yytext;
		total_token++; /*oddsym*/}
procedure	{	printf("%s:过程\n",yytext);mytoken[total_token]=procsym;
		rawstr[total_token]=yytext;
		total_token++; /*procsym*/}
read		{	printf("%s:读\n",yytext);mytoken[total_token]=readsym;
		rawstr[total_token]=yytext;
		total_token++; /*readsym*/}
then		{	printf("%s:然后\n",yytext);mytoken[total_token]=thensym;
		rawstr[total_token]=yytext;
		total_token++;/*thensym*/}
var		{	printf("%s:变量声明\n",yytext);mytoken[total_token]=varsym;
		rawstr[total_token]=yytext;
		total_token++;/*var*/}
while		{	printf("%s:当\n",yytext);mytoken[total_token]=whilesym;
		rawstr[total_token]=yytext;
		total_token++;/*whilesym*/}
write		{	printf("%s:写\n",yytext);mytoken[total_token]=writesym;
		rawstr[total_token]=yytext;
		total_token++;/*writesym*/}
[+]		{	printf("%s:加\n",yytext);mytoken[total_token]=pplus;
		rawstr[total_token]=yytext;
		total_token++;/*plus*/}
[-]		{	printf("%s:减\n",yytext);mytoken[total_token]=pminus;
		rawstr[total_token]=yytext;
		total_token++;/*pminus*/}
[*]		{	printf("%s:乘\n",yytext);mytoken[total_token]=times;
		rawstr[total_token]=yytext;
		total_token++;/*times*/}
[/]		{	printf("%s:除\n",yytext);mytoken[total_token]=slash;
		rawstr[total_token]=yytext;
		total_token++;/*slash*/}
[(]		{	printf("%s:左括号\n",yytext);mytoken[total_token]=lparen;
		rawstr[total_token]=yytext;
		total_token++;/*lparen*/}
[)]		{	printf("%s:右括号\n",yytext);mytoken[total_token]=rparen;
		rawstr[total_token]=yytext;
		total_token++;/*rparen*/}
[=]		{	printf("%s:等于号\n",yytext);mytoken[total_token]=eql;
		rawstr[total_token]=yytext;
		total_token++;/*eql*/}
[,]		{	printf("%s:逗号\n",yytext);mytoken[total_token]=comma;
		rawstr[total_token]=yytext;
		total_token++;/*comma*/}
[.]		{	printf("%s:点！程序结束\n",yytext);mytoken[total_token]=period;
		rawstr[total_token]=yytext;
		total_token++;/*period*/}
[#]		{	printf("%s:井号\n",yytext);mytoken[total_token]=neg;
		rawstr[total_token]=yytext;
		total_token++;/*neg*/}
[;]		{	printf("%s:分号\n",yytext);mytoken[total_token]=semicolon;
		rawstr[total_token]=yytext;
		total_token++;/*semicolon*/}

[<>]|>=|<=|==|!= { 	printf("%s:关系运算符\n",yytext);mytoken[total_token]=relationop;
		rawstr[total_token]=yytext;
		total_token++;/*relationop*/}
[*|/]		{ 	printf("%s:乘法运算符\n",yytext);}
[0-9]*	 {	printf("%s:数字\n",yytext);//[0-9][0-9]*|^-?\d+$
		/*mytoken[total_token]=number;*/
		mytoken[total_token]=ident;//这里让布尔表达式文法里的id也能是数字
		rawstr[total_token]=yytext;
		total_token++;/*number*/}
:=  		{ 	printf("%s:赋值\n",yytext);mytoken[total_token]=relationop;
		rawstr[total_token]=yytext;
		total_token++;/*become*/
/*
[0-9][0-9]*	{ 	printf("%s:无符号整数\n",yytext);}
^-?\d+$		{ 	printf("%s:整数\n",yytext);}
*/
}
[A-Za-z]|[A-Za-z][A-Za-z0-9]* { printf("%s:标识符\n",yytext);mytoken[total_token]=ident;
		rawstr[total_token]=yytext;
		total_token++;
	/*ident*/}
\n		{ /*printf("%s:换行符\n",yytext);*/ ++num_lines; ++num_chars;}
[\t\r]		{ /*printf("%s:制表符\n",yytext);*//*过滤空白*/}
[ ]		{ /*printf("%s:空白\n",yytext);*/}
 .      	{ ++num_chars;}
%%

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
	showrules();
	SLR_parser();/*进行SLR分析判断是否是，本次最重要的内容*/
	cout<<"\n generated pcode:\n";
	int i;
	for(i=100;i<nextstat;i++){
		cout<<"["<<i<<"]"<<"\t{";
		for(int j=0;j<4;j++){
			cout<<gen_pcode[i][j]<<" ";
			if(j!=3)cout<<",";
		}
		cout<<"}"<<endl;
	}
	ofstream pcode_file("pcode.txt");
	if(pcode_file.is_open()){
		for(i=100;i<nextstat;i++){
			pcode_file<<"["<<i<<"]"<<"\t{";
			for(int j=0;j<4;j++){
				pcode_file<<gen_pcode[i][j]<<" ";
				if(j!=3)pcode_file<<",";
			}
			pcode_file<<"}"<<endl;
		}
		pcode_file.close();
	}
//for(int i=0;i<total_token;i++)cout<<rawstr[i]<<" ";
	return 0;
}
