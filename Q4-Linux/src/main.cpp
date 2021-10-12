#include "N_Queen.h"
#include "example.h"
using namespace std;

int main() {
    //example();//N皇后问题的递归解法
    int N;
    cout << "输入N" << endl;
    cin >> N;
    Solution(N);  //N皇后的栈解法
    return 0;
}