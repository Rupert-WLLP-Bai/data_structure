#include <stdio.h>
#include <iostream>
using namespace std;

const int maxn = 20;
int a[maxn];
bool col_vis[maxn];              //标志每一列是否被占用
bool diagonal_vis[2][maxn * 2];  //标志主、副对角线是否被占用
int n;
int tot = 0;

//depth-first search
// 当前考虑到了第cur行
void dfs(int cur) {
    // 考虑完了所有皇后
    if (cur == n) {
        //输出解
        tot++;
        if (1) {
            printf("#%d: ", tot);
            //cout << "#" << tot << ":";
            for (int i = 0; i < n; i++) {
                //cout << a[i] << " ";
                printf("%d ", a[i]);
            }
            printf("\n");
        }
        return;
    }

    // 还没有考虑完
    // 枚举第cursor行的皇后放在哪一列
    for (int i = 1; i <= n; i++) {
        // 假设我把这个皇后放在第i列
        // 我们需要检查这个皇后所在的列、它所在的主副对角线 是否被其他皇后占用

        if (!col_vis[i] &&                 //检查所在列
            !diagonal_vis[0][cur + i] &&   //检查副对角线
            !diagonal_vis[1][cur - i + n]  //检查主对角线，加n是为了避免出现负数
        ) {
            a[cur] = i;
            col_vis[i] = diagonal_vis[0][cur + i] = diagonal_vis[1][cur - i + n] = true;
            dfs(cur + 1);
            col_vis[i] = diagonal_vis[0][cur + i] = diagonal_vis[1][cur - i + n] = false;  //非常重要，修改了辅助全局变量务必改回来
        }
    }
}

void example() {
    cin >> n;
    dfs(0);
    cout << tot << endl;
}