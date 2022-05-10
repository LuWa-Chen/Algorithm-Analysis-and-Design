#include<iostream>
#include<vector>
#include<string>
using namespace std;

bool judge(vector<vector<char>>& board, int x, int row, int column)//�����ж������е�row�е�column�д��Ƿ������������x������ֵ1����������룬0�����޷����롣
{
	for (int i = 0; i < 9; i++)//�ж�ͬһ�����Ƿ�����ͬ����
	{
		if (i == column)//�ų��������ڸ�
			continue;
		if (board[row][i] == x + '0')
			return 0;
	}
	for (int i = 0; i < 9; i++)//�ж�ͬһ�����Ƿ�����ͬ����
	{
		if (i == row)//�ų��������ڸ�
			continue;
		if (board[i][column] == x + '0')
			return 0;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)//�ж�����3x3���������Ƿ�����ͬ����
		{
			if (row / 3 * 3 + i == row && column / 3 * 3 + j == column)//�ų��������ڸ�
				continue;
			if (board[row / 3 * 3 + i][column / 3 * 3 + j] == x + '0')
				return 0;
		}
	}
	return 1;
}

bool dfs(vector<vector<char>>& board)
{
	int flag = 1;//�����ж������Ƿ�����
	char tmp;//���ڱ�������ĳλ������ǰ��״̬�����ڻ���
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] == ' ')//�������̣����Կո񴦽����Դ�
			{
				flag = 0;//���̴��ڿո�
				for (int k = 1; k < 10; k++)//�Դ����ݹ���
				{
					if (judge(board, k, i, j))//���ô�������������k����judge��������Ϊ1
					{

						tmp = board[i][j];
						board[i][j] = k + '0';//int������ת��Ϊchar�ʹ洢��board��
						flag = dfs(board);//�����ж�����������Ƿ�����
						if (flag)//����������������1��Ϊ����ֵ���֮ǰ��dfs��������
							return flag;
						else//δ���������л���
							board[i][j] = tmp;
							
					}
				}
				if (board[i][j] == ' ')//�Դ��жϺ�ô�������Ϊ�գ���ʾ֮ǰĳ��kֵ������0Ϊ����ֵ���л���
					return 0;
			}
		}
	}
	return 1;//�����������������ڿ�ֵ
}

void sudokuPuzzleSolver(vector<vector<char>>& board)
{
	dfs(board);//dfs������boolΪ����ֵ����Ҫ������ķ���ֵ�жϻ��ݣ����ӵ�0�е�0�п�ʼ��������
}

int main()
{
	cout << "�������СΪ9x9�ĳ�ʼ�������̣��ո����ô�����Ϊ�գ�" << endl;
	vector<vector<char>> board(9, vector<char>(10, 0));
	char a[10];
	for (int i = 0; i < 9; i++)//���뺬�ո�ĳ�ʼ��������
	{
		cin.getline(a,10);
		for (int j = 0; j < 10; j++)
			board[i][j] = a[j];
	}

	sudokuPuzzleSolver(board);

	cout << endl << "�������ֺ󣬸������Ľ�Ϊ��" << endl;
	for (int i = 0; i < 9; i++)//�����ɺ����������
	{
		for (int j = 0; j < 9; j++)
			cout << board[i][j] << " ";
		cout << endl;
	}
	return 0;
}
