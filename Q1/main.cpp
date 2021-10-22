/*
@name:		  main.cpp
@description: 主函数
@version:     v1.0.1
@author:      Laobai
@time:        2021年9月21日10:56:35
*/

/*
update notes:
v1.0.0 2021年9月21日10:56:35
    //  TODO in v1.0.1
        1. 注释的位置放在某一行的上一行(***改掉行尾注释)
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
