//Maze.h �Թ�
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
    int _x, _y;                      //�����꣬������
    bool _visited;                   //�Ƿ񱻷���
    bool _up, _down, _left, _right;  //�������ҵ�ǽ
    Node(int x = 0, int y = 0, bool visited = false, bool up = false, bool down = false, bool left = false, bool right = false) {
        _x = x;
        _y = y;
        _visited = visited;
        _up = up;
        _down = down;
        _left = left;
        _right = right;
    }  //���ι���
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
    Node start;                                                           //���
    Node end;                                                             //����
    Node offset[4] = {Node(-1, 0), Node(1, 0), Node(0, -1), Node(0, 1)};  //ƫ���� �ֱ�����������
    int row;                                                              //����
    int column;                                                           //����
    vector<vector<Node>> map;                                             //��Ŷ�ά�Ľڵ�ͼ
    stack<Node> L;                                                        //��¼·��
    bool search_neighbors(Node A);                                        //�����ڽӽڵ�
    void break_the_wall(Node A, int direcion);                            //��ǽ
    void init(int R, int C) {
        row = R;             //����
        column = C;          //����
        start = Node(0, 0);  //��ʼ������յ�
        end = Node(row - 1, column - 1);

        vector<Node> temp;  //�м�vector����һ��
        for (int i = 0; i < row; i++) {
            temp.clear();  //����һ�����
            for (int j = 0; j < column; j++) {
                temp.push_back(Node(i, j));  //�ڵ㰴������
            }
            map.push_back(temp);  //����һ��
        }
    }

   public:
    Maze(int R = 10, int C = 10) { init(R, C); };
    ~Maze(){};
    void print_node_position();  //�������λ��
    void print_node_num();       //������
    void print_node_all();       //��ӡ������Ϣ(�ȴ�ȡһ�е������ٴ�ӡ)
    void print_the_wall();       //���ǽ
    void print_visited();
    void reset();  //����
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
    vector<Node> Line;  //һ�еĽڵ�����
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
    vector<Node> Line;  //һ�еĽڵ�����
    //cout << "Print_Node_All" << endl;
    for (int i = 0; i < row; i++) {
        Line.clear();
        for (int j = 0; j < column; j++) {  //�����һ��
            Line = map[i];                  //��ȡ��i�еĽڵ�����
            cout << "����";                   //������Ͻ�һ��ǽ
            if (Line[j]._up == false)
                cout << "������";  //����ڵ��Ϸ���ǽ
            else {
                cout << "   ";  //�������ǽ
            }
        }
        cout << "����" << endl;               //��������ڵ����Ͻǵ�ǽ������
        cout << "����";                       //����ڶ�������ߵ�ǽ
        for (int j = 0; j < column; j++) {  //����ڶ��У���������ǽ�����֣�

            if (Line[j]._right == false) {
                if (printnumber)
                    cout << hex << setw(3) << ID++;  //�������
                else
                    cout << "   ";
                cout << "����";  //����ڵ��ұߵ�ǽ
            } else {
                if (printnumber)
                    cout << hex << setw(3) << ID++;  //�������
                else
                    cout << "   ";
                cout << "  ";  //�������ǽ
            }
        }
        cout << endl;  //�������������
    }
    for (int i = 0; i < 5 * column + 2; i++)
        cout << "��";  //������һ��
    cout << endl;
}
bool Maze::search_neighbors(Node node) {  //����node���ڽӽڵ��Ƿ񶼱�����
    int value[4] = {1, 1, 1, 1};          //�ĸ����� ��˳������������ Ĭ��Ϊ1 �ѷ���
    bool flag;                            //����ֵ 0��ʾ��δ���ʵĽڵ� 1��ʾ��ǰ�ڵ���ջ
    int x = node._x;
    int y = node._y;

    if (node._y == 0) {  //���ڵ�
        if (node._x == 0) {
            //����
            value[1] = map[x + 1][y]._visited;  //down
            value[3] = map[x][y + 1]._visited;  //right
        } else if (node._x == row - 1) {
            //����
            value[0] = map[x - 1][y]._visited;  //up
            value[3] = map[x][y + 1]._visited;  //right
        } else {
            //�������
            value[0] = map[x - 1][y]._visited;  //up
            value[1] = map[x + 1][y]._visited;  //down
            value[3] = map[x][y + 1]._visited;  //right
        }
    } else if (node._y == column - 1) {  //�Ҳ�ڵ�
        if (node._x == 0) {
            //����
            value[1] = map[x + 1][y]._visited;  //down
            value[2] = map[x][y - 1]._visited;  //left
        } else if (node._x == row - 1) {
            //����
            value[0] = map[x - 1][y]._visited;  //up
            value[2] = map[x][y - 1]._visited;  //left
        } else {
            //�Ҳ�����
            value[0] = map[x - 1][y]._visited;  //up
            value[1] = map[x + 1][y]._visited;  //down
            value[2] = map[x][y - 1]._visited;  //left
        }
    } else if (node._x == 0) {              //�ϲ� ����������
        value[1] = map[x + 1][y]._visited;  //down
        value[2] = map[x][y - 1]._visited;  //left
        value[3] = map[x][y + 1]._visited;  //right

    } else if (node._x == row - 1) {        //�²� ����������
        value[0] = map[x - 1][y]._visited;  //up
        value[2] = map[x][y - 1]._visited;  //left
        value[3] = map[x][y + 1]._visited;  //right
    } else {
        //�Ǳ߽�ڵ�
        value[0] = map[x - 1][y]._visited;  //up
        value[1] = map[x + 1][y]._visited;  //down
        value[2] = map[x][y - 1]._visited;  //left
        value[3] = map[x][y + 1]._visited;  //right
    }
    //cout << "��������:" << value[0] << value[1] << value[2] << value[3] << endl;
    flag = value[0] & value[1] & value[2] & value[3];  //���渳ֵΪ1111
    return flag;
}
void Maze::break_the_wall(Node A, int direcion) {  //��ǽ
    int x = A._x;
    int y = A._y;

    switch (direcion) {
        case 0:  //��
            map[x][y]._up = true;
            map[x - 1][y]._down = true;
            break;
        case 1:  //��
            map[x][y]._down = true;
            map[x + 1][y]._up = true;
            break;
        case 2:  //��
            map[x][y]._left = true;
            map[x][y - 1]._right = true;
            break;
        case 3:  //��
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
    cout << "������������������������" << endl;  //96,88
    cout << "���� 1 ���� 2 ����" << endl;
    cout << "����   ����   ����" << endl;
    cout << "���� 3    4 ����" << endl;
    cout << "������������������������" << endl;
}
