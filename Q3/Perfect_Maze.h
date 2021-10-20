#pragma once
#include <algorithm>
#include "Maze.h"
#include "Union_Set.h"
using namespace std;

/*W = all the wall
T = {}
number_of_components = N*N
while number_of_components > 1
  (u, v) = W.pop
  if component(u) != component(v)
    T << (u, v)
    merge component(u) and component(v)*/

typedef struct N {  //����ڵ�
    int ID;
    bool visited;
    N(int id = 0, bool v = false) {
        ID = id;
        visited = v;
    }
} N;
typedef pair<int, int> P;  //һ��ID��ʾһ��ǽ
class Perfect_Maze {
   private:
    // vector<vector<N>> map;  //��ͼ
    vector<P> wall;  //��Ҫ���Ƶ�ǽ
   public:
    Perfect_Maze(){};
    ~Perfect_Maze(){};
    void generate(Maze& A);
    int choose_neighbor(int cur, int row, int column);  //ѡ��cur���ھ�
    void print_wall_broken();                           //������Ƶ�ǽ
    void translate(Maze& A);                            //����wall�����ݵ�Maze��
};

void Perfect_Maze::generate(Maze& A) {
    int Total = A.column * A.row;
    int count = 0;
    Union_Set U(Total);

    // vector<int> Visited;    //�ѱ����ʵ�id
    // vector<int> N_Visited;  //δ������id

    // cout << "---------------------------------------��ֵ-----------------------------------------" << endl;
    //��ֵ
    // vector<N> temp;  //��һ��
    // for (int i = 0; i < A.row; i++) {
    //     temp.clear();
    //     for (int j = 0; j < A.column; j++) {
    //         temp.push_back(N(i * A.column + j, false));
    //         N_Visited.push_back(i * A.column + j);
    //     }
    //     map.push_back(temp);
    // }
    // cout << "-------------------------------------��ֵ����---------------------------------------" << endl;
    // cout << "---------------------------------------ѭ��-----------------------------------------" << endl;
    //ѭ��
    // while (N_Visited.size()) {  //���нڵ㶼���������� �����ܱ�֤���еĶ�����
    //     //��δ���ʵĽڵ�����ѡһ��ID
    //     //cout << "---------------------------------------���-----------------------------------------" << endl;
    //     int cur = N_Visited[rand() % N_Visited.size()];
    //     //������Χ��ѡһ���� ע��߽�
    //     //cout << "---------------------------------------ѡ��-----------------------------------------" << endl;
    //     int neighbor = choose_neighbor(cur, A.row, A.column);
    //     //�ж��������Ƿ���һ������ ���������ϲ� ���Ϊ����
    //     if (!U.isSame(cur, neighbor)) {
    //         //cout << "---------------------------------------�ϲ�-----------------------------------------" << endl;
    //         U.join(cur, neighbor);
    //         //cout << "-------------------------------------���cur---------------------------------------" << endl;
    //         map[cur / A.column][cur % A.column].visited = true;
    //         //cout << dec;
    //         //cout << "cur = " << cur << " neighbor = " << neighbor << endl;
    //         //cout << "(" << cur / A.column << "," << cur % A.column << ")"
    //         //<< "(" << neighbor / A.column << "," << neighbor % A.column << ")" << endl
    //         //<< endl;
    //         //cout << "---------------------------------V����cur�ڵ�-------------------------------------" << endl;
    //         Visited.push_back(cur);
    //         //cout << "V_SIZE: " << Visited.size() << endl;
    //         //cout << "---------------------------------Nɾ��cur�ڵ�-------------------------------------" << endl;
    //         N_Visited.erase(find(N_Visi�Թ�][neighbor % A.column].visited == false) {
    //             //cout << "------------------------------Nɾ���ڵ�neighbor--------------------------------" << endl;
    //             N_Visited.erase(find(N_Visited.begin(), N_Visited.end(), neighbor));  //ɾ��
    //             //cout << "------------------------------V����ڵ�neighbor--------------------------------" << endl;
    //             Visited.push_back(neighbor);
    //             //cout << "------------------------------���neighbor--------------------------------" << endl;
    //             map[neighbor / A.column][neighbor % A.column].visited = true;
    //         }
    //         //cout << "-----------------------------cur��neighbor����ǽ---------------------------------" << endl;
    //         wall.push_back(P(cur, neighbor));
    //         count++;
    //         //cout << "N_SIZE: " << N_Visited.size() << endl;
    //         //cout << "-------------------------------------ɾ������---------------------------------------" << endl;
    //     }
    // }
    srand((unsigned)time(NULL));
    while (1) {
        if (count == Total - 1)
            break;
        int cur = rand() % Total;
        int neighbor = choose_neighbor(cur, A.row, A.column);
        if (!U.isSame(cur, neighbor)) {
            U.join(cur, neighbor);
            wall.push_back(P(cur, neighbor));
            count++;
        }
    }
    // ���
    //U.print();
    //print_wall_broken();

    //����
    translate(A);
}

int Perfect_Maze::choose_neighbor(int cur, int row, int column) {
    int ret = 0;
    int choice;
    //const char* F[] = {"��", "��", "��", "��"};
    while (1) {
        choice = rand() % 4;  //��������
        switch (choice) {
            case 0:  //��
                ret = cur - column;
                if (ret < 0)
                    continue;  //����
                break;
            case 1:  //��
                ret = cur + column;
                if (ret > column * row - 1)
                    continue;  //����
                break;
            case 2:  //��
                ret = cur - 1;
                if (cur % column == 0)
                    continue;  //����
                break;
            case 3:  //��
                ret = cur + 1;
                if (ret % column == 0)
                    continue;  //����
                break;
        }
        break;
    }
    //cout << "Direction = " << F[choice] << endl;
    return ret;
}

void Perfect_Maze::print_wall_broken() {
    for (unsigned i = 0; i < wall.size(); i++) {
        cout << "(" << wall[i].first << "," << wall[i].second << ")"
             << "  ";
        if (i % 20 == 19)
            cout << endl;
    }
    cout << endl;
}

void Perfect_Maze::translate(Maze& A) {
    int cur_x, cur_y, neighbor_x, neighbor_y;
    for (unsigned i = 0; i < wall.size(); i++) {
        cur_x = wall[i].first / A.column;
        neighbor_x = wall[i].second / A.column;
        cur_y = wall[i].first % A.column;
        neighbor_y = wall[i].second % A.column;
        if (cur_x > neighbor_x) {  //UP
            A.map[cur_x][cur_y]._up = true;
            A.map[neighbor_x][cur_y]._down = true;
        } else if (cur_x < neighbor_x) {  //DOWN
            A.map[cur_x][cur_y]._down = true;
            A.map[neighbor_x][neighbor_y]._up = true;
        } else if (cur_y > neighbor_y) {  //LEFT
            A.map[cur_x][cur_y]._left = true;
            A.map[neighbor_x][neighbor_y]._right = true;
        } else {  //RIGHT
            A.map[cur_x][cur_y]._right = true;
            A.map[neighbor_x][neighbor_y]._left = true;
        }
    }
}