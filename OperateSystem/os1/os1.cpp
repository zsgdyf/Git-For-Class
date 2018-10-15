// os1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>
#include<fstream>
using namespace std;

struct P
{
	char name[10];//进程名
	double ComeTime;//进程到达时间
	double RunTime;//预估运行时间
	int Priority;//进程优先级
	double BeginTime;//进程开始时间
	double FinishTime;//进程完成时间
	double RoundTime;//进程周转时间
	double LRoundTime;//进程带权周转时间
};

void Print(int n,P *p)
{
	double roundTime = 0, lroundTime = 0;
	cout << "进程名\t" << "开始时间\t" << "完成时间\t" << "周转时间\t" << "带权周转时间\t" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << p[i].name <<"\t"
			<< p[i].BeginTime <<"\t\t"
			<< p[i].FinishTime <<"\t\t"
			<< p[i].RoundTime <<"\t\t"
			<< p[i].LRoundTime << endl;
		roundTime = roundTime + p[i].RoundTime;//计算平均周转时间
		lroundTime = lroundTime + p[i].LRoundTime;//计算平均带权周转时间
	}
	cout << "平均周转时间为：" << roundTime / n << endl;
	cout << "平均带权周转时间为：" << lroundTime / n << endl << endl;
}

void FCFS(P *p,int n)
{
	cout << "先来先服务算法：" << endl;
	P temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (p[i].ComeTime > p[j].ComeTime)
			{
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
	p[0].BeginTime = p[0].ComeTime;//开始时间
	for (int i = 1; i < n; i++)
	{
		if (p[i].ComeTime > p[i - 1].BeginTime + p[i - 1].RunTime)
			p[i].BeginTime = p[i].ComeTime;
		else p[i].BeginTime = p[i - 1].BeginTime + p[i - 1].RunTime;
	}
	for (int i = 0; i < n; i++)
	{
		p[i].FinishTime = p[i].BeginTime + p[i].RunTime;//完成时间
		p[i].RoundTime = p[i].FinishTime - p[i].ComeTime;//周转时间
		p[i].LRoundTime = p[i].RoundTime / p[i].RunTime;//带权周转时间
	}
	cout << "调度顺序为：";
	for (int i = 0; i < n-1; i++)
	{
		cout << p[i].name << "->";
	}
	cout << p[n - 1].name << endl;

}

void Priority(P *p, int n)
{
	cout << "优先级法：" << endl;
	P temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (p[i].ComeTime > p[j].ComeTime)
			{
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
	p[0].BeginTime = p[0].ComeTime;//开始时间
	for (int i = 1; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (p[i].Priority > p[j].Priority)
			{
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
	for (int i = 1; i < n; i++)
	{
		if (p[i].ComeTime > p[i - 1].BeginTime + p[i - 1].RunTime)
			p[i].BeginTime = p[i].ComeTime;
		else p[i].BeginTime = p[i - 1].BeginTime + p[i - 1].RunTime;
	}
	for (int i = 0; i < n; i++)
	{
		p[i].FinishTime = p[i].BeginTime + p[i].RunTime;//完成时间
		p[i].RoundTime = p[i].FinishTime - p[i].ComeTime;//周转时间
		p[i].LRoundTime = p[i].RoundTime / p[i].RunTime;//带权周转时间
	}
	cout << "调度顺序为：";
	for (int i = 0; i < n - 1; i++)
	{
		cout << p[i].name << "->";
	}
	cout << p[n - 1].name << endl;

}

void ShortFirst(P *p, int n)
{
	cout << "短作业优先法：" << endl;
	P temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (p[i].ComeTime > p[j].ComeTime)
			{
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
	p[0].BeginTime = p[0].ComeTime;//开始时间
	for (int i = 1; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (p[i].RunTime > p[j].RunTime)
			{
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
	for (int i = 1; i < n; i++)
	{
		if (p[i].ComeTime > p[i - 1].BeginTime + p[i - 1].RunTime)
			p[i].BeginTime = p[i].ComeTime;
		else p[i].BeginTime = p[i - 1].BeginTime + p[i - 1].RunTime;
	}
	for (int i = 0; i < n; i++)
	{
		p[i].FinishTime = p[i].BeginTime + p[i].RunTime;//完成时间
		p[i].RoundTime = p[i].FinishTime - p[i].ComeTime;//周转时间
		p[i].LRoundTime = p[i].RoundTime / p[i].RunTime;//带权周转时间
	}
	cout << "调度顺序为：";
	for (int i = 0; i < n - 1; i++)
	{
		cout << p[i].name << "->";
	}
	cout << p[n - 1].name << endl;
}

int main()
{
	int n, i = 0;
	cout << "请输入进程个数" << endl;
	cin >> n;
	struct P *p = new struct P[n];//动态结构体数组
//从文件输入
	ifstream in("C:\\Users\\sherlock\\Desktop\\os1.txt", ios::in);
	if (!in.is_open())
	{
		cout << "文件打开失败" << endl;
		exit(1);
	}
	while (!in.eof() && i < n)
	{
//依次输入进程名，到达时间，预估执行时间，优先级
		in >> p[i].name >> p[i].ComeTime >> p[i].RunTime >> p[i].Priority;
		i++;
	}
	in.close();
//手动输入
/*	for (i = 0; i < n; i++)
	{
		cout << "依次请输入第" << i + 1 << "个进程的信息（进程名，提交时间，预估执行时间，优先级）" << endl;
		cin >> p[i].name >> p[i].ComeTime >> p[i].RunTime>>p[i].Priority;
	}
	/*
	cout << "请选择一种调度算法：\n 1.先来先服务算法\n 2.优先级法\n 3.短作业优先法" << endl;
	cin >> a;
	switch (a)
		case 1:
		case 2:
		case 3:
	*/
	FCFS(p, n);
	Print(n, p);
	Priority(p, n);
	Print(n, p);
	ShortFirst(p, n);
	Print(n, p);
    return 0;
}
