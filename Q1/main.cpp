/*
@name:		  main.cpp
@description: 主函数
@version:     v1.0.1
@author:      Laobai
@time:        2021年10月21日23:12:08
*/

/*
update notes:
v1.0.0 2021年10月19日17:55:52
v1.0.1 2021年10月21日23:12:08
*/

#include <iostream>
#include "core.h"
int main() {
    int ret;
    Table T;
    T.Spawn();  //创建
    T.Print();  //输出现有的表
    while (1) {
        fetch_choice(ret, T);
        if (ret == 0) {
            cout << "退出程序" << endl;
            break;
        }
    }
    return 0;
}
