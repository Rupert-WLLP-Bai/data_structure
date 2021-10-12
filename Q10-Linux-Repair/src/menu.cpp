#include "menu.h"
void print_menu() {
    cout << "**" << setw(15) << " "
         << "排序算法比较" << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "1---冒泡排序" << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "2---选择排序" << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "3---插入排序" << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "4---希尔排序" << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "5---快速排序" << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "6---堆排序  " << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "7---归并排序" << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "8---基数排序" << setw(15) << " "
         << "**" << endl;
}

void input() {
    int num, range;
    get_input(num, 0, INT32_MAX, "Input num of random numbers : ");
    get_input(range, 1, INT32_MAX, "Input range of random numbers : ");
}

void get_input(int& ret, int min, int max, const char* prompt = "") {
    while (1) {
        cout << prompt << endl;
        cin >> ret;
        if (cin.fail() || ret < min || ret > max) {
            cin.clear();
            cin.ignore(65536, '\n');
            cout << "Error input" << endl;
        } else
            break;
    }
}

void fetch_choice() {
    int ret;
    get_input(ret, 0, 8, "");
}

void mainloop() {
    //可提供一个重置数组的选项 同时重新打印菜单 即直接从程序开头重新执行
    //输出菜单
    //获取数量 以及范围
    //输入错误 停顿 clear 返回最开始
    //获取用户操作
    //输入错误重新获取用户操作 不重新生成
    while (1) {
        print_menu();
        input();
        fetch_choice();
    }
}