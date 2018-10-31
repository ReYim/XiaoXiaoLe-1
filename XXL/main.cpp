/*ʵ�����������Ž�
�㷨˼�룺
�������+���ݼ�֦

���ݽṹ��
����map<string, prestate>��¼״̬���������
1. string = �ַ����� + ��һ��������������Լ������ķ������������γ�Ψһ��key��
2. state = ǰһ��״̬��string �� ��ǰ�õ��ķ�������һ���ṹ���ʾ���ɡ�

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
#include <map> 
#include <algorithm> //��������
#include <time.h>

using namespace std;


//---------------������������--------------------//
const int ROW = 8;        //��
const int COLUMN = 4;     //��
int max_score;            //���÷�
string max_str;           //���÷ֵ��ַ���

typedef struct state   
{ 
	int current_score;   //��ǰ�÷�
	int K;               //��ǰ����
	int i, j;            //��ǰ�ɽ���������
	int dir;             //��ǰ��������
	string previous;     //��¼��һ��״̬����
}state;

map<string, state> mymap;   //map�洢���в��ظ����ż�¼,����ڵݹ��з�������ͬ��key������state

//������������һ�α������ͨ��
void DFS(string pre_key);                       //�����пɽ�������ȱ���
int is_clear(string& now_key, int i0, int j0);  //��p(i0,j0)������ȥ����
void update_key(string& now_key);               //����ȥ��ľ�����и���
void print(string str);                         //�������
void str_to_mat(string str, char mat[][COLUMN]); 
void mat_to_str(char mat[][COLUMN], string & str);
int get_point(int count);                       //������ȥ�ĸ����ж�һ���õ��ķ���������ͳ����һ����׬��
bool is_exchange(string pre_key, int i, int j, int dir);  //�ж�p(i,j)�Ƿ������dir���򽻻�
void clear(string pre_key, int i0, int j0, int dir); //���ĺ������ۺ����Ϻ���

													 
//---------------------------���岿��--------------------------------------//
void print(string str) {        //���״̬����
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++)
		{
			cout << str[i*COLUMN+j] << ' ';
		}
		cout << endl;
	}
}

void str_to_mat(string str, char mat[][COLUMN]) {
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			mat[i][j] = str[i*COLUMN + j];
		}
	}
}

void mat_to_str(char mat[][COLUMN], string &str) {
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			str[i*COLUMN + j] = mat[i][j];
		}
	}
}

int get_point(int count) {
	if (count == 3) return 1;
	if (count == 4) return 4;
	if (count == 5) return 10;
	return 0;
}

int duta(string& now_key) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j = j ++) {
			if (now_key[i*COLUMN+j] != '0' && is_clear(now_key, i, j)) {
				update_key(now_key);
				return 1;
			}
		}
	}
	return 0;
}

//��������,ֻ�����������������Ϸ��ķ���������Ĳ���
int is_clear(string& now_key, int i0, int j0) {
	//˼·�������������������˵
	int count = 1;
	int score = 0;
	char mat[ROW][COLUMN];
	str_to_mat(now_key, mat);
	char p = mat[i0][j0];

	int j = j0+1;
	while (j < COLUMN)
	{
		if (mat[i0][j] == p)
		{
			count++;
			j++;
		}
		else
		{
			break;
		}
	}
	j = j0 - 1;
	while (j >= 0) {
		if (mat[i0][j] == p)
		{
			count++;
			j--;
		}
		else
		{
			break;
		}
	}

	if (count > 2)
	{
		mat[i0][j0] = '0';
		j = j0 + 1;
		while (j < COLUMN && mat[i0][j] == p)
		{
			mat[i0][j] = '0';
			j++;
		}
		j = j0 - 1;
		while (j >=0 && mat[i0][j] == p)
		{
			mat[i0][j] = '0';
			j--;
		}
	}
	score += get_point(count);
	//�ж��е�
	int i = i0 + 1;
	count = 1;
	while (i<ROW)
	{
		if (mat[i][j0] == p)
		{
			count++;
			i++;
		}
		else {
			break;
		}
	}
	i = i0 - 1;
	while (i >= 0) {
		if (mat[i][j0] == p)
		{
			count++;
			i--;
		}
		else {
			break;
		}
	}
	if (count > 2)
	{
		mat[i0][j0] = '0';
		i = i0 + 1;
		while (i < ROW && mat[i][j0] == p)
		{
			mat[i][j0] = '0';
			i++;
		}
		i = i0 - 1;
		while (i >=0 && now_key[i*COLUMN + j0] == now_key[i0*COLUMN + j0])
		{
			mat[i][j0] = '0';
			i--;
		}
	}
	score += get_point(count);
	if (score > 0)
	{
		mat_to_str(mat, now_key);
	}
	return score;
}

void update_key(string& now_key) {  //���м���ȥ�Ĳ���������ķ�������
	for (int i = 1; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++)
		{
			if (now_key[i*COLUMN + j] == '0') {
				int k = i;
				while (k > 0)
				{
					swap(now_key[k*COLUMN + j], now_key[(k - 1)*COLUMN + j]);
					k--;
				}
			}
		}
	}
}

//����������������ԣ���ȵݹ飬������ȥ��ļ�¼���浽map��ͷ��
void clear(string pre_key, int i0, int j0, int dir) {  //pre_key���βΣ���Ӱ����һ��״̬
	//��¼״̬
	state pre_state = mymap[pre_key];
	state now_state;
	now_state.previous = pre_key;
	now_state.current_score = pre_state.current_score;
	now_state.K = pre_state.K + 1;
	now_state.i = i0;
	now_state.j = j0;
	now_state.dir = dir;


	//----------��ʼ��ȥ����-----------------//
	string now_key = pre_key;  //�µ�״̬�ַ�����ʼ��Ϊ��һ��״̬

	//�Ƚ��������������
	int i1 = i0;
	int j1 = j0; //��¼�ͣ�i0,j0�������ĵ�
	if (dir == 1) { 
		j1 = j0 + 1;
		swap(now_key[i0*COLUMN + j0], now_key[i1*COLUMN + j1]); 
	}
	if (dir == 2) {
		i1 = i0 + 1;
		swap(now_key[i0*COLUMN + j0], now_key[i1*COLUMN + j1]);
	}
	//��¼��ȥ�����ڵ㸽��������õ��ķ�����
	int score = is_clear(now_key,i0,j0);   //�����now_key�������ʵ�Σ����Ի�ı�
	score += is_clear(now_key, i1, j1);
	if (score > 0) {  //˵����һ����Ч�����㣬����map��������һ��DFS����
		//���н��пյĲ���������ķ���ѹ����
		update_key(now_key);
		score += duta(now_key);
		now_state.current_score = now_state.current_score + score;
		if (max_score < now_state.current_score)
		{
			max_score = now_state.current_score;
			max_str = now_key;
		}
		if (mymap.count(now_key) == 0)  //���û�иü�¼������ü�¼,���еݹ�
		{
			mymap[now_key] = now_state;
			DFS(now_key);
		}
		else  if (mymap[now_key].current_score < now_state.current_score) { //����иü�¼�����ǱȽ�С�����²��ݹ�
			mymap[now_key] = now_state;
			DFS(now_key);
		}
	}
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
		return true;
	}
	//�ж�p(i,j)�ɷ����½���
	if (dir == 2
		&& i+1 < ROW
		&& pre_key[i*COLUMN+j] != '0' 
		&& pre_key[(1+i)*COLUMN + j] != '0'
		&& pre_key[i*COLUMN + j] != pre_key[(1 + i)*COLUMN + j])
	{
		return true;
	}
	return false;
}

void DFS(string pre_key) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			if (is_exchange(pre_key, i, j, 1)) {  //�ж��Ƿ�������ҽ���
				clear(pre_key, i, j, 1);          //��ȥ���������������ȥ�ͽ������µݹ�
			}
			if (is_exchange(pre_key, i, j, 2)) {  //�ж��Ƿ�������½���
				clear(pre_key, i, j, 2);          //��ȥ���������н�����ȥ������ȱ���
			}
		}
	}
}

int main() {
	string str0 = "33433233243413433311343314431232"; //������ַ�����ʾ 
	max_score = 0;                //��ʼ�����÷�
	state state0;                 //��ʼ״̬
	state0.previous = "";         //��ǰ״̬
	state0.current_score = 0;     //��ʼ����Ϊ0
	state0.K = 0;                 //��ʼ����Ϊ0
	state0.i = -1;                //-1�����ʼ��
	state0.j = -1;                
	state0.dir = 0;               //0�����޷���
	mymap[str0] = state0;         //map�����¼ԭʼ�ľ���
	cout << "-----------------------��ʼ����" << endl;
	print(str0);
	cout << "-----------------------���" << endl;
	clock_t start = clock();
	DFS(str0);
	clock_t end = clock();
	cout << "����ʱ��Ϊ��" << (double)(end - start) << "ms" << endl;
	cout << "�ܹ���"<< mymap.size()<< "���ڵ�" <<endl;
	cout << "��߷���: "<< max_score << endl;
	cout << "������ " << mymap[max_str].K << " ������"<<endl;
	cout << "-----------------------���վ���Ϊ" << endl;
	print(max_str);
	getchar();
	return 0;
}
