/*ʵ�����������Ž�
�㷨˼�룺
�������+���ݼ�֦

���ݽṹ��
����map<string, prestate>��¼״̬���������
1. string = �ַ����� + ��һ��������������Լ������ķ������������γ�Ψһ��key��
2. perstate = ǰһ��״̬��string �� ��ǰ�õ��ķ�������һ���ṹ���ʾ���ɡ�

�㷨���裺
1. ÿ�εݹ鶼�ҳ��Ǹ�ʱ���������пɽ����㣬����ÿ������������
2. �ݹ��������������
	��û�пɽ����㣬����
	�ڼ�֦���鿴map�Ƿ�����ͬ״̬���������ߵģ�����и��ߵģ������ݹ���л���
	  �����滻�������͵Ľ�����һ���ݹ顣
3. �ж϶�����Χ�Ƿ��п����γ���ȥ������������ͨ���ж����пɷ���ȥ�������пɷ���ȥ
4. ÿ����ȥ֮���Ϸ��ķ�������������ʱ������֮��Ҫ��һ���ж��Ƿ�����Զ�������ֱ��ȷ�ϲ�������
5. ������һ�εݹ�֮ǰҪ�ѵ�ǰ״̬��¼��map�ϡ�

�Ż�ϸ�ڣ�
1. �ַ�0����ʾ�գ����ܽ�������ͬ��ɫ���������壬����������ȥ����Ļ����ܽ���
2. ������������������洢�ɽ����㣬ͨ����ɾ���Ƶݹ�

*/

#include <iostream>   
#include <string>
#include <list>
#include <map>
#include<algorithm>//sort����������ͷ�ļ�

using namespace std;

const int ROW = 8;        //��
const int COLUMN = 4;     //��

typedef struct state   
{ 
	int current_score;   //��ǰ����
	string previous;     //��¼��һ��״̬���� + �ͽ����ĵ�
}state;

typedef struct point
{
	int i, j; //����
	int dir;   //����
}point;

map<string, state> mymap;   //map�洢���в��ظ����ż�¼,����ڵݹ��з�������ͬ��key������state

void str_to_mat(string str, char mat[][COLUMN]) {    //�ַ���ת��ά�ַ�����
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			mat[i][j] = str[i*COLUMN + j];
		}
	}
}

void mat_to_str(string str, char mat[][COLUMN]) {    //��ά�ַ�����ת�ַ���
	for (int i = 0; i < ROW; i++)
	{
		for (int i = 0; i < COLUMN; i++)
		{
			for (int j = 0; j < COLUMN; j++)
			{
				str[i*COLUMN + j] = mat[i][j];
			}
		}
	}
}

void print(string str) {        //���״̬����
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++)
		{
			cout << str[i*COLUMN+j] << ' ';
		}
		cout << endl;
	}
}

//�жϽ�����ĵ�ɷ�������������ԣ����������ķ�����������У������㣬������ȥ��ļ�¼���浽map��ͷ��
int clear(string pre_key, int i, int j) {
	int score;
	return score;
}

//�ж�p(i,j)�ܷ���dir���򽻻�
bool is_exchange(string pre_key, int i, int j, int dir) {
	//�ж�p(i,j)�ɷ����ҽ���
	if (dir == 1 
		&& j+1 < COLUMN 
		&& pre_key[i*COLUMN+j] != '0' 
		&& pre_key[i*COLUMN +j+1] != '0' 
		&& pre_key[i*COLUMN + j] != pre_key[i*COLUMN + j+1]) 
	{

	}
	//�ж�p(i,j)�ɷ����½���
	if (dir == 2
		&& i+1 < ROW
		&& pre_key[i*COLUMN+j] != '0' 
		&& pre_key[(1+1)*COLUMN + j] != '0'
		&& pre_key[i*COLUMN + j] != pre_key[(1 + 1)*COLUMN + j])
	{

	}
	return false;
}

void DFS(string pre_key) {
	list<point> list;  //��¼���пɽ����Ľڵ�
	string now_key;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			if (is_exchange(pre_key, i, j, 1)) {  //�ж��Ƿ�������ҽ���
				now_key = pre_key;   //��ʱ�ַ���now_key��������
				int score = clear(now_key, i, j);
				if (score) {       //�ж��ܷ���ȥ����ȥ
					state now_state;
					now_state.current_score = score;
					now_state.previous = pre_key;

				}
			}
			if (is_exchange(pre_key, i, j, 2)) {  //�ж��Ƿ�������½���

			}
		}
	}
}

int main() {
	//�ַ��������λ�� i+j+��������000��ʾ��ʼ״̬
	string str0 = "33433233243413433311343314431232000"; //������ַ�����ʾ
	state mat;
	mat.previous = "";
	mat.current_score = 0;
	mymap[str0] = mat;  //map�����¼��ԭʼ�ľ���
	print(str0);
	getchar();
	return 0;
}
