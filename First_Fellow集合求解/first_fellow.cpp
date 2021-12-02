#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define length 90

int b;  //������FOLLOW����
int k;  //���ڴ�����з��ս��ʱ�����õı���
int N;  //���ڴ�Ų���ʽ��Ŀ
char sen[255];   //���ڴ������ľ���
char noend[length];  //���ڴ�ŷ��ս��
char end[length];   //���ڴ���ս��
int h,z;  //������FIRST����ʱ����
struct CHUAN
{
	char left;   //����->��ߵķ��ս��
	char right[length];    //����->�ұߵķ���
	char first[length];    //����FIRST�����е�Ԫ��
	char follow[length];    //����FOLLOW�����е�Ԫ��
};


//��ȡ->�������ߵ��ַ�
int getLR(struct CHUAN *p,int i,char *sen) {
	int a = 0;
	int b;

	//��ȡ��ߵķ��ս��
	if (sen[0]>='A' && sen[0]<='Z')
	{
		p[i].left = sen[0];
	}
	else
	{
		printf("������->�����Ϊ�ս��\n");
		return 0;
	}

	//��ȡ->�ұߵ��ַ�
	for (b = 3; b <strlen(sen); b++,a++)
	{
		p[i].right[a] = sen[b];
	}
	p[i].right[a] = '\0';
	return 1;
}

//����ƥ�䣬��ֹ�ظ�
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

//��ȡ���з��ս��,���ظ�
void VN(struct CHUAN* p, int i) {
	if (p[i].left >= 'A' && p[i].left <= 'Z') {
			noend[k] = p[i].left;
			k++;
	}
	noend[k] = '\0';
}

//��ȡFIRST����
int FIRST(struct CHUAN* p,int i,int h,int z) {
	
	for (int j = 0; j < 1; j++)
	{
		if (!(p[z].right[j] >= 'A' && p[z].right[j] <= 'Z')) {
			/*
			���ڽ�����磺
			A->B
			B->a
			B->b
			�����
			��ֹ����
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
			//i���������е�forѭ�����ģ�i��ֵ��������ĵڼ�������
			for (int w = i + 1; w < N; w++) {
	//ע��ÿ��ѭ��ʱw������ǰ+1
	//z���0�������һ�����ͣ�֮�����ŵݹ飬z���->��ߵķ��ţ�w���z�ڵľ��͵���һ������
				if (p[z].right[0] == p[w].left) {
					FIRST(p, w, h, w);
				}
			}
		}
	}
	return -1;
}

//���ѵõ���FIRST�������ϣ������ұ߷�����ͬ�ĺϲ�
/* �������
	* A->b
	* A->a
	* �����ľ���
	* */
void FQC(struct CHUAN* p) {
	for (int w = 0; w < N - 1; w++)
	{
		for (int r = N-1; r > w; r--)
		{
			if (p[w].left == p[r].left)
			{
				//����߷�����ͬʱ����ǰ���д�������FIRST������
				p[r].first[strlen(p[r].first)+1] = '\0';  //������Ҫ��һ�����ȼ��Ͻ���������ֹ���ȷ�������
				p[r].first[strlen(p[r].first)] = p[w].first[0];
					//����ַ���
					memset(p[w].first, '\0', sizeof(p[w].first));
			}
		}
	}
}

//��FOLLOW����
int FOLLOW(struct CHUAN* p,int i) {
	//  ��� '\0'�Ĳ���һ��Ҫ����ǰ�棨��Ҫ��
	for (int w = 0; w < strlen(p[i].right); w++)
	{
		//��ʼ���ŵ�FOLLOW�������������У�����
		if (i == 0)
		{
			if (FIND(p[i].follow, '$') == -1) {
				p[i].follow[0] = '$';
				p[i].follow[1] = '\0';
			}
		}

		//��������A->...Ba�����ľ��ͣ���a���뵽B��FOLLOW������
		if (FIND(noend,p[i].right[w])!= -1&&p[i].right[w+1]!='\0')
		{
			//printf("����----\n");
			if (!(p[i].right[w + 1] >= 'A' && p[i].right[w + 1] <= 'Z'))
			{
				//printf("����----%c\n", p[i].right[w + 1]);
				int r = strlen(noend) - 1;
				char ch = p[i].right[w];
				for (; ch != p[r].left; r--);
				if (FIND(p[r].follow, p[i].right[w + 1]) == -1) {
					p[r].follow[strlen(p[r].follow) + 1] = '\0';
					p[r].follow[strlen(p[r].follow)] = p[i].right[w + 1];
				}
				//printf("����----%s\n", p[r].follow);
				
			}
		}

		/*��������A->...B�ľ��ͣ�
		��A��FOLLOW�����е�Ԫ�ؼ��뵽B��
		*/
		if (FIND(noend, p[i].right[w]) != -1&& p[i].right[w + 1] == '\0')
		{//˵��p[i].right[w]���ս���������ұߵ����һ������
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

		/*��������A->...BC�����ľ��ͣ�
		��C��FIRST���ϼ��뵽B��FOLLOW������
		���C->@��A��FOLLOW���ϼӵ�B��
		*/
		if (FIND(noend, p[i].right[w]) != -1 && FIND(noend, p[i].right[w + 1]) != -1 && p[i].right[w + 2] == '\0')
		{
			//����ߵķ��ս����Ӧ
			char fu = p[i].left;
			int n = strlen(noend)-1;
			for (; fu != p[n].left; n--);

			//���ұߵĵ�һ�����ս����Ӧ
			char cha = p[i].right[w];
			int m = strlen(noend)-1;
			for (; cha != p[m].left; m--);

			//���ұߵĵڶ������ս����Ӧ
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

			//�ж����ұߵķ��ս����FIRST��������û�пռ���@��
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

//���ѵõ���FOLLOW�������ϣ������ұ߷�����ͬ�ĺϲ�
void FOQC(struct CHUAN* p){

	for (int w = 0; w < N - 1; w++)
	{
		for (int r = N - 1; r > w; r--)
		{
			if (p[w].left == p[r].left)
			{
				for (int b = 0; b < strlen(p[w].follow); p++) {
					//����߷�����ͬʱ����ǰ���д�������FOLLOW������
					p[r].follow[strlen(p[r].follow) + 1] = '\0';  //������Ҫ��һ�����ȼ��Ͻ���������ֹ���ȷ�������
					p[r].follow[strlen(p[r].follow)] = p[w].follow[b];
				}
				//����ַ���
				memset(p[w].follow, '\0', sizeof(p[w].follow));
				memset(p[w].right, '\0', sizeof(p[w].right));
			}
		}
	}

}
//��ӡFIRST����
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

//��ӡFOLLOW����
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

//���մ�ӡ����
void PRINT(struct CHUAN* p) {
	printf("\n");
	printf("****************** ʵ����  First Fellow*********************************\n");
	printf("���ս��\t\t\t     FIRST\t\t\t        FOLLOW\n");
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
	k = 0;     //���ڴ�����з��ս��ʱ�����õı���
	struct CHUAN p[length];
	
	do {
		printf("���������ʽ��Ŀ\n");
		scanf("%d", &N);
		getchar();
	} while (N <= 0);

	
	printf("��������ͣ���@��ʾ�ռ���\n");

	//ÿ����һ�����;ͻ�ȡ->�������ߵķ���
	for (int i = 0; i < N; i++) {
		scanf("%s",sen);
		if (getLR(p, i, sen) == 0) {
			return 2;
		}

		//��ȡ���з��ս��
		VN(p, i);
	}
    //��ǰ������ڴ��FOLLOW���ϵĴ�
	for (int w = 0; w < N; w++)
	{
		memset(p[w].follow, '\0', sizeof(p[w].follow));
	}

	//��FIRST����
	for (int i = 0; i < N; i++) {
		//��ǰ���һ�δ�����ֹ���루��Ҫ��
		memset(p[h].first, '\0', sizeof(p[h].first));
		FIRST(p, i, h, z);
		h++;
		z++;
	}

	//��FIRST����ȥ��,������FOLLOW����ȥ��֮ǰ
	FQC(p);
   
	//��FOLLOW����
	do
	{
		b = 0;
		int a[255];
		//��¼ѭ����ʼǰÿ��������߷��ս����FOLLOW����
		for (int q = 0; q < N; q++)
		{
			a[q] = strlen(p[q].follow);
		}

		for (int i = 0; i < N; i++)
		{
			FOLLOW(p, i);
		}

		//��ѭ�����о�����߷��ս����FOLLOW���ȷ����仯��b++
		for (int q = 0; q < N; q++)
		{
			if(strlen(p[q].follow) != a[q]){
				b++;
			}
			//printf("����=====%d\n", b);
		}
		//printf("����=====%d\n", b);
	} while (b != 0);
	
	//��FOLLOW����ȥ��
	FOQC(p);

	//��ӡFOLLOW����
    //PRI(p);

    //��ӡFIRST��FOLLOW����
	PRINT(p);
	printf("���ս��Ϊ%s", noend);
	return 1;
}
