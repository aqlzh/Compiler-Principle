/**
ͨ���ڽӾ������ʽ����ȷ���������Զ���DFA,
�ж�������ַ�������Ϸ�

����˼��
1.״̬ת��������Ӧ���ַ�Ϊ������ô�죿
2.NFA�޷����ʵ�֣��ǲ��Ƕ�����ת��ΪDFA֮����ܱ��ʵ��?

*/
#include <iostream>
#include <string>
#include <set>
#include <map>
#define N 10
using namespace std;

map<char, int> alpha2idx;

int Map[N][N];

set<char> alphaSet;//������ĸ���洢���з��ŵļ��ϣ����ڽ�����ӳ�䵽����

int main()
{
    int n;//��ʾ��ת�������ĸ���
    int s_begin, s_end;//��ʼ״̬�ͽ���״̬
    int s0, s1;
    string str;//��ʶ����ַ���
    cin >> n;
    cin >> s_begin >> s_end;
    char alpha;
    int idx4alpha = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            Map[i][j] = -1;//��ʼ���ڽӾ���

    for (int i = 0; i < n; i++) {
        cin >> s0 >> alpha >> s1;
        if (alphaSet.find(alpha) == alphaSet.end()) {//�жϵ�ǰ�ַ��Ƿ��Ѿ�ת��Ϊ��Ӧ������
            alpha2idx[alpha] = idx4alpha;
            alphaSet.insert(alpha);
            idx4alpha++;
        }
        Map[s0][alpha2idx[alpha]] = s1;//����ת������
    }

    //��ӡ�ڽӾ���
//    for(int i=0;i<N;i++){
//        for(int j=0;j<idx4alpha;j++){
//            cout<<Map[i][j]<<" ";
//        }
//        cout<<endl;
//    }

    while (cin >> str) {
        int curState = s_begin;//��ʼ״̬
        cout << curState << "->";
        int len = str.size();
        bool flag = true;
        for (int i = 0; i < len; i++) {
            if (alphaSet.find(str[i]) == alphaSet.end()) {//�жϵ�ǰ��ĸ�Ƿ�����ĸ������
                flag = false;
                break;
            }
            else {
                i != len - 1 ? cout << Map[curState][alpha2idx[str[i]]] << "->" : cout << Map[curState][alpha2idx[str[i]]];

                if (Map[curState][alpha2idx[str[i]]] != -1) {//ת����������
                    curState = Map[curState][alpha2idx[str[i]]];//���µ�ǰ״̬
                }
                else {//�����ڶ�Ӧ��ת����ϵ
                    flag = false;
                    break;
                }
            }
        }
        cout << endl;
        //�ж�����Ƿ�ﵽ�˽���״̬
        if (curState == s_end && flag) {
            cout << "True" << endl;
        }
        else {
            cout << "False" << endl;
        }

    }

    return 0;
}
/*
9
0 4
0 a 1
0 b 22
1 a 1
1 b 3
2 b 2
2 a 1
3 a 1
3 b 4
4 a 1
aaaaaaabb
*/

