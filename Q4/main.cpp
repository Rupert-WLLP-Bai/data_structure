/*
# -*- coding: gbk -*-
# @Time    : 2021-10-19 22:48:17
# @Author  : Laobai
# @File    : main.cpp
*/

#include<iostream>
#include"N_Queen.h"
#include"tool.h"
using namespace std;

int main() {
	enum methods {
		RECURSIVE = 1,NO_RECURSIVE
	};
	int max;//N
	int method;//递归或者非递归
	get_input(max, 1, 20, "N皇后问题，请输入N的大小(≤20): ");
	get_input(method, RECURSIVE,NO_RECURSIVE , "请选择解法,1为递归方式，2为非递归方式: ");
	N_Queen N(max);
	switch (method) 	{
	case RECURSIVE:
		N.solve_Recursive();
		break;
	case NO_RECURSIVE:
		N.solve_noRecursive();
		break;
	}
	return 0;
}
