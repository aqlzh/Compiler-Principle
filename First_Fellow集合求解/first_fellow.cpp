#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define length 90

int b;  //用于求FOLLOW集合
int k;  //用于存放所有非终结符时，所用的变量
int N;  //用于存放产生式数目
char sen[255];   //用于存放输入的句型
char noend[length];  //用于存放非终结符
char end[length];   //用于存放终结符
int h,z;  //用于找FIRST集合时计数
struct CHUAN
{
	char left;   //保存->左边的非终结符
	char right[length];    //保存->右边的符号
	char first[length];    //保存FIRST集合中的元素
	char follow[length];    //保存FOLLOW集合中的元素
};


//获取->左右两边的字符
int getLR(struct CHUAN *p,int i,char *sen) {
	int a = 0;
	int b;

	//获取左边的非终结符
	if (sen[0]>='A' && sen[0]<='Z')
	{
		p[i].left = sen[0];
	}
	else
	{
		printf("出错，“->”左边为终结符\n");
		return 0;
	}

	//获取->右边的字符
	for (b = 3; b <strlen(sen); b++,a++)
	{
		p[i].right[a] = sen[b];
	}
	p[i].right[a] = '\0';
	return 1;
}

//符号匹配，防止重复
int FIND(char* s, char c) {
	int i;
	int tong = -1;
	for (i = 0; i < strlen(s); i++) {
		if (s[i] == c)
		{
			tong++;
		}
	}
	return tong;
}

//获取所有非终结符,可重复
void VN(struct CHUAN* p, int i) {
	if (p[i].left >= 'A' && p[i].left <= 'Z') {
			noend[k] = p[i].left;
			k++;
	}
	noend[k] = '\0';
}

//获取FIRST集合
int FIRST(struct CHUAN* p,int i,int h,int z) {
	
	for (int j = 0; j < 1; j++)
	{
		if (!(p[z].right[j] >= 'A' && p[z].right[j] <= 'Z')) {
			/*
			用于解决形如：
			A->B
			B->a
			B->b
			的情况
			防止覆盖
			*/
			if (strlen(p[h].first) != 0)
			{
				p[h].first[strlen(p[h].first)+1] = '\0';
				p[h].first[strlen(p[h].first)] = p[z].right[j];
			}
			else {
				p[h].first[0] = p[z].right[j];
				p[h].first[1] = '\0';
			}	
			return 1;
		}
		else {
			//i是主函数中的for循环给的，i的值代表输入的第几个句型
			for (int w = i + 1; w < N; w++) {
	//注意每次循环时w都会提前+1
	//z最初0，代表第一个句型，之后随着递归，z变成->左边的符号，w变成z在的句型的下一个句型
				if (p[z].right[0] == p[w].left) {
					FIRST(p, w, h, w);
				}
			}
		}
	}
	return -1;
}

//将已得到的FIRST集合整合，即将右边符号相同的合并
/* 解决形如
	* A->b
	* A->a
	* 这样的句型
	* */
void FQC(struct CHUAN* p) {
	for (int w = 0; w < N - 1; w++)
	{
		for (int r = N-1; r > w; r--)
		{
			if (p[w].left == p[r].left)
			{
				//当左边符号相同时，将前面的写到后面的FIRST集合中
				p[r].first[strlen(p[r].first)+1] = '\0';  //至关重要的一步，先加上结束符，防止长度发生错误
				p[r].first[strlen(p[r].first)] = p[w].first[0];
					//清空字符串
					memset(p[w].first, '\0', sizeof(p[w].first));
			}
		}
	}
}

//求FOLLOW集合
int FOLLOW(struct CHUAN* p,int i) {
	//  添加 '\0'的操作一定要放在前面（重要）
	for (int w = 0; w < strlen(p[i].right); w++)
	{
		//开始符号的FOLLOW集合中天生就有￥符号
		if (i == 0)
		{
			if (FIND(p[i].follow, '$') == -1) {
				p[i].follow[0] = '$';
				p[i].follow[1] = '\0';
			}
		}

		//处理形如A->...Ba这样的句型，将a加入到B的FOLLOW集合中
		if (FIND(noend,p[i].right[w])!= -1&&p[i].right[w+1]!='\0')
		{
			//printf("这里----\n");
			if (!(p[i].right[w + 1] >= 'A' && p[i].right[w + 1] <= 'Z'))
			{
				//printf("这里----%c\n", p[i].right[w + 1]);
				int r = strlen(noend) - 1;
				char ch = p[i].right[w];
				for (; ch != p[r].left; r--);
				if (FIND(p[r].follow, p[i].right[w + 1]) == -1) {
					p[r].follow[strlen(p[r].follow) + 1] = '\0';
					p[r].follow[strlen(p[r].follow)] = p[i].right[w + 1];
				}
				//printf("这里----%s\n", p[r].follow);
				
			}
		}

		/*处理形如A->...B的句型，
		将A的FOLLOW集合中的元素加入到B中
		*/
		if (FIND(noend, p[i].right[w]) != -1&& p[i].right[w + 1] == '\0')
		{//说明p[i].right[w]是终结符，且是右边的最后一个符号
			int r = strlen(noend)-1;
			char ch = p[i].right[w];
			for (; ch != p[r].left; r--);

			for (int x = 0; x < strlen(p[i].follow); x++)
			{
				if (FIND(p[r].follow, p[i].follow[x]) == -1)
				{
					p[r].follow[strlen(p[r].follow) + 1] = '\0';
					p[r].follow[strlen(p[r].follow)] = p[i].follow[x];
				}
			}
		}

		/*处理形如A->...BC这样的句型，
		将C的FIRST集合加入到B的FOLLOW集合中
		如果C->@则将A的FOLLOW集合加到B中
		*/
		if (FIND(noend, p[i].right[w]) != -1 && FIND(noend, p[i].right[w + 1]) != -1 && p[i].right[w + 2] == '\0')
		{
			//与左边的非终结符对应
			char fu = p[i].left;
			int n = strlen(noend)-1;
			for (; fu != p[n].left; n--);

			//与右边的第一个非终结符对应
			char cha = p[i].right[w];
			int m = strlen(noend)-1;
			for (; cha != p[m].left; m--);

			//与右边的第二个非终结符对应
			char ch = p[i].right[w + 1];
			int l = strlen(noend) - 1;
			for (; ch != p[l].left; l--);

			for (int e = 0; e < strlen(p[l].first); e++)
			{
				if (FIND(p[m].follow, p[l].first[e]) == -1 && p[l].first[e]!='@') {
					p[m].follow[strlen(p[m].follow) + 1] = '\0';
					p[m].follow[strlen(p[m].follow)] = p[l].first[e];
				}
			}

			//判断最右边的非终结符的FIRST集合中有没有空集（@）
			if (FIND(p[l].first,'@') != -1)
			{
				for (int x = 0; x < strlen(p[n].follow); x++)
				{
					if (FIND(p[m].follow, p[n].follow[x]) == -1)
					{
						p[m].follow[strlen(p[m].follow) + 1] = '\0';
						p[m].follow[strlen(p[m].follow)] = p[n].follow[x];
					}
				}
			}
		}
	}
	return 0;
 }

//将已得到的FOLLOW集合整合，即将右边符号相同的合并
void FOQC(struct CHUAN* p){

	for (int w = 0; w < N - 1; w++)
	{
		for (int r = N - 1; r > w; r--)
		{
			if (p[w].left == p[r].left)
			{
				for (int b = 0; b < strlen(p[w].follow); p++) {
					//当左边符号相同时，将前面的写到后面的FOLLOW集合中
					p[r].follow[strlen(p[r].follow) + 1] = '\0';  //至关重要的一步，先加上结束符，防止长度发生错误
					p[r].follow[strlen(p[r].follow)] = p[w].follow[b];
				}
				//清空字符串
				memset(p[w].follow, '\0', sizeof(p[w].follow));
				memset(p[w].right, '\0', sizeof(p[w].right));
			}
		}
	}

}
//打印FIRST集合
void PRINTF(struct CHUAN* p) {
	for (int w = 0; w < N; w++)
	{
		if (strlen(p[w].first) != 0) {
			printf("FIRST(%c)={",p[w].left);
			for (int e = 0; e < strlen(p[w].first); e++)
			{
				printf("%c ", p[w].first[e]);
			}
			printf("}\n");
		}
	}
}

//打印FOLLOW集合
void PRI(struct CHUAN* p) {
	for (int w = 0; w < N; w++)
	{
		if (strlen(p[w].first) != 0) {
			printf("FOLLOW(%c)={", p[w].left);
			for (int e = 0; e < strlen(p[w].follow); e++)
			{
				printf("%c ", p[w].follow[e]);
			}
			printf("}\n");
		}
	}
}

//最终打印界面
void PRINT(struct CHUAN* p) {
	printf("\n");
	printf("****************** 实验三  First Fellow*********************************\n");
	printf("非终结符\t\t\t     FIRST\t\t\t        FOLLOW\n");
	for (int w = 0; w < N; w++)
	{
		if (strlen(p[w].first) != 0) {
			printf("  %c\t\t\t\t    {", p[w].left);
			for (int e = 0; e < strlen(p[w].first); e++)
			{
				printf("%c  ", p[w].first[e]);
			}
			printf("}\t\t\t\t");
/*===================================================================*/
			printf("{");
			for (int e = 0; e < strlen(p[w].follow); e++)
			{
				printf("%c ", p[w].follow[e]);
			}
			printf("}\n\n");
		}
	}
}

int main() {
	h = 0;
	z = 0;
	k = 0;     //用于存放所有非终结符时，所用的变量
	struct CHUAN p[length];
	
	do {
		printf("请输入产生式数目\n");
		scanf("%d", &N);
		getchar();
	} while (N <= 0);

	
	printf("请输入句型（用@表示空集）\n");

	//每输入一个句型就获取->左右两边的符号
	for (int i = 0; i < N; i++) {
		scanf("%s",sen);
		if (getLR(p, i, sen) == 0) {
			return 2;
		}

		//获取所有非终结符
		VN(p, i);
	}
    //提前清空用于存放FOLLOW集合的串
	for (int w = 0; w < N; w++)
	{
		memset(p[w].follow, '\0', sizeof(p[w].follow));
	}

	//求FIRST集合
	for (int i = 0; i < N; i++) {
		//提前清空一次串，防止乱码（重要）
		memset(p[h].first, '\0', sizeof(p[h].first));
		FIRST(p, i, h, z);
		h++;
		z++;
	}

	//对FIRST集合去重,必须在FOLLOW集合去重之前
	FQC(p);
   
	//求FOLLOW集合
	do
	{
		b = 0;
		int a[255];
		//记录循环开始前每个句型左边非终结符的FOLLOW长度
		for (int q = 0; q < N; q++)
		{
			a[q] = strlen(p[q].follow);
		}

		for (int i = 0; i < N; i++)
		{
			FOLLOW(p, i);
		}

		//若循环后有句型左边非终结符的FOLLOW长度发生变化，b++
		for (int q = 0; q < N; q++)
		{
			if(strlen(p[q].follow) != a[q]){
				b++;
			}
			//printf("这里=====%d\n", b);
		}
		//printf("这里=====%d\n", b);
	} while (b != 0);
	
	//对FOLLOW集合去重
	FOQC(p);

	//打印FOLLOW集合
    //PRI(p);

    //打印FIRST和FOLLOW集合
	PRINT(p);
	printf("非终结符为%s", noend);
	return 1;
}
