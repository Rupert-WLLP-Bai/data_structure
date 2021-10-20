#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stack>
using namespace std;

class N_Queen {
   private:
    int max;  //最大行列数
    int* array;
    bool judge(int n);

   public:
    N_Queen(int max);
    ~N_Queen();
    void solve_Recursive();    //递归解法
    void solve_noRecursive();  //非递归解法
};

N_Queen::N_Queen(int max) {
    this->array = new int[max];
    this->max = max;
}

N_Queen::~N_Queen() {
    delete[] array;
}

bool N_Queen::judge(int n) {
    for (int i = 0; i < n; i++) {
        if (array[i] == array[n] || abs(n - i) == abs(array[i] - array[n])) {
            return false;
        }
    }
    return true;
}

//非递归解法
inline void N_Queen::solve_noRecursive() {
    //八皇后问题：回溯法（非递归）
    int n = max;    //max个皇后
    int count = 0;  //记录当前第几情况
    int i, k = 0;   //初始化k为第一列
    for (int j = 0; j < max; j++) {
        array[j] = -1;
    }
    while (k > -1) {                           //k==-1时：表示摆放第1个皇后就超过了列底部（即已经找完所有情况）
        array[k] += 1;                         //a[k]位置，摆放一个皇后
        while ((array[k] < n) && (!judge(k)))  //如果a[k]（即皇后摆放位置）没有到列最底部，且摆放冲突。
            array[k] += 1;                     //将皇后列下移一位
        if (array[k] < n) {                    //皇后摆放位置没有到达列最底部
            if (k == (n - 1)) {                //k==n-1表示，max列皇后全部摆放完毕
                printf("第%10d种情况：",++count);
                for (i = 0; i < n; ++i)  //打印情况
                    //cout << setw(2) << array[i] + 1 << " ";
                    printf("%2d ",array[i]+1);
                printf("\n");
            } else {            //皇后还未摆放完毕
                k += 1;         //继续摆放下一列
                array[k] = -1;  //此行初始化a[k] = -1;表示第k列，从第一行开始摆放皇后
            }
        } else       //回溯：当a[k]>max进入else,表示在第k列中没有找到合适的摆放位置
            k -= 1;  //回溯到k-1步：k表示第几个皇后，a[k]表示第k个皇后摆放的位置
    }
}

//递归解法
inline void N_Queen::solve_Recursive() {

}