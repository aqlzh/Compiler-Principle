#include <stdio.h>
#include "stdlib.h"
#include <tchar.h>
#include <iostream>
#include<stack>
using namespace std;
const int NonterminalNum=5; //非终结符个数
const int TerminalNum=9; //终结符个数
char nonterminal[NonterminalNum]= {'E','A','T','B','F'}; //定义非终结符
char terminal[TerminalNum]= {'i', '+','*','(', ')','e','-','/'}; //定义终结符
stack <char>s;
void Event0();
void Event1();
void Event2();
void Event3();
void Event4();
void Event5();
void Event6();
void Event7();
void Event8();
void Event9();
void Error();
typedef void(*Action)();
Action ParseTable[NonterminalNum][TerminalNum]=
{
    {Event1,Error,Error,Event1,Error,Error,Error,Error,Error},
    {Error,Event2,Error,Error,Event3,Event3,Event3,Event4,Error},
    {Event5,Error,Error,Event5,Error,Error,Error,Error,Error},
    {Error,Event6,Event8,Error,Event6,Event6,Event6,Event6,Event7,},
    {Event0,Error,Error,Event9,Error,Error,Error,Error,Error}
};
void Event1()
{
    s.pop();
    s.push('A');
    s.push('T');
};
void Event2()
{
    s.pop();
    s.push('A');
    s.push('T');
    s.push('+');
};
void Event3()
{
    s.pop();
};
void Event4()
{
    s.pop();
    s.push('A');
    s.push('T');
    s.push('-');
};
void Event5()
{
    s.pop();
    s.push('B');
    s.push('F');
};
void Event6()
{
    s.pop();
};
void Event7()
{
    s.pop();
    s.push('B');
    s.push('F');
    s.push('/');
};
void Event8()
{
    s.pop();
    s.push('B');
    s.push('F');
    s.push('*');
};
void Event9()
{
    s.pop();
    s.push(')');
    s.push('E');
    s.push('(');
};
void  Event0()
{
    s.pop();
    s.push('i');
};
void Error()
{
    cerr<<"------分析失败!------\n";
    exit(1);
};

/**
* 看一下是不是终结符
*/
bool isVt(char ch)
{
    for(int i=0; i<9; i++)
    {
        if(terminal[i]==ch)
            return true;
        else continue;
    }
    return false;
}
void pushTogether(char nonterminal, char terminal)
{
    switch(nonterminal)
    {
    case 'E':
        switch(terminal)
        {
        case 'i':
            ParseTable[0][0]();
            break;
        case '+':
            ParseTable[0][1]();
            break;
        case '*':
            ParseTable[0][2]();
            break;
        case '(':
            ParseTable[0][3]();
            break;
        case ')':
            ParseTable[0][4]();
            break;
        case ';':
            ParseTable[0][5]();
            break;
        case 'e':
            ParseTable[0][6]();
            break;
        case '-':
            ParseTable[0][7]();
            break;
        case '/':
            ParseTable[0][8]();
            break;
        case '#':
            ParseTable[0][9]();
            break;
        default:
            break;
        }
        break;
    case 'A':
        switch(terminal)
        {
        case 'i':
            ParseTable[1][0]();
            break;
        case '+':
            ParseTable[1][1]();
            break;
        case '*':
            ParseTable[1][2]();
            break;
        case '(':
            ParseTable[1][3]();
            break;
        case ')':
            ParseTable[1][4]();
            break;
        case ';':
            ParseTable[1][5]();
            break;
        case 'e':
            ParseTable[1][6]();
            break;
        case '-':
            ParseTable[1][7]();
            break;
        case '/':
            ParseTable[1][8]();
            break;
        case '#':
            ParseTable[1][9]();
            break;
        default:
            break;
        }
        break;
    case 'T':
        switch(terminal)
        {
        case 'i':
            ParseTable[2][0]();
            break;
        case '+':
            ParseTable[2][1]();
            break;
        case '*':
            ParseTable[2][2]();
            break;
        case '(':
            ParseTable[2][3]();
            break;
        case ')':
            ParseTable[2][4]();
            break;
        case ';':
            ParseTable[2][5]();
            break;
        case 'e':
            ParseTable[2][6]();
            break;
        case '-':
            ParseTable[2][7]();
            break;
        case '/':
            ParseTable[2][8]();
            break;
        case '#':
            ParseTable[2][9]();
            break;
        default:
            break;
        }
        break;
    case 'B':
        switch(terminal)
        {
        case 'i':
            ParseTable[3][0]();
            break;
        case '+':
            ParseTable[3][1]();
            break;
        case '*':
            ParseTable[3][2]();
            break;
        case '(':
            ParseTable[3][3]();
            break;
        case ')':
            ParseTable[3][4]();
            break;
        case ';':
            ParseTable[3][5]();
            break;
        case 'e':
            ParseTable[3][6]();
            break;
        case '-':
            ParseTable[3][7]();
            break;
        case '/':
            ParseTable[3][8]();
            break;
        case '#':
            ParseTable[3][9]();
            break;
        default:
            break;
        }
        break;
    case 'F':
        switch(terminal)
        {
        case 'i':
            ParseTable[4][0]();
            break;
        case '+':
            ParseTable[4][1]();
            break;
        case '*':
            ParseTable[4][2]();
            break;
        case '(':
            ParseTable[4][3]();
            break;
        case ')':
            ParseTable[4][4]();
            break;
        case ';':
            ParseTable[4][5]();
            break;
        case 'e':
            ParseTable[4][6]();
            break;
        case '-':
            ParseTable[4][7]();
            break;
        case '/':
            ParseTable[4][8]();
            break;
        case '#':
            ParseTable[4][9]();
            break;
        default:
            break;
        }
        break;
    default:
        Error();
        break;
    }
}
void print(stack <char> s,char a[],int i)
{
    stack <char>t=s;
    int j=0;
    char b[10]= {};
    while(!t.empty())
    {
        b[j++]=t.top();
        t.pop();
    }
    for(int m=j-1; m>=0; m--) cout<<b[m];
    cout<<"                   ";
    for(int k=i; k<10; k++) cout<<a[k];
    cout<<endl;
}
void LL1Parse()
{
    s.push(';');
    s.push('E');
    char a[10]= {};
    cout<<"请输入一字符串以;结束:"<<endl;
    for(int i=0; a[i-1]!=';'; i++)
    {
        cin>>a[i];
    }

    int    i=0;
        bool flag=true;
        while(flag)
        {
            char X=s.top();
            if(isVt(X))
            {
                print(s,a,i);
                if(X==a[i])//match
                    { s.pop(); i++; }
                else
                    Error();
            }
            else if(X==';')
            {
                print(s,a,i);
                if(X==a[i])//parse successfully
                {
                    flag=false;
                    s.pop();
                }
                else Error();
            }
            else //reverse, pushintos
            {
                print(s,a,i);
                pushTogether(X,a[i]);
            }
        }
    if(s.empty()) cout<<"分析成功!"<<endl;

}
int main()
{
    cout<<"\t 文法为:\n";
    cout<<"E->TA\nA->+TA\nA->e\nA->-TA\nT->FB\nB->e\nB->/FB\nB->*FB\nF->(E)\nF->i\n";
    LL1Parse();
}