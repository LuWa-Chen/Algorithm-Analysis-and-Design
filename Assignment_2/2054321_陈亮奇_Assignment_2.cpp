#include<iostream>
#include<vector>
#include<string>
using namespace std;

bool judge(vector<vector<char>>& board, int x, int row, int column)//用于判断棋盘中第row行第column列处是否可以填入数字x，返回值1代表可以填入，0代表无法填入。
{
	for (int i = 0; i < 9; i++)//判断同一行中是否有相同数字
	{
		if (i == column)//排除自身所在格
			continue;
		if (board[row][i] == x + '0')
			return 0;
	}
	for (int i = 0; i < 9; i++)//判断同一列中是否有相同数字
	{
		if (i == row)//排除自身所在格
			continue;
		if (board[i][column] == x + '0')
			return 0;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)//判断所在3x3区域中中是否有相同数字
		{
			if (row / 3 * 3 + i == row && column / 3 * 3 + j == column)//排除自身所在格
				continue;
			if (board[row / 3 * 3 + i][column / 3 * 3 + j] == x + '0')
				return 0;
		}
	}
	return 1;
}

bool dfs(vector<vector<char>>& board)
{
	int flag = 1;//用于判断棋盘是否填满
	char tmp;//用于保存棋盘某位置填数前的状态，便于回溯
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] == ' ')//遍历棋盘，并对空格处进行试错
			{
				flag = 0;//棋盘存在空格
				for (int k = 1; k < 10; k++)//试错及回溯过程
				{
					if (judge(board, k, i, j))//若该处可以填入数字k，则judge函数返回为1
					{

						tmp = board[i][j];
						board[i][j] = k + '0';//int型数字转换为char型存储在board中
						flag = dfs(board);//用于判断填入后棋盘是否填满
						if (flag)//若填满，则依次以1作为返回值打断之前的dfs函数进程
							return flag;
						else//未填满，进行回溯
							board[i][j] = tmp;
							
					}
				}
				if (board[i][j] == ' ')//以此判断后该处棋盘仍为空，表示之前某处k值有误，以0为返回值进行回溯
					return 0;
			}
		}
	}
	return 1;//棋盘已填满，不存在空值
}

void sudokuPuzzleSolver(vector<vector<char>>& board)
{
	dfs(board);//dfs函数以bool为返回值并需要以自身的返回值判断回溯，并从第0行第0列开始遍历棋盘
}

int main()
{
	cout << "请输入大小为9x9的初始数独棋盘，空格代表该处数字为空：" << endl;
	vector<vector<char>> board(9, vector<char>(10, 0));
	char a[10];
	for (int i = 0; i < 9; i++)//读入含空格的初始数独棋盘
	{
		cin.getline(a,10);
		for (int j = 0; j < 10; j++)
			board[i][j] = a[j];
	}

	sudokuPuzzleSolver(board);

	cout << endl << "填入数字后，该数独的解为：" << endl;
	for (int i = 0; i < 9; i++)//输出完成后的数独棋盘
	{
		for (int j = 0; j < 9; j++)
			cout << board[i][j] << " ";
		cout << endl;
	}
	return 0;
}
