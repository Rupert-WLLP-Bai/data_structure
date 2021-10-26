/*
@file:        menu.h
@description: 菜单函数
@version:     v1.0.0
@author:      Laobai
@time:        2021年10月26日16:35:17
*/

/*
update notes:

v1.0.0 2021年10月26日16:35:17
    TODO in v1.0.1:
        1. 完善输入提示
        2. fetch_choice的内容改为枚举
*/
#include <iomanip>
#include <iostream>
using namespace std;

//输出菜单
void print_menu();
//获取操作
void fetch_choice(int* arr);
//主循环
void mainloop();
//获取输入
void get_input(int&, int, int, const char*);

#include "sort.h"
using namespace sort_laobai;
using namespace test_sort;
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
    cout << "**" << setw(15) << ""
         << "9---std::sort" << setw(14) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "0---退出程序" << setw(15) << " "
         << "**" << endl;
}

void input(int*& arr) {
    int num, range;
    get_input(num, 0, INT32_MAX, "Input num of random numbers : ");
    get_input(range, 1, INT32_MAX, "Input range of random numbers : ");
    arr = new int[num];
    generate(arr, num, range);
}

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

void fetch_choice(int* arr) {
    int ret;
    string NAME[10] = {"Exit", "Bubble_sort", "Selection_sort", "Insertion_sort", "Quick_sort", "Shell_sort", "Heap_sort", "Merge_sort", "Radix_sort", "std::sort"};
    get_input(ret, 0, 9, "Choose type of sort : ");  //0~8的输入
    cout << NAME[ret] << endl;
    switch (ret) {
        case 0:  //退出
            delete[] arr;
            exit(0);
        case 1:  //冒泡排序
            Bubble_sort(arr);
            break;
        case 2:  //选择排序
            Selection_sort(arr);
            break;
        case 3:  //插入排序
            Insertion_sort(arr);
            break;
        case 4:  //希尔排序
            Shell_sort(arr);
            break;
        case 5:  //快速排序
            Quick_sort(arr);
            break;
        case 6:  //堆排序
            Heap_sort(arr);
            break;
        case 7:  //二路归并排序
            Merge_sort(arr);
            break;
        case 8:  //基数排序
            Radix_sort(arr);
            break;
        case 9:  //std::sort()
            std_result(arr);
            break;
    }
}

void mainloop() {
    int* arr = nullptr; //需要初始化
    int i = 1;
    while (1) {
        if (i) {
            print_menu();
            input(arr);
            i = 0;
        }
        fetch_choice(arr);
    }
}

//2021年10月19日17:40:47