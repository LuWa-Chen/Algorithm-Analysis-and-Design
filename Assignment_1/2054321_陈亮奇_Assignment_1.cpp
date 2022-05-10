#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
	vector<int> coins;
	int amount, tmp = 0, num = 0;
	cout << "请输入若干硬币面值（需为正整数），以-1结束输入" << endl;
	while (1)
	{
		cin >> tmp;
		if (tmp > 0)				//若用户输入为非正数均结束读入
		{ 
			coins.push_back(tmp);
			num++;
		}
		else if (num > 0)
			break;
	}
	cout << "请输入目标金额" << endl;
	cin >> amount;
	sort(coins.begin(), coins.end());		 //对用户输入的硬币面值进行升序排序
	if (amount < coins[0])					 //若用户输入的目标金额小于最小硬币面值则不存在合法方案，输出0并结束程序
	{
		if (amount == 0)
			cout << "最少硬币数为 0" << endl;
		else
			cout << "-1(不存在合法方案)" << endl;
		return 0;
	}
	int* count = new int[amount + 1];		  //动态分配数组
	for (int i = 0; i <= amount; i++)	 	  //数组初始化
			count[i] = 0;

	for (int j = 0; j < num; j++)
	{
		if (coins[j] > amount)
			break;
		count[coins[j]] = 1;				  //只用对应面值的硬币即可凑成目标金额
		for (int i = coins[j]; i <= amount; i++)//动态规划：取现有方案硬币数与使用一次j类面值的硬币对应硬币数量的较小值
			if (count[i - coins[j]] > 0 && ((count[i - coins[j]] + 1 < count[i]) || count[i] == 0))   
				count[i] = count[i - coins[j]] + 1;
	}
	if (count[amount] == 0)
		cout << "-1(不存在合法方案)" << endl;
	else
		cout << "最少硬币数为 " << count[amount] << endl;
	delete[]count;
	return 0;
}
