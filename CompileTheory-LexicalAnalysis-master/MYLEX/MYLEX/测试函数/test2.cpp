#include<iostream>
using namespace std;
int cope(int a,int b,int c)   //���a,b������c�򷵻�10
{
if(a>c&&b>c)
return 10;
else 
return 0;
}
void cppo(int a,int b,int &c)//���a,b����֮һ����c,�޸�cֵΪa
{
 if(a>c||b>c)
 c=a;
else 
c=b;
}
int main()    
{
int a,b,c,d;
cin>>a>>b>>c;
d=cope(a,b,c);
cppo(a,b,c);
cout<<d<<endl;
cout<<c<<endl;
return 0;
}