/*#include <iostream>
#include <stack>
#include <cmath>
#include "stdio.h"
#include <string>
using namespace std;
*/
#include <stack>
/*这里的代码会被另一个代码文件pl0lex.cpp包括进去*/
#define ACC  888
int getsymcol(string sym)
{/*通过符号获取其相应的符号数*/
        if(sym=="not")return 0;//if(sym=="!")return 0;
        else if(sym=="and")return 1;//else if(sym=="&")return 1;
        else if(sym==")")return 2;
        else if(sym=="(")return 3;
        else if(sym=="rop")return 4;//else if(sym=="p")return 4;
        else if(sym=="or")return 5;//else if(sym=="|")return 5;
        else if(sym=="true")return 6;//else if(sym=="1")return 6;
        else if(sym=="false")return 7;//else if(sym=="0")return 7;
        else if(sym=="id")return 8;
        else if(sym=="#")return 9;
        else if(sym=="E")return 10;
        return -1;
}
void showBoolean_expression_rules(int i)
{	
	if(i==1)cout<<"E -> E or E";
	else if(i==2)cout<<"E -> E and E";
	else if(i==3)cout<<"E -> not E";
	else if(i==4)cout<<"E -> ( E )";
	else if(i==5)cout<<"E -> id rop id";
	else if(i==6)cout<<"E -> true";
	else if(i==7)cout<<"E -> flase";
	return;
}
/*布尔表达式文法*/
// E -> E | E   即 E -> E or E
// E -> E & E   即 E -> E and E
// E -> ! E     即 E -> not E
// E -> ( E )
// E -> id p id 即 E -> id rop id  其中rop为关系运算符
// E -> 1       即 E -> true
// E -> 0       即 E -> flase
        //由布尔表达式文法得到的SLR分析表
        // | State | 0  | 1  |  2  | 3  |  4  | 5  | 6  | 7  |  8  |   9    |  E  |
        // +-------|---------A----C----T----I ----O----N--------------------|-GOTO|
        // +-------+----+----+-----+----+-----+----+----+----+-----+--------+-----+
        // | State | !  | &  |  )  | (  |  p  | |  | 1  | 0  |  id |   #    |  E  |
        // +-------+----+----+-----+----+-----+----+----+----+-----+--------+-----+
        // |   0   | S2 | 0  |  0  | S3 |  0  | 0  | S5 | S6 |  S4 |   0    |  S1 |
        // |   1   | 0  | S8 |  0  | 0  |  0  | S7 | 0  | 0  |  0  | Accept |  0  |
        // |   2   | S2 | 0  |  0  | S3 |  0  | 0  | S5 | S6 |  S4 |   0    |  S9 |
        // |   3   | S2 | 0  |  0  | S3 |  0  | 0  | S5 | S6 |  S4 |   0    | S10 |
        // |   4   | 0  | 0  |  0  | 0  | S11 | 0  | 0  | 0  |  0  |   0    |  0  |
        // |   5   | 0  | R6 |  R6 | 0  |  0  | R6 | 0  | 0  |  0  |   R6   |  0  |
        // |   6   | 0  | R7 |  R7 | 0  |  0  | R7 | 0  | 0  |  0  |   R7   |  0  |
        // |   7   | S2 | 0  |  0  | S3 |  0  | 0  | S5 | S6 |  S4 |   0    | S12 |
        // |   8   | S2 | 0  |  0  | S3 |  0  | 0  | S5 | S6 |  S4 |   0    | S13 |
        // |   9   | 0  | R3 |  R3 | 0  |  0  | R3 | 0  | 0  |  0  |   R3   |  0  |
        // |  10   | 0  | S8 | S14 | 0  |  0  | S7 | 0  | 0  |  0  |   0    |  0  |
        // |  11   | 0  | 0  |  0  | 0  |  0  | 0  | 0  | 0  | S15 |   0    |  0  |
        // |  12   | 0  | R1 |  R1 | 0  |  0  | R1 | 0  | 0  |  0  |   R1   |  0  |
        // |  13   | 0  | R2 |  R2 | 0  |  0  | R2 | 0  | 0  |  0  |   R2   |  0  |
        // |  14   | 0  | R4 |  R4 | 0  |  0  | R4 | 0  | 0  |  0  |   R4   |  0  |
        // |  15   | 0  | R5 |  R5 | 0  |  0  | R5 | 0  | 0  |  0  |   R5   |  0  |
        // +-------+----+----+-----+----+-----+----+----+----+-----+--------+-----+

//Si shift 把当前输入符号和状态i压栈
//Rj reduce 按第j个产生式归约
int reducenum(int i)
{/*一共7个产生式，每个产生式右部有几个符号，即待归约符号的数量*/
        int num[7]={3,3,2,3,3,1,1};
        return num[i-1];
}

int SLR_parser()
{/*这里使用plolex.cpp里定义的全局字符串数组globalstr*/
        /*int GOTO[16] = { 1,0,9,10,0,0,0,12,13,0,0,0,0,0,0,0};*/
        //string str[14]={"(","(","id","rop","id",")","or","(","true","and","false",")",")","#"};
       // for(int i=0;i<14;i++) cout<<str[i]<<" ";

        int ip=0,j=0;/*ip指示指到哪了*/
        string sym;/*存符号*/
        int state_row;/*状态数*/
        int sym_col;/*符号数*/
        int top;
        int Reduce_j;/*这是用来存归约Rj的下标j的*/
        int Reduce_j_reducenum;/*由Rj知道用到是第几条产生式，这个产生式右部有几个符号(待归约的总数)*/
        string nt[7]={"E","E","E","E","E","E","E"};/*布尔表达式文法7个产生式的左部都是E*/
        int ACTION_GOTO[16][11]={/*左部是ACTION表，右部是GOTO表*/
                2 ,0 ,0 ,3 ,0 ,0 ,5 ,6 ,4 ,0 ,          1,//0
                0 ,8 ,0 ,0 ,0 ,7 ,0 ,0 ,0 ,888 ,        0,//1  888 ACC
                2 ,0 ,0 ,3 ,0 ,0 ,5 ,6 ,4 ,0 ,          9,//2
                2 ,0 ,0 ,3 ,0 ,0 ,5 ,6 ,4 ,0 ,          10,//3
                0 ,0 ,0 ,0 ,11,0 ,0 ,0 ,0 ,0 ,          0,//4
                0 ,-6,-6,0 ,0 ,-6,0 ,0 ,0 ,-6,          0,//5
                0 ,-7,-7,0 ,0 ,-7,0 ,0 ,0 ,-7,          0,//6
                2 ,0 ,0 ,3 ,0 ,0 ,5 ,6 ,4 ,0 ,          12,//7
                2 ,0 ,0 ,3 ,0 ,0 ,5 ,6 ,4 ,0 ,          13,//8
                0 ,-3,-3,0 ,0 ,-3,0 ,0 ,0 ,-3,          0,//9
                0 ,8 ,14,0 ,0 ,7 ,0 ,0 ,0 ,0 ,          0,//10
                0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,0 ,          0,//11
                0 ,-1,-1,0 ,0 ,-1,0 ,0 ,0 ,-1,          0,//12
                0 ,-2,-2,0 ,0 ,-2,0 ,0 ,0 ,-2,          0,//13
                0 ,-4,-4,0 ,0 ,-4,0 ,0 ,0 ,-4,          0,//14
                0 ,-5,-5,0 ,0 ,-5,0 ,0 ,0 ,-5,          0 //15
        };
        stack<int> statestack;/*状态栈*/
        statestack.push(0);/*开始是0状态*/
        ip=0;
        while(1){
                //sym=str[ip];/*获得符号*/
		sym=globalstr[ip];/*这里从另一个文件pl0lex.cpp里定义的全局字符串数组获得符号*/
                sym_col=getsymcol(sym);/*获得符号数*/
                state_row=statestack.top();/*得到栈顶当前状态*/
                if(ACTION_GOTO[state_row][sym_col]>0){/*Shift 移进*/
                        if(ACTION_GOTO[state_row][sym_col]!=ACC){/*接受ACC在表中是888*/
                                statestack.push(ACTION_GOTO[state_row][sym_col]);
                        }else{
                                cout<<" \nSuccess! （is boolean expression）该语句符合布尔表达式文法 \n";
                                break;
                        }
                        ip++;/*往下挪*/
                }else if(ACTION_GOTO[state_row][sym_col]<0){/*Reduce 归约*/
                        Reduce_j=-ACTION_GOTO[state_row][sym_col];
                        Reduce_j_reducenum=reducenum(Reduce_j);cout<<"\n归约所用产生式：["<<Reduce_j<<"]",showBoolean_expression_rules(Reduce_j);
                        for(j=0;j< Reduce_j_reducenum;j++){
                                statestack.pop();
                        }
                        statestack.push(ACTION_GOTO[statestack.top()][getsymcol(nt[Reduce_j-1])]);
                }else{
                        cout<<" \nFail! (not a boolean expression)  该语句不符合布尔表达式文法 \n";
                        break;
                }
        }
        return 0;
}

int SLR_demo()
{/*A complete simple demo for SLR Analysis,This is GOOD CODE.*/
/*This demo just judge whether a sentence is a boolean expression or not,you can change string str to test
 *Demo result:( ( id rop id ) or ( true and false ) ) #  Success! （is boolean expression）
 */
        /*int GOTO[16] = { 1,0,9,10,0,0,0,12,13,0,0,0,0,0,0,0};*/
        string str[14]={"(","(","id","rop","id",")","or","(","true","and","false",")",")","#"};
        for(int i=0;i<14;i++) cout<<str[i]<<" ";

        int ip=0,j=0;/*ip指示指到哪了*/
        string sym;/*存符号*/
        int state_row;/*状态数*/
        int sym_col;/*符号数*/
        int top;
        int Reduce_j;/*这是用来存归约Rj的下标j的*/
        int Reduce_j_reducenum;/*由Rj知道用到是第几条产生式，这个产生式右部有几个符号(待归约的总数)*/
        string nt[7]={"E","E","E","E","E","E","E"};/*布尔表达式文法7个产生式的左部都是E*/
        int ACTION_GOTO[16][11]={/*左部是ACTION表，右部是GOTO表*/
                2 ,0 ,0 ,3 ,0 ,0 ,5 ,6 ,4 ,0 ,          1,//0
                0 ,8 ,0 ,0 ,0 ,7 ,0 ,0 ,0 ,888 ,        0,//1  888 ACC
                2 ,0 ,0 ,3 ,0 ,0 ,5 ,6 ,4 ,0 ,          9,//2
                2 ,0 ,0 ,3 ,0 ,0 ,5 ,6 ,4 ,0 ,          10,//3
                0 ,0 ,0 ,0 ,11,0 ,0 ,0 ,0 ,0 ,          0,//4
                0 ,-6,-6,0 ,0 ,-6,0 ,0 ,0 ,-6,          0,//5
                0 ,-7,-7,0 ,0 ,-7,0 ,0 ,0 ,-7,          0,//6
                2 ,0 ,0 ,3 ,0 ,0 ,5 ,6 ,4 ,0 ,          12,//7
                2 ,0 ,0 ,3 ,0 ,0 ,5 ,6 ,4 ,0 ,          13,//8
                0 ,-3,-3,0 ,0 ,-3,0 ,0 ,0 ,-3,          0,//9
                0 ,8 ,14,0 ,0 ,7 ,0 ,0 ,0 ,0 ,          0,//10
                0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,0 ,          0,//11
                0 ,-1,-1,0 ,0 ,-1,0 ,0 ,0 ,-1,          0,//12
                0 ,-2,-2,0 ,0 ,-2,0 ,0 ,0 ,-2,          0,//13
                0 ,-4,-4,0 ,0 ,-4,0 ,0 ,0 ,-4,          0,//14
                0 ,-5,-5,0 ,0 ,-5,0 ,0 ,0 ,-5,          0 //15
        };
        stack<int> statestack;/*状态栈*/
        statestack.push(0);/*开始是0状态*/
        ip=0;
        while(1){
                sym=str[ip];/*获得符号*/
                sym_col=getsymcol(sym);/*获得符号数*/
                state_row=statestack.top();/*得到栈顶当前状态*/
                if(ACTION_GOTO[state_row][sym_col]>0){/*Shift 移进*/
                        if(ACTION_GOTO[state_row][sym_col]!=ACC){/*接受ACC在表中是888*/
                                statestack.push(ACTION_GOTO[state_row][sym_col]);
                        }else{
                                cout<<" Success! （is boolean expression） \n";
                                break;
                        }
                        ip++;/*往下挪*/
                }else if(ACTION_GOTO[state_row][sym_col]<0){/*Reduce 归约*/
                        Reduce_j=-ACTION_GOTO[state_row][sym_col];
                        Reduce_j_reducenum=reducenum(Reduce_j);
                        for(j=0;j< Reduce_j_reducenum;j++){
                                statestack.pop();
                        }
                        statestack.push(ACTION_GOTO[statestack.top()][getsymcol(nt[Reduce_j-1])]);
                }else{
                        cout<<" Fail! (not a boolean expression)   \n";
                        break;
                }
        }
        return 0;
}
/*
int main()
{
        SLR_demo();
        return 0;
}*/
