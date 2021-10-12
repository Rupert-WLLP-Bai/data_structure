//DFS 不使用并查集
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>
#include "Maze.h"
#include "backtrace.h"
using namespace std;

class DFS {
   public:
    void get_choice(int* choice, int current, Maze A);
    bool search_neighbors(int* neighbor_visited, int current, Maze A, vector<int> visited);
    void generate(Maze& A) {  //生成迷宫
        //const char* F[] = {"上", "下", "左", "右"};
        srand(time(NULL));
        A.L.push(A.start);                              //起始位置入栈
        A.map[A.start._x][A.start._y]._visited = true;  //起点标记为已被访问
        int current_x, current_y;                       //现在节点所在的位置
        current_x = A.start._x;                         //起点
        current_y = A.start._y;                         //起点
        //cout << "start = (" << A.start._x << "," << A.start._y << ")" << endl;
        while (A.L.top() != A.end) {                                 //未走到终点 搜索邻接节点
            if (!A.search_neighbors(A.map[current_x][current_y])) {  //邻接节点有未被访问的节点
                int direction;                                       //方向
                while (1) {
                    int _x, _y;  //横坐标，纵坐标
                    _x = current_x;
                    _y = current_y;
                    direction = rand() % 4;  //四个方向
                    if (direction == 0)
                        _x--;
                    else if (direction == 1)
                        _x++;
                    else if (direction == 2)
                        _y--;
                    else
                        _y++;
                    if (_x < 0 || _x > A.row - 1 || _y < 0 || _y > A.column - 1)  //超限
                        continue;
                    if (A.map[_x][_y]._visited == false)
                        break;
                }
                //cout << "direction = " << F[direction] << endl;
                //print_visited();
                A.break_the_wall(A.map[current_x][current_y], direction);      //拆墙
                Node cur = A.map[current_x][current_y] + A.offset[direction];  //更新位置
                current_x = cur._x;                                            //更新位置
                current_y = cur._y;                                            //更新位置
                A.map[current_x][current_y]._visited = true;                   //标记为已访问
                A.L.push(A.map[current_x][current_y]);                         //节点入栈
                //cout << "current = (" << current_x << "," << current_y << ")" << endl;
            } else {
                A.L.pop();  //节点退栈
                //cout << "(" << current_x << "," << current_y << ")退栈" << endl;
                current_x = A.L.top()._x;  //更新位置
                current_y = A.L.top()._y;
            }
            //print_the_wall();
            //A.print_node_all();
        }
    }
    void solve(Maze A);          //SOLVE
    void print_results(Maze A);  //Maze和Solution

   private:
    deque<int> solution;
};
void DFS::get_choice(int* choice, int current, Maze A) {
    Node L = A.map[current / A.column][current % A.column];
    choice[0] = L._up;
    choice[1] = L._down;
    choice[2] = L._left;
    choice[3] = L._right;
}
void DFS::solve(Maze A) {
    srand(time(NULL));
    vector<int> visited;  //记录已经访问的点
    int choice[4];
    int direction;
    int current = A.start._x * A.column + A.start._y;
    visited.push_back(current);                                     //起点标记
    solution.push_back(A.start._x * A.column + A.start._y);         //放入起点
    while (solution.back() != A.end._x * A.column + A.end._y) {     //走到终点
        get_choice(choice, current, A);                             //获取节点可以走的位置
        bool flag = search_neighbors(choice, current, A, visited);  //搜索邻接节点的访问情况
        if (flag) {
            while (1) {  //随机一个位置
                direction = rand() % 4;
                if (choice[direction] == true)
                    break;
            }
            switch (direction) {
                case 0:  //up
                    current -= A.column;
                    break;
                case 1:  //down
                    current += A.column;
                    break;
                case 2:  //left
                    current -= 1;
                    break;
                case 3:  //right
                    current += 1;
                    break;
            }
            solution.push_back(current);
            visited.push_back(current);
        } else {
            solution.pop_back();
            current = solution.back();
        }
    }
    // while (solution.size()) {
    //     cout << solution.front() << " --> ";
    //     solution.pop_front();
    // }
    // cout << "END" << endl;

    ofstream output;
    output.open("Solution.log");
    while (solution.size()) {
        output << hex << solution.front() << " --> ";
        solution.pop_front();
    }
    output << "END" << endl;
}
bool DFS::search_neighbors(int* choice, int current, Maze A, std::vector<int> visited) {
    int cur = current;
    if (choice[0]) {  //UP
        cur -= A.column;
        const vector<int>::iterator it = find(visited.begin(), visited.end(), cur);
        if (it != visited.end()) {  //找到
            choice[0] = false;
        }
        cur = current;  //回复
    }
    if (choice[1]) {  //DOWN
        cur += A.column;
        const vector<int>::iterator it = find(visited.begin(), visited.end(), cur);
        if (it != visited.end()) {  //找到
            choice[1] = false;
        }
        cur = current;  //回复
    }
    if (choice[2]) {  //LEFT
        cur -= 1;
        const vector<int>::iterator it = find(visited.begin(), visited.end(), cur);
        if (it != visited.end()) {  //找到
            choice[2] = false;
        }
        cur = current;  //回复
    }
    if (choice[3]) {  //RIGHT
        cur += 1;
        const vector<int>::iterator it = find(visited.begin(), visited.end(), cur);
        if (it != visited.end()) {  //找到
            choice[3] = false;
        }
        cur = current;  //回复
    }
    return (choice[0] | choice[1] | choice[2] | choice[3]);
}
void DFS::print_results(Maze A) {
    int ID = 0;
    const int printnumber = 0;
    // int max_digit = int(log10(row * column)) + 1;
    vector<Node> Line;  //一行的节点内容
    //cout << "Print_Node_All" << endl;
    for (int i = 0; i < A.row; i++) {
        Line.clear();
        for (int j = 0; j < A.column; j++) {  //输出第一行
            Line = A.map[i];                  //获取第i行的节点数据
            cout << "██";                     //输出左上角一格墙
            if (Line[j]._up == false)
                cout << "███";  //输出节点上方的墙
            else {
                cout << "\033[34m"
                     << "  "
                     << "\033[0m";  //否则不输出墙
            }
        }
        cout << "██" << endl;                 //输出结束节点右上角的墙，换行
        cout << "██";                         //输出第二行最左边的墙
        for (int j = 0; j < A.column; j++) {  //输出第二行（包含左右墙和数字）

            if (Line[j]._right == false) {
                if (printnumber)
                    cout << hex << setw(3) << ID++;  //输出数字
                else
                    cout << "   ";
                cout << "██";  //输出节点右边的墙
            } else {
                if (printnumber)
                    cout << hex << setw(3) << ID++;  //输出数字
                else
                    cout << "   ";
                cout << "\033[34m"
                     << "  "
                     << "\033[0m";  //否则不输出墙
            }
        }
        cout << endl;  //结束输出，换行
    }
    for (int i = 0; i < 5 * A.column + 2; i++)
        cout << "█";  //输出最后一行
    cout << endl;
}