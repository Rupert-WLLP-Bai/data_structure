//重新组织思路 该部分已被废弃
// //用栈模拟实现N皇后问题
// //v1.0
// #include <cmath>
// #include <iomanip>
// #include <iostream>
// #include "LinkedStack.h"
// using namespace std;

// // int place(LinkedStack<int>St,int i,int j)  //测试(i,j)是否与1～i-1皇后有冲突
// // {
// //     int a=0;         //a为函数的返回值
// //     int k=1;
// //     if (i==1)
// //     {
// //         a=1;
// //         return a;	//放第一个皇后时没有冲突
// //     }
// //     while (k<=i-1)			//j=1到k-1是已放置了皇后的列
// //     {
// //         if ((St.data[k]==j)||(fabs(j-St.data[k])==fabs(i-k)))
// //         {
// //             a=0;
// //             return a;
// //         }
// //         else
// //             k++;
// //     }
// //     a=1;
// //     return a;
// // }
// // //输出解,参数控制是否具体内容
// // void display_solution(LinkedStack<int>* map, int N, bool show) {
// //     static int count = 0;
// //     const int solu_width = 10;
// //     const int num_width = int(log10(N)) + 1;
// //     int top;
// //     if (show) {
// //         cout << "第" << setw(solu_width) << ++count << "个解：";
// //         for (int i = 0; i < N; i++) {
// //             map[i].getTop(top);
// //             cout << setw(num_width) << top << " ";
// //         }
// //         cout << endl;
// //     }
// // }
// // //判断是否能够放置皇后在第i行第j列
// // bool place(LinkedStack<int>* map, int i, int j) {
// //     bool flag;
// //     return flag;
// // }
// // //输入参数N,构造n个链式栈,存放n列皇后存放位置的列号
// // void Solution(int N) {
// //     int total = 0;
// //     //map[i]表示第i行的栈
// //     LinkedStack<int>* map = new LinkedStack<int>[N];
// //     //visited数组 回溯到上一层时 重置数组内容
// //     bool** visited = new bool*[N];
// //     for (int i = 0; i < N; i++) {
// //         for (int j = 0; j < N; j++) {
// //             visited[i][j] = false;
// //         }
// //     }

// //     //释放
// //     delete[] map;
// //     delete[] visited;
// // }

// #define MaxSize 100
// typedef struct
// {
//     int col[MaxSize];
//     int top;
// } StackType;
// void dispasolution(StackType St) {
//     static int count = 0;
//     cout << "第" << ++count << "个解:";
//     for (int i = 1; i <= St.top; i++)
//         cout << "(" << i << "," << St.col[i] << ")";
//     cout << endl;
// }
// bool place(StackType St, int k, int j) {
//     int i = 1;
//     if (k == 1)
//         return true;
//     while (i <= k - 1) {
//         if ((St.col[i] == j) || (abs(j - St.col[i]) == abs(i - k)))
//             return false;
//         i++;
//     }
//     return true;
// }
// void queen(int n) {
//     int k;
//     bool find;
//     StackType St;
//     St.top = 0;
//     St.top++;
//     St.col[St.top] = 0;
//     while (St.top != 0) {
//         k = St.top;
//         find = false;
//         for (int j = St.col[k] + 1; j <= n; j++)
//             if (place(St, k, j)) {
//                 St.col[St.top] = j;
//                 find = true;
//                 break;
//             }
//         if (find) {
//             if (k == n)
//                 dispasolution(St);
//             else {
//                 St.top++;
//                 St.col[St.top] = 0;
//             }
//         } else
//             St.top--;
//     }
// }
// void Solution() {
//     int n;
//     printf("皇后问题(n<20) n=");
//     scanf("%d", &n);
//     if (n > 20)
//         printf("n值太大\n");
//     else {
//         printf(" %d皇后问题求解如下：\n", n);
//         queen(n);
//     }
// }
