/*
@name:		  main.cpp
@description: ������
@version:     v1.0.1
@author:      Laobai
@time:        2021��10��21��23:12:08
*/

/*
update notes:
v1.0.0 2021��10��19��17:55:52
v1.0.1 2021��10��21��23:12:08
*/

#include <iostream>
#include "core.h"
int main() {
    int ret;
    Table T;
    T.Spawn();  //����
    T.Print();  //������еı�
    while (1) {
        fetch_choice(ret, T);
        if (ret == 0) {
            cout << "�˳�����" << endl;
            break;
        }
    }
    return 0;
}
