#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
#define BUFFER 256      //���建������С
class MAlex{
public:
	char range[12];  //12�����
	char opn[19][3]; //19�������
	string key[20]; //20��������
	char line[256]; //��ȡһ���ַ���
	ifstream infile;//�����ļ�����
	ofstream preout, resout;
public:
	void Init();//��ʼ��
	bool is_digit(char c); //�ж��Ƿ�������
	bool is_alpbat(char c); //�ж��Ƿ���ĸ
	int is_oprator(int &i);//�ж��Ƿ������
	int is_range(int &i);//�ж��Ƿ���
	int alpbat_c(int &i);//�ж�����ĸ��c
	int alpbat_i(int &i);//�ж�����ĸ��i
	int alpbat_s(int &i);//�ж�����ĸ��s
	int alpbat_e(int &i);//�ж�����ĸ��e
	void recog_reserve(int &i, int &num); //ʶ������
	void cope_firsrtaph(int &i);//�������ַ�����ĸ
	void cope_firsrtnum(int &i);//�������ַ�������
	void cope_range(int num, int &i);//�������ַ��ǽ��
	void cope_operaor(int &i);//�������ַ��ǲ�����
	int COPE(ifstream &inflie);//�ܴ������
	void print_list(CString &s1);
};

