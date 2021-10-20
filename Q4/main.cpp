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
	int method;//�ݹ���߷ǵݹ�
	get_input(max, 1, 20, "N�ʺ����⣬������N�Ĵ�С(��20): ");
	get_input(method, RECURSIVE,NO_RECURSIVE , "��ѡ��ⷨ,1Ϊ�ݹ鷽ʽ��2Ϊ�ǵݹ鷽ʽ: ");
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
