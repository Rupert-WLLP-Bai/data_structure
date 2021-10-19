//tool.h 获取输入等工具函数
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