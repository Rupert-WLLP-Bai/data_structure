/*
@file:        main.cpp
@description: ������
@version:     v1.0.1
@author:      Laobai
@time:        2021��10��25��22:27:39
*/

/*
update notes:
v1.0.0 2021��10��10��10:20:39
	TODO in v1.0.1:
		1. ����ݹ�ⷨ��֮���޸Ĳ˵�
v1.0.1 2021��10��25��22:27:39
	TODO in v1.0.2:
        1. ������߳̽ⷨ�Ĳ˵�(��Java����ʵ��)
*/

/*
@name:		  main.cpp
@description: ������
@version:     v1.0.0
@author:      Laobai
@time:        2021��10��26��16:11:39
*/

/*
update notes:

v1.0.0 2021��10��26��16:11:39

*/

#include<iostream>
#include"N_Queen.h"
#include"tool.h"
using namespace std;

int main() {
	enum methods {
		RECURSIVE = 1, NO_RECURSIVE, MULTITHREADING
	};
	int max;	//N�Ĵ�С
	int method;	//�ݹ���߷ǵݹ�
	get_input(max, 1, 20, "N�ʺ����⣬������N�Ĵ�С(��20): ");
	get_input(method, RECURSIVE,MULTITHREADING , "��ѡ��ⷨ,1Ϊ�ݹ鷽ʽ��2Ϊ�ǵݹ鷽ʽ��3Ϊ���̷߳�ʽ: ");
	N_Queen N(max);
	switch (method) 	{
	case RECURSIVE:
		N.solve_Recursive();
		break;
	case NO_RECURSIVE:
		N.solve_noRecursive();
		break;
	case MULTITHREADING:
		N.solve_Multithreading();
	}
	return 0;
}
