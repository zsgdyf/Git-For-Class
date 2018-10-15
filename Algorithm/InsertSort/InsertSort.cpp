// InsertSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

void Swap(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
}
void InsertSort1(int a[], int n)
{
	int i, j;
	for (i = 1; i < n; i++)
	{
		int key = a[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (key < a[j])
			{
				a[j + 1] = a[j];
			}
			else break;
		}
		a[j + 1] = key;
	}
}
void InsertSort2(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j > 0 && a[j] < a[j - 1]; j--)
		{
			int temp = a[j];
			a[j] = a[j - 1];
			a[j - 1] = temp;
		}
	}
}
void BubbleSort(int a[], int n) 
{
	int temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
}
void SelectSort(int a[], int n) 
{
	for (int i = 0; i < n; i++) 
	{
		int min = i;
		for (int j = i +1 ; j < n; j++) 
		{
			if (a[min] > a[j])
				min = j;
		}
		int temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
}
void ShellSort(int a[], int n)
{
	int h = 1;
	while (h < n / 3)
		h = h * 3 + 1;
	while (h >= 1)
	{
		for (int i = h; i < n; i++)
		{
			for (int j = i; j > h && a[j] < a[j - h]; j = j - h)
			{
				int temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
			}
		}
		h = h / 3;
	}
}
int Partition(int a[], int low, int high)
{
		int pivot = a[high];
		int i = low - 1;
		for (int j = low; j < high; j++)
		{
			if (a[j] <= pivot)
			{
				i++;
				Swap(a[i], a[j]);
			}
		}
		Swap(a[i + 1],a[high]);
		return i + 1;
}
void QuickSort(int a[], int low, int high)
{
	if (low < high)
	{
		int mid = Partition(a, low, high);
		QuickSort(a, low, mid - 1);
		QuickSort(a, mid + 1, high);
	}
}

int main()
{
	int n, i;
	cin >> n;
	int *a = new int[n];			//动态数组
	for (i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	//InsertSort1(a, n);				//插入排序
	//InsertSort2(a, n);
	//BubbleSort(a, n);				//冒泡排序
	//SelectSort(a, n);				//选择排序
	//ShellSort(a, n);				//希尔排序
	QuickSort(a, 0, n-1);
	for (i = 0; i < n; i++)
	{
		cout << a[i]<<"  ";
	}
	delete[]a;
    return 0;
}

