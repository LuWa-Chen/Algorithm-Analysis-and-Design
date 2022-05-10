#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
	vector<int> coins;
	int amount, tmp = 0, num = 0;
	cout << "����������Ӳ����ֵ����Ϊ������������-1��������" << endl;
	while (1)
	{
		cin >> tmp;
		if (tmp > 0)				//���û�����Ϊ����������������
		{ 
			coins.push_back(tmp);
			num++;
		}
		else if (num > 0)
			break;
	}
	cout << "������Ŀ����" << endl;
	cin >> amount;
	sort(coins.begin(), coins.end());		 //���û������Ӳ����ֵ������������
	if (amount < coins[0])					 //���û������Ŀ����С����СӲ����ֵ�򲻴��ںϷ����������0����������
	{
		if (amount == 0)
			cout << "����Ӳ����Ϊ 0" << endl;
		else
			cout << "-1(�����ںϷ�����)" << endl;
		return 0;
	}
	int* count = new int[amount + 1];		  //��̬��������
	for (int i = 0; i <= amount; i++)	 	  //�����ʼ��
			count[i] = 0;

	for (int j = 0; j < num; j++)
	{
		if (coins[j] > amount)
			break;
		count[coins[j]] = 1;				  //ֻ�ö�Ӧ��ֵ��Ӳ�Ҽ��ɴճ�Ŀ����
		for (int i = coins[j]; i <= amount; i++)//��̬�滮��ȡ���з���Ӳ������ʹ��һ��j����ֵ��Ӳ�Ҷ�ӦӲ�������Ľ�Сֵ
			if (count[i - coins[j]] > 0 && ((count[i - coins[j]] + 1 < count[i]) || count[i] == 0))   
				count[i] = count[i - coins[j]] + 1;
	}
	if (count[amount] == 0)
		cout << "-1(�����ںϷ�����)" << endl;
	else
		cout << "����Ӳ����Ϊ " << count[amount] << endl;
	delete[]count;
	return 0;
}
