/*
@file:        N_Queen.h
@description: N皇后
@version:     v1.0.1
@author:      Laobai
@time:        2021年10月25日22:27:39
*/

/*
update notes:

v1.0.0 2021年9月29日17:55:52
    TODO in v1.0.1:
        1. 加入递归解法

v1.0.1 2021年10月25日22:27:39
    TODO in v1.0.2:
        1. 加入多线程解法(在Java下已实现)
*/

#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

class N_Queen {
   private:
    int max;                      //最大行列数
    int* array;                   //存放皇后放置列数的数组
    bool judge(int n);            //判断放置位置是否合理
    void solve_Recursive(int n);  //递归解法(Private)
   public:
    N_Queen(int max);
    ~N_Queen();
    void solve_Recursive();       //递归解法
    void solve_noRecursive();     //非递归解法
    void solve_Multithreading();  //多线程解法
};

N_Queen::N_Queen(int max) {
    this->array = new int[max];
    this->max = max;
    for (int j = 0; j < max; j++) {
        this->array[j] = -1;
    }
}

N_Queen::~N_Queen() {
    delete[] array;
}

//判断放置位置是否合理
bool N_Queen::judge(int n) {
    for (int i = 0; i < n; i++) {
        if (array[i] == array[n] || abs(n - i) == abs(array[i] - array[n])) {
            return false;
        }
    }
    return true;
}

//递归解法(Private)
inline void N_Queen::solve_Recursive(int N) {
    static int count = 0;  //记录当前是第几种情况
    for (int i = 0; i < max; i++) {
        array[N] += i + 1;
        if (judge(N)) {
            /*到达最后一层，输出结果*/
            if (N == max - 1) {
                printf("第%10d种情况：", ++count);
                /*打印情况*/
                for (int i = 0; i < max; ++i)
                    printf("%2d ", array[i] + 1);
                printf("\n");
            }
            /*未到达最后一层，向下搜索*/
            else {
                solve_Recursive(N + 1);
            }
        }
        array[N] = -1;
    }
}
//递归解法(Public)
inline void N_Queen::solve_Recursive() {
    solve_Recursive(0);
}
//非递归解法
inline void N_Queen::solve_noRecursive() {
    int n = max;    //max个皇后
    int count = 0;  //记录当前第几情况
    int k = 0;      //初始化k为第一列

    while (k > -1) {                           //k==-1时：表示摆放第1个皇后就超过了列底部（即已经找完所有情况）
        array[k] += 1;                         //a[k]位置，摆放一个皇后
        while ((array[k] < n) && (!judge(k)))  //如果a[k]（即皇后摆放位置）没有到列最底部，且摆放冲突。
            array[k] += 1;                     //将皇后列下移一位
        if (array[k] < n) {                    //皇后摆放位置没有到达列最底部
            if (k == (n - 1)) {                //k==n-1表示，max列皇后全部摆放完毕
                printf("第%10d种情况：", ++count);
                for (int i = 0; i < n; ++i)  //打印情况
                    printf("%2d ", array[i] + 1);
                printf("\n");
            } else {            //皇后还未摆放完毕
                k += 1;         //继续摆放下一列
                array[k] = -1;  //此行初始化a[k] = -1;表示第k列，从第一行开始摆放皇后
            }
        } else       //回溯：当a[k]>max进入else,表示在第k列中没有找到合适的摆放位置
            k -= 1;  //回溯到k-1步：k表示第几个皇后，a[k]表示第k个皇后摆放的位置
    }
}

//多线程解法
inline void N_Queen::solve_Multithreading() {
}