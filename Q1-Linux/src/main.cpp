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
//2021年10月19日17:57:01