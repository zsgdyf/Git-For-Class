// os4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>  
using namespace std;

struct Avail//空闲分区表
{
	int Number;//空闲分区编号
	int Length;//空闲分区长度
	int BeginAddress;//空闲分区起始地址
	bool Used;//该分区是否被使用
};
struct Busy//进程占用分区表
{
	char Name;//进程名
	int Length;//进程长度
	int BeginAddress;//进程起始地址
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
	struct Avail *Navail = new struct Avail[m + 1];//建立新的可用表
	for (int i = 0; i < m; i++)
	{//没有回收的进程内存占用不变
		Navail[i + 1].Number = avail[i].Number + 1;
		Navail[i + 1].BeginAddress = avail[i].BeginAddress;
		Navail[i + 1].Length = avail[i].Length;
	}
	Navail[0].Number = 1;
	for (int j = 0; j < n; j++)
	{
		if (name == busy[j].Name)//找到需要回收的进程
		{
			key = j;
			cout << "进程回收成功！" << endl;
			break;
		}
	}
	Navail[0].BeginAddress = busy[key].BeginAddress;//修改可用表起始地址
	Navail[0].Length = busy[key].Length;//释放分区长度
	Print(Navail, busy, n, m + 1);//输出新的可用表
}

void Distribute(Avail *avail,Busy *busy,int m,int n)
{
	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < m; i++)
		{
			if (avail[i].Length >= busy[j].Length && !avail[i].Used)
			{//分区空闲且分区长度大于进程所需长度
				//分配内存，并调整空闲分区长度
				avail[i].Length = avail[i].Length - busy[j].Length;
				if (avail[i].Length != 0)
				{//调整分区表空闲分区起始地址
					avail[i].BeginAddress = avail[i].BeginAddress + busy[j].Length;
					busy[j + 1].BeginAddress = busy[j].BeginAddress + busy[j].Length;
				}
				else
				{//若进程所需大小等于空闲分区大小，则置为已使用
					avail[i].Used = true;
				}
				//分配成功
				cout << busy[j].Name << "进程分配成功" << endl;
				break;
			}
			else
			{
				cout << busy[j].Name << "分配失败！" << endl;
			}
		}
	}
	//输出空闲表和内存分配情况
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