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

typedef struct N {  //定义节点
    int ID;
    bool visited;
    N(int id = 0, bool v = false) {
        ID = id;
        visited = v;
    }
} N;
typedef pair<int, int> P;  //一组ID表示一面墙
class Perfect_Maze {
   private:
    // vector<vector<N>> map;  //地图
    vector<P> wall;  //需要打破的墙
   public:
    Perfect_Maze(){};
    ~Perfect_Maze(){};
    void generate(Maze& A);
    int choose_neighbor(int cur, int row, int column);  //选择cur的邻居
    void print_wall_broken();                           //输出打破的墙
    void translate(Maze& A);                            //翻译wall的内容到Maze里
};

void Perfect_Maze::generate(Maze& A) {
    int Total = A.column * A.row;
    int count = 0;
    Union_Set U(Total);

    // vector<int> Visited;    //已被访问的id
    // vector<int> N_Visited;  //未被访问id

    // cout << "---------------------------------------赋值-----------------------------------------" << endl;
    //赋值
    // vector<N> temp;  //存一行
    // for (int i = 0; i < A.row; i++) {
    //     temp.clear();
    //     for (int j = 0; j < A.column; j++) {
    //         temp.push_back(N(i * A.column + j, false));
    //         N_Visited.push_back(i * A.column + j);
    //     }
    //     map.push_back(temp);
    // }
    // cout << "-------------------------------------赋值结束---------------------------------------" << endl;
    // cout << "---------------------------------------循环-----------------------------------------" << endl;
    //循环
    // while (N_Visited.size()) {  //所有节点都被访问跳出 但不能保证所有的都连接
    //     //在未访问的节点中任选一个ID
    //     //cout << "---------------------------------------随机-----------------------------------------" << endl;
    //     int cur = N_Visited[rand() % N_Visited.size()];
    //     //在其周围任选一个点 注意边界
    //     //cout << "---------------------------------------选点-----------------------------------------" << endl;
    //     int neighbor = choose_neighbor(cur, A.row, A.column);
    //     //判断两个点是否在一个集合 如果不是则合并 标记为访问
    //     if (!U.isSame(cur, neighbor)) {
    //         //cout << "---------------------------------------合并-----------------------------------------" << endl;
    //         U.join(cur, neighbor);
    //         //cout << "-------------------------------------标记cur---------------------------------------" << endl;
    //         map[cur / A.column][cur % A.column].visited = true;
    //         //cout << dec;
    //         //cout << "cur = " << cur << " neighbor = " << neighbor << endl;
    //         //cout << "(" << cur / A.column << "," << cur % A.column << ")"
    //         //<< "(" << neighbor / A.column << "," << neighbor % A.column << ")" << endl
    //         //<< endl;
    //         //cout << "---------------------------------V加入cur节点-------------------------------------" << endl;
    //         Visited.push_back(cur);
    //         //cout << "V_SIZE: " << Visited.size() << endl;
    //         //cout << "---------------------------------N删除cur节点-------------------------------------" << endl;
    //         N_Visited.erase(find(N_Visi迷宫][neighbor % A.column].visited == false) {
    //             //cout << "------------------------------N删除节点neighbor--------------------------------" << endl;
    //             N_Visited.erase(find(N_Visited.begin(), N_Visited.end(), neighbor));  //删除
    //             //cout << "------------------------------V加入节点neighbor--------------------------------" << endl;
    //             Visited.push_back(neighbor);
    //             //cout << "------------------------------标记neighbor--------------------------------" << endl;
    //             map[neighbor / A.column][neighbor % A.column].visited = true;
    //         }
    //         //cout << "-----------------------------cur和neighbor加入墙---------------------------------" << endl;
    //         wall.push_back(P(cur, neighbor));
    //         count++;
    //         //cout << "N_SIZE: " << N_Visited.size() << endl;
    //         //cout << "-------------------------------------删除结束---------------------------------------" << endl;
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
    // 输出
    //U.print();
    //print_wall_broken();

    //翻译
    translate(A);
}

int Perfect_Maze::choose_neighbor(int cur, int row, int column) {
    int ret = 0;
    int choice;
    //const char* F[] = {"上", "下", "左", "右"};
    while (1) {
        choice = rand() % 4;  //上下左右
        switch (choice) {
            case 0:  //上
                ret = cur - column;
                if (ret < 0)
                    continue;  //超限
                break;
            case 1:  //下
                ret = cur + column;
                if (ret > column * row - 1)
                    continue;  //超限
                break;
            case 2:  //左
                ret = cur - 1;
                if (cur % column == 0)
                    continue;  //超限
                break;
            case 3:  //右
                ret = cur + 1;
                if (ret % column == 0)
                    continue;  //超限
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