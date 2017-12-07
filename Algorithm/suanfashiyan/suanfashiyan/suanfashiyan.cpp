// suanfashiyan.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
const int N = 5;

void TSolve(int money, int value[])
{
	cout << "---------------------------------贪心算法" << endl;
	int num = 0;
	for (int i = N-1; i >= 0; i--)
	{
		int count = money / value[i];
		money = money - count*value[i];
		num = num + count;
		cout << value[i] << "元\t" << count << "个" << endl;
	}
	cout << "总共需要的硬币个数为：" << num << "个" << endl;
}

void QSolve(int money, int value[])
{
	cout << "-----------------------------------穷举法" << endl;
	int MaxNum[N];
	for (int i = 0; i < N; i++)
	{
		MaxNum[i] = money / value[i] + 1;
	}
	for (int i = 0; i < MaxNum[0]; i++)
	{
		for (int j = 0; j < MaxNum[1]; j++)
		{
			for (int k = 0; k < MaxNum[2]; k++)
			{
				for (int m = 0; m < MaxNum[3]; m++)
				{
					for (int n = 0; n < MaxNum[4]; n++)
					{
						if (i*value[0] + j*value[1] + k*value[2] + m*value[3] + n*value[4] == money)
						{
							/*
							cout << value[0] << "元\t" << i << "个" << endl;
							cout << value[1] << "元\t" << j << "个" << endl;
							cout << value[2] << "元\t" << k << "个" << endl;
							cout << value[3] << "元\t" << m << "个" << endl;
							cout << value[4] << "元\t" << n << "个" << endl;
							*/
							cout << "总共需要的硬币个数为：" << i + j + k + m << endl;
							cout << "----------------------" << endl;
						}
					}
				}
			}
		}
	}
}

void DSolve(int money, int value[])
{
	cout << "---------------------------------动态规划" << endl;
	int *CoinNum = new int[money + 1];
	int *UsedValue = new int[money + 1];
	CoinNum[0] = 0;
	for (int i = 1; i < money + 1; i++)
	{
		int MinNum = i;
		int UsedCoin = 0;
		for (int j = 0; j < N; j++)
		{
			if (i >= value[j])
			{
				if (CoinNum[i - value[j]] + 1 < MinNum)
				{
					MinNum = CoinNum[i - value[j]] + 1;
					UsedCoin = value[j];
				}
			}
		}
		CoinNum[i] = MinNum;
		UsedValue[i] = UsedCoin;
	}
	if (UsedValue[money] == 0)
	{
		cout << "找不开" << endl;
	}
	else
	{
		cout << "总共需要的硬币个数为：" << CoinNum[money] << "个" << endl;
		cout << "硬币面值分别为:";
		while (money>0)
		{
			cout << UsedValue[money] << "元  ";
			money = money - UsedValue[money];
		}
		cout << endl;
	}
}


int main()
{
	int value[N] = { 1,3,7,15,31 };
	int money;
	cout << "请输入需找零的面值：";
	cin >> money;
	TSolve(money, value);
	DSolve(money, value);
	QSolve(money, value);
    return 0;
}

