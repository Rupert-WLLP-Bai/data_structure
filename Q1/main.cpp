/*
@name:		  main.cpp
@description: ������
@version:     v1.0.1
@author:      Laobai
@time:        2021��10��22��22:03:38
*/

/*
update notes:

v1.0.0 2021��9��21��10:56:35
    TODO in v1.0.1
        1. ע�͵�λ�÷���ĳһ�е���һ��(***�ĵ���βע��)

v1.0.1 2021��10��22��22:03:38
*/

#include <iostream>
#include "core.h"
int main() {
    int ret;
    Table T;
    /* ������������еı� */
    T.Spawn();  
    T.Print();  
    /* ������ѭ�� */
    while (1) {
        fetch_choice(ret, T);
        if (ret == 0) {
            cout << "�˳�����" << endl;
            break;
        }
    }
    return 0;
}
