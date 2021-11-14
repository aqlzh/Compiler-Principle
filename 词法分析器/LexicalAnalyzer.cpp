// �ʷ�������.cpp : �������̨Ӧ�ó������ڵ㡣
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
  
  
  int isKey(string s)//�ж��Ƿ��Ǳ�ʶ��
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
  
  	while ((ch = fgetc(fpin)) != EOF)//���ζ�����
  	{
  		arr = "";
  		if (ch == ' ' || ch == '\t' || ch == '\n')//���chΪ�ո���߻س����߻��з�
  		{
  			if (ch == '\n')//����ǻ������м�1 ����0
  			{
  				line++;
  				row = 0;
  			}
  		}
  		else if (isLetter(ch))//��һ���ַ��������ĸ�Ļ�
  		{
  			while (isLetter(ch) || isNumber(ch))//�������ĸ�������ֵĻ�����Ӳ������¶�
  			{
  				arr = arr + ch;
  				ch = fgetc(fpin);
  			}
  
  			fseek(fpin, -1L, SEEK_CUR);//֮�������˲�����ĸ�������֣������
  
  			if (isKey(arr))//�жϸոյõ����ַ����Ƿ�Ϊ������
  			{
  				row++;
  				cout << arr << "\t\t(1," << arr << ")" << "\t\t�ؼ���" << "\t\t(" << line << "," << row << ")" << endl;
  			}
  			else//���Ǳ����ֵĻ����Ǳ�ʶ����
  			{
  				row++;
  				insertId(arr);
  				cout << arr << "\t\t(6," << arr << ")" << "\t\t��ʶ�� " << "\t\t(" << line << "," << row << ")" << endl;
  			}
  		}
  		else if (isNumber(ch))//��һ���ַ������ֵĻ�
  		{
  			while (isNumber(ch) || (ch == '.'&&isNumber(fgetc(fpin))))//�ж��Ƿ���С���Ŀ���
  			{
  				arr = arr + ch;
  				ch = fgetc(fpin);
  			}
  			if (isLetter(ch))//һ������������ʵ���Ǵ����ˣ���ʶ�����������ֿ�ͷ
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
  				insertNumber(arr);//����ոյõ�������
  				row++;
  				fseek(fpin, -1L, SEEK_CUR);
  				cout << arr << "\t\t(5," << arr << ")" << "\t\t���� " << "\t\t(" << line << "," << row << ")" << endl;
  
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
  							cout << "+" << "\t\t( 3,+ )" << "\t\t��������� " << "\t\t(" << line << "," << row << ")" << endl;
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
  							cout << '-' << "\t\t(3,-)" << "\t\t���������" << "\t\t(" << line << "," << row << ")" << endl;
  						}
  						else
  						{
  							cout << arr + ch << "\t\tError" << "\t\tError" << "\t\t(" << line << "," << row << ")" << endl;
  						}
  						break;
  			}
  			case'*':cout << '/' << "\t\t(3,*)" << "\t\t���������" << "\t\t(" << line << "," << row << ")" << endl;
  			case'=':{
  						ch = fgetc(fpin);
  						if (ch == '=')
  						{
  							cout << "==" << "\t\t(4,==)" << "\t\t��ϵ����� " << "\t\t(" << line << "," << row << ")" << endl;
  						}
  						else
  						{
  							fseek(fpin, -1L, SEEK_CUR);
  							cout << "=" << "\t\t(4,=)" << "\t\t��ϵ����� " << "\t\t(" << line << "," << row << ")" << endl;
  						}
  						break;
  			}
  			case'/':cout << '/' << "\t\t(3,/)" << "\t\t���������" << "\t\t(" << line << "," << row << ")" << endl;
  			case'(':
  			case')':
  			case'[':
  			case']':
  			case';':
  			case'.':
  			case',':
  			case'{':
  			case'}':cout << ch << "\t\t(2," << ch << ")" << "\t\t�ֽ�� " << "\t\t(" << line << "," << row << ")" << endl;
  				break;
  			case'>':{
  						ch = fgetc(fpin);
  						if (ch == '=')
  							cout << ">=" << "\t\t(4,>=)" << "\t\t��ϵ����� " << "\t\t(" << line << "," << row << ")" << endl;
  						else
  						{
  							cout << ">" << "\t\t(4,>)" << "\t\t��ϵ����� " << "\t\t(" << line << "," << row << ")" << endl;
  							fseek(fpin, -1L, SEEK_CUR);
  						}
  						break;
  			}
  			case'<':{
  						ch = fgetc(fpin);
  						if (ch == '=')
  							cout << "<=" << "\t\t(4,<=)" << "\t\t��ϵ����� " << "\t\t(" << line << "," << row << ")" << endl;
  						else
  						{
  							cout << "<" << "\t\t(4,<)" << "\t\t��ϵ����� " << "\t\t(" << line << "," << row << ")" << endl;
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
  	cout << "������txt�ļ��ľ���·��" << endl;
  	for (;;){
  		//cin >>in_fn;
  		if ((fpin = fopen(in_fn, "r")) != NULL)
  			break;
  		else
  			cout << "������ȷ��·��" << endl;
  	}
  	analyse(fpin);
  	fclose(fpin);
  	return 0;
  }
