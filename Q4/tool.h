/*
@file:        joseph.h
/*
@file:        tool.h
@description: ���ߺ���
@version:     v1.0.0
@author:      Laobai
@time:        2021��10��22��11:20:33
*/

/*
update notes:

v1.0.0 2021��10��22��11:20:33

*/

#pragma once
#include<iostream>
using namespace std;

void get_input(int& ret, int min, int max, const char* prompt = "") {
    while (1) {
        cout << prompt;
        cin >> ret;
        if (cin.fail() || ret < min || ret > max) {
            cin.clear();
            cin.ignore(65536, '\n');
            cout << "Error input" << endl;
        } else
            break;
    }
}