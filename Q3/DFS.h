//DFS ��ʹ�ò��鼯
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>
#include "Maze.h"
//#include "backtrace.h"
using namespace std;

class DFS {
   public:
    void get_choice(bool* choice, int current, Maze A);
    bool search_neighbors(bool* neighbor_visited, int current, Maze A, vector<int> visited);
    void generate(Maze& A) {  //�����Թ�
        //const char* F[] = {"��", "��", "��", "��"};
        srand((unsigned)time(NULL));
        A.L.push(A.start);                              //��ʼλ����ջ
        A.map[A.start._x][A.start._y]._visited = true;  //�����Ϊ�ѱ�����
        int current_x, current_y;                       //���ڽڵ����ڵ�λ��
        current_x = A.start._x;                         //���
        current_y = A.start._y;                         //���
        //cout << "start = (" << A.start._x << "," << A.start._y << ")" << endl;
        while (A.L.top() != A.end) {                                 //δ�ߵ��յ� �����ڽӽڵ�
            if (!A.search_neighbors(A.map[current_x][current_y])) {  //�ڽӽڵ���δ�����ʵĽڵ�
                int direction;                                       //����
                while (1) {
                    int _x, _y;  //�����꣬������
                    _x = current_x;
                    _y = current_y;
                    direction = rand() % 4;  //�ĸ�����
                    if (direction == 0)
                        _x--;
                    else if (direction == 1)
                        _x++;
                    else if (direction == 2)
                        _y--;
                    else
                        _y++;
                    if (_x < 0 || _x > A.row - 1 || _y < 0 || _y > A.column - 1)  //����
                        continue;
                    if (A.map[_x][_y]._visited == false)
                        break;
                }
                //cout << "direction = " << F[direction] << endl;
                //print_visited();
                A.break_the_wall(A.map[current_x][current_y], direction);      //��ǽ
                Node cur = A.map[current_x][current_y] + A.offset[direction];  //����λ��
                current_x = cur._x;                                            //����λ��
                current_y = cur._y;                                            //����λ��
                A.map[current_x][current_y]._visited = true;                   //���Ϊ�ѷ���
                A.L.push(A.map[current_x][current_y]);                         //�ڵ���ջ
                //cout << "current = (" << current_x << "," << current_y << ")" << endl;
            } else {
                A.L.pop();  //�ڵ���ջ
                //cout << "(" << current_x << "," << current_y << ")��ջ" << endl;
                current_x = A.L.top()._x;  //����λ��
                current_y = A.L.top()._y;
            }
            //print_the_wall();
            //A.print_node_all();
        }
    }
    void solve(Maze A);          //SOLVE
    void print_results(Maze A);  //Maze��Solution

   private:
    deque<int> solution;
};
void DFS::get_choice(bool* choice, int current, Maze A) {
    Node L = A.map[current / A.column][current % A.column];
    choice[0] = L._up;
    choice[1] = L._down;
    choice[2] = L._left;
    choice[3] = L._right;
}
void DFS::solve(Maze A) {
    srand((unsigned)time(NULL));
    vector<int> visited;  //��¼�Ѿ����ʵĵ�
    bool choice[4];
    int direction;
    int current = A.start._x * A.column + A.start._y;
    visited.push_back(current);                                     //�����
    solution.push_back(A.start._x * A.column + A.start._y);         //�������
    while (solution.back() != A.end._x * A.column + A.end._y) {     //�ߵ��յ�
        get_choice(choice, current, A);                             //��ȡ�ڵ�����ߵ�λ��
        bool flag = search_neighbors(choice, current, A, visited);  //�����ڽӽڵ�ķ������
        if (flag) {
            while (1) {  //���һ��λ��
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
bool DFS::search_neighbors(bool* choice, int current, Maze A, std::vector<int> visited) {
    int cur = current;
    if (choice[0]) {  //UP
        cur -= A.column;
        const vector<int>::iterator it = find(visited.begin(), visited.end(), cur);
        if (it != visited.end()) {  //�ҵ�
            choice[0] = false;
        }
        cur = current;  //�ظ�
    }
    if (choice[1]) {  //DOWN
        cur += A.column;
        const vector<int>::iterator it = find(visited.begin(), visited.end(), cur);
        if (it != visited.end()) {  //�ҵ�
            choice[1] = false;
        }
        cur = current;  //�ظ�
    }
    if (choice[2]) {  //LEFT
        cur -= 1;
        const vector<int>::iterator it = find(visited.begin(), visited.end(), cur);
        if (it != visited.end()) {  //�ҵ�
            choice[2] = false;
        }
        cur = current;  //�ظ�
    }
    if (choice[3]) {  //RIGHT
        cur += 1;
        const vector<int>::iterator it = find(visited.begin(), visited.end(), cur);
        if (it != visited.end()) {  //�ҵ�
            choice[3] = false;
        }
        cur = current;  //�ظ�
    }
    return (choice[0] || choice[1] || choice[2] || choice[3]);
}
void DFS::print_results(Maze A) {
    int ID = 0;
    const int printnumber = 0;
    // int max_digit = int(log10(row * column)) + 1;
    vector<Node> Line;  //һ�еĽڵ�����
    //cout << "Print_Node_All" << endl;
    for (int i = 0; i < A.row; i++) {
        Line.clear();
        for (int j = 0; j < A.column; j++) {  //�����һ��
            Line = A.map[i];                  //��ȡ��i�еĽڵ�����
            cout << "����";                     //������Ͻ�һ��ǽ
            if (Line[j]._up == false)
                cout << "������";  //����ڵ��Ϸ���ǽ
            else {
                cout << "\033[34m"
                     << "  "
                     << "\033[0m";  //�������ǽ
            }
        }
        cout << "����" << endl;                 //��������ڵ����Ͻǵ�ǽ������
        cout << "����";                         //����ڶ�������ߵ�ǽ
        for (int j = 0; j < A.column; j++) {  //����ڶ��У���������ǽ�����֣�

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
                cout << "\033[34m"
                     << "  "
                     << "\033[0m";  //�������ǽ
            }
        }
        cout << endl;  //�������������
    }
    for (int i = 0; i < 5 * A.column + 2; i++)
        cout << "��";  //������һ��
    cout << endl;
}