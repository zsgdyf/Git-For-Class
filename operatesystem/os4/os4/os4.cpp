// os4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>  
using namespace std;

struct Avail
{
	int Number;
	int Length;
	int BeginAddress;
	bool Used;
};
struct Busy
{
	char Name;
	int Length;
	int BeginAddress;
};

void Print(Avail *avail, Busy *busy,int n,int m)
{
	cout << "-----------------------进程在内存存储情况" << endl;
	cout << "进程名\t" << "进程起始地址\t" << "进程大小" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << busy[i].Name << "\t" << busy[i].BeginAddress << "\t\t" << busy[i].Length << endl;
	}
	cout << "-----------------------内存空间可用表" << endl;
	cout << "块号\t" << "起始地址\t" << "分区长度" << endl;
	for (int i = 0; i < m; i++)
	{
		cout << avail[i].Number << "\t" << avail[i].BeginAddress << "\t\t" << avail[i].Length << endl;
	}
}

void Recover(Avail *avail,Busy *busy,int m,int n)
{
	char name;
	int key;
	cout << "请输入需要回收的进程名:";
	cin >> name;
	struct Avail *Navail = new struct Avail[m + 1];
	for (int i = 0; i < m; i++)
	{
		Navail[i + 1].Number = avail[i].Number + 1;
		Navail[i + 1].BeginAddress = avail[i].BeginAddress;
		Navail[i + 1].Length = avail[i].Length;
	}
	Navail[0].Number = 1;
	for (int j = 0; j < n; j++)
	{
		if (name == busy[j].Name)
		{
			key = j;
			cout << "进程回收成功！" << endl;
			break;
		}
	}
	Navail[0].BeginAddress = busy[key].BeginAddress;
	Navail[0].Length = busy[key].Length;
	Print(Navail, busy, n, m + 1);
}

void Distribute(Avail *avail,Busy *busy,int m,int n)
{
	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < m; i++)
		{
			if (avail[i].Length >= busy[j].Length && !avail[i].Used)
			{
				avail[i].Length = avail[i].Length - busy[j].Length;
				if (avail[i].Length != 0)
				{
					avail[i].BeginAddress = avail[i].BeginAddress + busy[j].Length;
					busy[j + 1].BeginAddress = busy[j].BeginAddress + busy[j].Length;
				}
				else
				{
					avail[i].Used = true;
				}
				cout << busy[j].Name << "进程分配成功" << endl;
				break;
			}
			else
			{
				cout << busy[j].Name << "分配失败！" << endl;
			}
		}
	}
	Print(avail, busy, n, m);
}

int main()
{
	int m = 0, n = 0;
	int i = 0;
	struct Avail *avail = new struct Avail[m];
	struct Busy *busy = new struct Busy[n];
	ifstream in("C:\\Users\\sherlock\\Desktop\\os4.txt", ios::in);
	if (!in.is_open())
	{
		cout << "文件打开失败" << endl;
		exit(1);
	}
	in >> m;
	while (!in.eof() && i < m)
	{
		in >> avail[i].Number >> avail[i].BeginAddress >> avail[i].Length;
		i++;
	}
	in >> n;
	i = 0;
	while (!in.eof() && i < n)
	{
		in >> busy[i].Name >> busy[i].BeginAddress >> busy[i].Length;
		i++;
	}
	in.close();
	avail->Used = false;
	Print(avail, busy, n, m);
	Distribute(avail, busy, m, n);
	Recover(avail, busy, m, n);
	return 0;
}