// 词法分析器.cpp : 定义控制台应用程序的入口点。
//


  #include<iostream>
  #include<string>
  //#include<stdio.h>
  using namespace std;
  
  char ch = ' ';
  static int line = 1;
  static int row = 0;
  int numberCount = 0;
  int idCount = 0;
  string arr = "";
  
  string Key[] = { "if", "else", "for", "while", "do", "return", "break", "continue" };
  string Delimiter[] = { ";", "(", ")", "[", "]", ",", ".", "{", "}" };
  string Operator[] = { "+", "-", "*", "/" };
  string R_operators[] = { "<", "<=", "==", ">", ">=" };
  string Number[100];
  string Identifier[100];
  
  
  int isKey(string s)//判断是否是标识符
  {
  	for (int i = 0; i <8; i++)
  	{
  		if (Key[i].compare(s) == 0)
  			return 1;
  	}
  	return 0;
  }
  
  int isLetter(char c)
  {
  	if (((c <= 'z') && (c >= 'a')) || ((c <= 'Z') && (c >= 'A')))
  	{
  		if ((c <= 'Z') && (c >= 'A'))
  			ch = ch + 32;
  		return 1;
  	}
  	return 0;
  
  }
  
  int isNumber(char c)
  {
  	if (c >= '0'&&c <= '9')
  		return 1;
  	return 0;
  }
  
  int insertId(string s)
  {
  	for (int i = 0; i < idCount; i++)
  	{
  		if (Identifier[i] == s)
  		{
  			return i;
  			break;
  		}
  		else if (idCount == i + 1)
  		{
  			Identifier[idCount] = s;
  			return idCount;
  			idCount++;//not understand
  		}
  	}
  }
  
  int insertNumber(string s)
  {
  	for (int i = 0; i < numberCount; i++)
  	{
  		if (Number[i] == s)
  		{
  			return i;
  			break;
  		}
  		else if (numberCount == i + 1)
  		{
  			Number[numberCount] = s;
  			return numberCount;
  			numberCount++;
  		}
  	}
  }
  void analyse(FILE *fpin)
  {
  
  	while ((ch = fgetc(fpin)) != EOF)//依次读数据
  	{
  		arr = "";
  		if (ch == ' ' || ch == '\t' || ch == '\n')//如果ch为空格或者回车或者换行符
  		{
  			if (ch == '\n')//如果是换行则行加1 列置0
  			{
  				line++;
  				row = 0;
  			}
  		}
  		else if (isLetter(ch))//第一个字符如果是字母的话
  		{
  			while (isLetter(ch) || isNumber(ch))//如果是字母或者数字的话，相加并且往下读
  			{
  				arr = arr + ch;
  				ch = fgetc(fpin);
  			}
  
  			fseek(fpin, -1L, SEEK_CUR);//之后遇到了不是字母或者数字，则回退
  
  			if (isKey(arr))//判断刚刚得到的字符串是否为保留字
  			{
  				row++;
  				cout << arr << "\t\t(1," << arr << ")" << "\t\t关键字" << "\t\t(" << line << "," << row << ")" << endl;
  			}
  			else//不是保留字的话就是标识符了
  			{
  				row++;
  				insertId(arr);
  				cout << arr << "\t\t(6," << arr << ")" << "\t\t标识符 " << "\t\t(" << line << "," << row << ")" << endl;
  			}
  		}
  		else if (isNumber(ch))//第一个字符是数字的话
  		{
  			while (isNumber(ch) || (ch == '.'&&isNumber(fgetc(fpin))))//判断是否有小数的可能
  			{
  				arr = arr + ch;
  				ch = fgetc(fpin);
  			}
  			if (isLetter(ch))//一旦遇到数字其实就是错误了，标识符不能以数字开头
  			{
  				while (isLetter(ch) || isNumber(ch))
  				{
  					arr = arr + ch;
  					ch = fgetc(fpin);
  				}
  
  				fseek(fpin, -1L, SEEK_CUR);
  				row++;
  				cout << arr << "\t\tError" << "\t\tError" << "\t\t(" << line << "," << row << ")" << endl;
  			}
  			else{
  				insertNumber(arr);//插入刚刚得到的数字
  				row++;
  				fseek(fpin, -1L, SEEK_CUR);
  				cout << arr << "\t\t(5," << arr << ")" << "\t\t常数 " << "\t\t(" << line << "," << row << ")" << endl;
  
  			}
  
  		}
  		else
  		{
  			row++;
  			arr = ch;
  			switch (ch)
  			{
  			case'+':{
  						ch = fgetc(fpin);
  						if (ch == '(' || isNumber(ch) || isLetter(ch))
  						{
  							fseek(fpin, -1L, SEEK_CUR);
  							cout << "+" << "\t\t( 3,+ )" << "\t\t算术运算符 " << "\t\t(" << line << "," << row << ")" << endl;
  						}
  						else
  						{
  							cout << arr + ch << "\t\tError" << "\t\tError" << "\t\t(" << line << "," << row << ")" << endl;
  						}
  						break;
  			}
  			case'-':{
  						ch = fgetc(fpin);
  						if (ch == '(' || isNumber(ch) || isLetter(ch))
  						{
  							fseek(fpin, -1L, SEEK_CUR);
  							cout << '-' << "\t\t(3,-)" << "\t\t算术运算符" << "\t\t(" << line << "," << row << ")" << endl;
  						}
  						else
  						{
  							cout << arr + ch << "\t\tError" << "\t\tError" << "\t\t(" << line << "," << row << ")" << endl;
  						}
  						break;
  			}
  			case'*':cout << '/' << "\t\t(3,*)" << "\t\t算术运算符" << "\t\t(" << line << "," << row << ")" << endl;
  			case'=':{
  						ch = fgetc(fpin);
  						if (ch == '=')
  						{
  							cout << "==" << "\t\t(4,==)" << "\t\t关系运算符 " << "\t\t(" << line << "," << row << ")" << endl;
  						}
  						else
  						{
  							fseek(fpin, -1L, SEEK_CUR);
  							cout << "=" << "\t\t(4,=)" << "\t\t关系运算符 " << "\t\t(" << line << "," << row << ")" << endl;
  						}
  						break;
  			}
  			case'/':cout << '/' << "\t\t(3,/)" << "\t\t算术运算符" << "\t\t(" << line << "," << row << ")" << endl;
  			case'(':
  			case')':
  			case'[':
  			case']':
  			case';':
  			case'.':
  			case',':
  			case'{':
  			case'}':cout << ch << "\t\t(2," << ch << ")" << "\t\t分界符 " << "\t\t(" << line << "," << row << ")" << endl;
  				break;
  			case'>':{
  						ch = fgetc(fpin);
  						if (ch == '=')
  							cout << ">=" << "\t\t(4,>=)" << "\t\t关系运算符 " << "\t\t(" << line << "," << row << ")" << endl;
  						else
  						{
  							cout << ">" << "\t\t(4,>)" << "\t\t关系运算符 " << "\t\t(" << line << "," << row << ")" << endl;
  							fseek(fpin, -1L, SEEK_CUR);
  						}
  						break;
  			}
  			case'<':{
  						ch = fgetc(fpin);
  						if (ch == '=')
  							cout << "<=" << "\t\t(4,<=)" << "\t\t关系运算符 " << "\t\t(" << line << "," << row << ")" << endl;
  						else
  						{
  							cout << "<" << "\t\t(4,<)" << "\t\t关系运算符 " << "\t\t(" << line << "," << row << ")" << endl;
  							fseek(fpin, -1L, SEEK_CUR);
  						}
  						break;
  			}
  			default:
  				cout << ch << "\t\tError" << "\t\tError" << "\t\t(" << line << "," << row << ")" << endl;
  				break;
  
  			}
  		}
  
  	}
  
  }
  int main()
  {
  	char in_fn[30]="cifafenxiqi.txt";
  	FILE *fpin;
  	cout << "请输入txt文件的绝对路径" << endl;
  	for (;;){
  		//cin >>in_fn;
  		if ((fpin = fopen(in_fn, "r")) != NULL)
  			break;
  		else
  			cout << "输入正确的路径" << endl;
  	}
  	analyse(fpin);
  	fclose(fpin);
  	return 0;
  }
