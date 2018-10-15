// os3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<cmath>
#include <algorithm>
#include<fstream>
using namespace std;

void Fcfs(int n,int begin,int *a)
{
	cout << endl << "先来先服务（FCFS）算法：" << endl;
	cout << "磁头依次访问的磁道号序列为：";
	cout << begin << "->";
	for (int i = 0; i < n-1; i++)//按顺序输出磁道号序列
	{
		cout << a[i] << "->";
	}
	cout << a[n - 1] << endl;
	int sum = abs(begin - a[0]);
	for (int i = 0; i < n-1; i++)
	{
		sum = sum + abs(a[i] - a[i + 1]);
	}
	cout << "磁头移动的总磁道数为：" << sum << endl;
}

void Sstf(int n, int begin, int *a)
{
	cout << endl << "最短寻道时间优先（SSTF）算法：" << endl;
	cout << begin;
	int sum = 0;
	int *visited = new int[n];
	int *next = new int[n];//存储下一个磁道号，便于输出
	next[0] = begin;
	for (int i = 0; i < n; i++)//设置访问位
	{
		visited[i] = 0;//0表示未被访问
	}
	for (int j = 0; j < n; j++)
	{
		int min = 9999, key = 0;
		for (int i = 0; i < n; i++)//找出每次的最短寻道时间
		{
			if (!visited[i] && abs(a[i] - begin) < min)
			{
				min = abs(a[i] - begin);
				key = i;
			}
		}
		cout << "->" << a[key];
		begin = a[key];
		next[j + 1] = a[key];
		visited[key] = 1;//每次将访问过的磁道设置为1
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		sum = sum + abs(next[i] - next[i + 1]);
	}
	cout << "磁头移动的总磁道数为：" << sum << endl;
}

void ScanL(int n, int begin, int *a)
{
	cout << endl << "电梯算法（磁头初始移动方向为左）：" << endl;
	int key;
	int *s = new int[n + 1];
	for (int i = 0; i < n; i++)//将磁道号序列和当前磁头位置一起存入一个新数组
	{
		s[i] = a[i];
	}
	s[n] = begin;
	sort(s, s + n + 1);//当前磁头位置和磁道号序列数组排序
	for (int i = 0; i < n + 1; i++)//找到当前磁头所在位置
	{
		if (s[i] == begin)
		{
			key = i;
		}
	}
	cout << "磁头依次访问的磁道号序列为：";
	for (int i = key; i >= 0; i--)//先向左移动
	{
		cout << s[i] << "->";
	}
	for (int i = key + 1; i < n; i++)//向右移动
	{
		cout << s[i] << "->";
	}
	cout << s[n] << endl;
	int sum = 0;
	sum = s[key] - s[0] + s[n] - s[0];//计算总磁道数
	cout << "磁头移动的总磁道数为：" << sum << endl;
}

void ScanR(int n,int begin,int *a)
{
	cout << endl << "电梯算法（磁头初始移动方向为右）：" << endl;
	int key;
	int *s = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		s[i] = a[i];
	}
	s[n] = begin;
	sort(s, s + n + 1);
	for (int i = 0; i < n + 1; i++)
	{
		if (s[i] == begin)
		{
			key = i;
		}
	}
	cout << "磁头依次访问的磁道号序列为：";
	for (int i = key; i <= n; i++)
	{
		cout << s[i] << "->";
	}
	for (int i = key - 1; i > 0; i--)
	{
		cout << s[i] << "->";
	}
	cout << s[0] << endl;
	int sum = 0;
	sum = s[n] - s[key] + s[n] - s[0];
	cout << "磁头移动的总磁道数为：" << sum << endl;
}


int main()
{
	int begin, n, i = 0;
	cout << "请输入要访问的磁道数目：";
	cin >> n;
//文件输入
	int *a = new int[n];//动态数组
	ifstream in;
	in.open("C:\\Users\\sherlock\\Desktop\\os3.txt", ios::in);
	if (!in.is_open())
	{
		cout << "文件打开失败" << endl;
		exit(1);
	}
	in >> begin;//当前磁头位置
	while (!in.eof() && i < n)
	{
		in >> a[i];//将磁道号序列存入数组
		i++;
	}
	in.close();
//手动输入
/*	cout << "请输入当前磁头的位置：";
	cin >> begin;
	cout << "磁道访问请求序列：";
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
*/
	Fcfs(n, begin, a);
	ScanL(n, begin, a);
	ScanR(n, begin, a);
	Sstf(n, begin, a);
    return 0;
}

