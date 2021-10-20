//Maze.h 迷宫
#pragma once
#include <stdlib.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>
//#include "backtrace.h"
using namespace std;

class Node {
   public:
    int _x, _y;                      //横坐标，纵坐标
    bool _visited;                   //是否被访问
    bool _up, _down, _left, _right;  //上下左右的墙
    Node(int x = 0, int y = 0, bool visited = false, bool up = false, bool down = false, bool left = false, bool right = false) {
        _x = x;
        _y = y;
        _visited = visited;
        _up = up;
        _down = down;
        _left = left;
        _right = right;
    }  //带参构造
    friend Node operator+(const Node& A, const Node& B);
    friend bool operator==(const Node& A, const Node& B);
    friend bool operator!=(const Node& A, const Node& B);
};
Node operator+(const Node& A, const Node& B) {
    Node node;
    node._x = A._x + B._x;
    node._y = A._y + B._y;
    node._visited = 0;
    node._up = 1;
    node._down = 1;
    node._left = 1;
    node._right = 1;
    return node;
};
bool operator==(const Node& A, const Node& B) {
    if (A._x == B._x && A._y == B._y)
        return true;
    else
        return false;
}
bool operator!=(const Node& A, const Node& B) {
    if (A._x != B._x || A._y != B._y)
        return true;
    else
        return false;
}
class Maze {
   private:
    Node start;                                                           //入口
    Node end;                                                             //出口
    Node offset[4] = {Node(-1, 0), Node(1, 0), Node(0, -1), Node(0, 1)};  //偏移量 分别是上下左右
    int row;                                                              //行数
    int column;                                                           //列数
    vector<vector<Node>> map;                                             //存放二维的节点图
    stack<Node> L;                                                        //记录路径
    bool search_neighbors(Node A);                                        //搜索邻接节点
    void break_the_wall(Node A, int direcion);                            //拆墙
    void init(int R, int C) {
        row = R;             //行数
        column = C;          //列数
        start = Node(0, 0);  //初始化起点终点
        end = Node(row - 1, column - 1);

        vector<Node> temp;  //中间vector，存一行
        for (int i = 0; i < row; i++) {
            temp.clear();  //用完一次清空
            for (int j = 0; j < column; j++) {
                temp.push_back(Node(i, j));  //节点按行填入
            }
            map.push_back(temp);  //插入一行
        }
    }

   public:
    Maze(int R = 10, int C = 10) { init(R, C); };
    ~Maze(){};
    void print_node_position();  //输出坐标位置
    void print_node_num();       //输出序号
    void print_node_all();       //打印所有信息(先存取一行的内容再打印)
    void print_the_wall();       //输出墙
    void print_visited();
    void reset();  //重置
    friend class DFS;
    friend class Perfect_Maze;
};
void Maze::print_node_position() {
    vector<Node>::iterator it;
    vector<vector<Node>>::iterator iter;
    vector<Node> vec_tmp;
    int max_digit = int(log10(max(row, column))) + 1;
    cout << "Print_Node_Position" << endl;
    for (iter = map.begin(); iter != map.end(); iter++) {
        vec_tmp = *iter;
        for (it = vec_tmp.begin(); it != vec_tmp.end(); it++) {
            cout << "(" << setw(max_digit) << it->_x << "," << setw(max_digit) << it->_y << ") ";
        }
        cout << endl;
    }
}
void Maze::print_node_num() {
    vector<Node>::iterator it;
    vector<vector<Node>>::iterator iter;
    vector<Node> vec_tmp;
    int ID = 0;
    int max_digit = int(log10(row * column)) + 1;
    cout << "Print_Node_Num" << endl;
    for (iter = map.begin(); iter != map.end(); iter++) {
        vec_tmp = *iter;
        for (it = vec_tmp.begin(); it != vec_tmp.end(); it++) {
            cout << "[" << setw(max_digit) << ID++ << "] ";
        }
        cout << endl;
    }
}
void Maze::print_the_wall() {
    vector<Node> Line;  //一行的节点内容
    for (int i = 0; i < row; i++) {
        Line.clear();
        for (int j = 0; j < column; j++) {
            Line = map[i];
            cout << Line[j]._up << Line[j]._down << Line[j]._left << Line[j]._right << "  ";
        }
        cout << endl
             << endl;
    }
}
void Maze::print_node_all() {
    int ID = 0;
    const int printnumber = 1;
    // int max_digit = int(log10(row * column)) + 1;
    vector<Node> Line;  //一行的节点内容
    //cout << "Print_Node_All" << endl;
    for (int i = 0; i < row; i++) {
        Line.clear();
        for (int j = 0; j < column; j++) {  //输出第一行
            Line = map[i];                  //获取第i行的节点数据
            cout << "██";                   //输出左上角一格墙
            if (Line[j]._up == false)
                cout << "███";  //输出节点上方的墙
            else {
                cout << "   ";  //否则不输出墙
            }
        }
        cout << "██" << endl;               //输出结束节点右上角的墙，换行
        cout << "██";                       //输出第二行最左边的墙
        for (int j = 0; j < column; j++) {  //输出第二行（包含左右墙和数字）

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
                cout << "  ";  //否则不输出墙
            }
        }
        cout << endl;  //结束输出，换行
    }
    for (int i = 0; i < 5 * column + 2; i++)
        cout << "█";  //输出最后一行
    cout << endl;
}
bool Maze::search_neighbors(Node node) {  //搜索node的邻接节点是否都被访问
    int value[4] = {1, 1, 1, 1};          //四个方向 按顺序是上下左右 默认为1 已访问
    bool flag;                            //返回值 0表示有未访问的节点 1表示当前节点退栈
    int x = node._x;
    int y = node._y;

    if (node._y == 0) {  //左侧节点
        if (node._x == 0) {
            //左上
            value[1] = map[x + 1][y]._visited;  //down
            value[3] = map[x][y + 1]._visited;  //right
        } else if (node._x == row - 1) {
            //左下
            value[0] = map[x - 1][y]._visited;  //up
            value[3] = map[x][y + 1]._visited;  //right
        } else {
            //左侧其他
            value[0] = map[x - 1][y]._visited;  //up
            value[1] = map[x + 1][y]._visited;  //down
            value[3] = map[x][y + 1]._visited;  //right
        }
    } else if (node._y == column - 1) {  //右侧节点
        if (node._x == 0) {
            //右上
            value[1] = map[x + 1][y]._visited;  //down
            value[2] = map[x][y - 1]._visited;  //left
        } else if (node._x == row - 1) {
            //右下
            value[0] = map[x - 1][y]._visited;  //up
            value[2] = map[x][y - 1]._visited;  //left
        } else {
            //右侧其他
            value[0] = map[x - 1][y]._visited;  //up
            value[1] = map[x + 1][y]._visited;  //down
            value[2] = map[x][y - 1]._visited;  //left
        }
    } else if (node._x == 0) {              //上侧 不包含两角
        value[1] = map[x + 1][y]._visited;  //down
        value[2] = map[x][y - 1]._visited;  //left
        value[3] = map[x][y + 1]._visited;  //right

    } else if (node._x == row - 1) {        //下侧 不包含两角
        value[0] = map[x - 1][y]._visited;  //up
        value[2] = map[x][y - 1]._visited;  //left
        value[3] = map[x][y + 1]._visited;  //right
    } else {
        //非边界节点
        value[0] = map[x - 1][y]._visited;  //up
        value[1] = map[x + 1][y]._visited;  //down
        value[2] = map[x][y - 1]._visited;  //left
        value[3] = map[x][y + 1]._visited;  //right
    }
    //cout << "上下左右:" << value[0] << value[1] << value[2] << value[3] << endl;
    flag = value[0] & value[1] & value[2] & value[3];  //成真赋值为1111
    return flag;
}
void Maze::break_the_wall(Node A, int direcion) {  //拆墙
    int x = A._x;
    int y = A._y;

    switch (direcion) {
        case 0:  //上
            map[x][y]._up = true;
            map[x - 1][y]._down = true;
            break;
        case 1:  //下
            map[x][y]._down = true;
            map[x + 1][y]._up = true;
            break;
        case 2:  //左
            map[x][y]._left = true;
            map[x][y - 1]._right = true;
            break;
        case 3:  //右
            map[x][y]._right = true;
            map[x][y + 1]._left = true;
            break;
    }
}
void Maze::print_visited() {
    for (int i = 0; i < row; i++) {
        cout << "#" << setw(3) << i + 1 << " ";
        for (int j = 0; j < column; j++) {
            cout << map[i][j]._visited << " ";
        }
        cout << endl;
    }
}
void Maze::reset() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            map[i][j]._down = false;
            map[i][j]._up = false;
            map[i][j]._left = false;
            map[i][j]._right = false;
            map[i][j]._visited = false;
        }
    }
    cout << "Maze rested" << endl;
}
void example_output() {
    cout << "Example Output: " << endl;
    cout << "████████████" << endl;  //96,88
    cout << "██ 1 ██ 2 ██" << endl;
    cout << "██   ██   ██" << endl;
    cout << "██ 3    4 ██" << endl;
    cout << "████████████" << endl;
}
