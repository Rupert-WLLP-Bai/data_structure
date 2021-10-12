#include <iostream>
#include <vector>
#include "BSTree.h"
#include "tools.h"
using namespace std;

//1. 获取操作 第一次只能选择建立(可以输入为空)
void first_input(BSTree<int>& tree) {
    while (1) {
        vector<int> num;  //存放建立BSTree的Vector
        print_menu();
        int choice = fetch_choice();
        if (choice == QUIT) {
            cout << "Exit in first input" << endl;
            tree.destory();
            exit(0);
        } else if (choice != CREATE) {
            cout << "第一次只能选择建立操作，输入回车即建立空树,按回车继续" << endl;
            getchar();
            system("clear");
            continue;
        } else {
            int temp;
            cout << "输入一些数(用空格分隔)以建立二叉排序树，输入回车则建立空树" << endl;
            while (1) {
                cin >> temp;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(INT32_MAX, '\n');
                    cout << "输入错误！" << endl;
                    num.clear();
                    continue;
                } else {
                    num.push_back(temp);
                    for (vector<int>::iterator it = num.begin(); it != num.end(); it++) {
                        tree.insert(*it);
                    }
                    cout << "BSTree is :" << endl;
                    tree.inOrder();
                    cout << endl;
                    return;
                }
            }
        }
    }
}
//2. 第二次开始禁用建立操作 只能选择插入 查询 退出
void other_input(BSTree<int>& tree) {
    while (1) {
        int choice = fetch_choice();
        if (choice == QUIT) {
            cout << "Exit in input" << endl;
            tree.destory();
            exit(0);
        } else if (choice == CREATE) {
            cout << "BSTree已存在，请使用插入和查询操作" << endl;
            continue;
        } else if (choice == INSERT) {
            while (1) {
                int temp;
                cout << "输入插入的数" << endl;
                cin >> temp;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(INT32_MAX, '\n');
                    cout << "输入错误！" << endl;
                    continue;
                } else {
                    tree.insert(temp);
                    break;
                }
            }

        } else if (choice == SEARCH) {
            while (1) {
                int temp;
                cout << "输入搜索的数" << endl;
                cin >> temp;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(INT32_MAX, '\n');
                    cout << "输入错误！" << endl;
                    continue;
                } else {
                    BSNode<int>* val = tree.search_recursion(temp);
                    if (val != nullptr)
                        cout << "查找成功" << endl;
                    else
                        cout << "查找失败" << endl;
                    break;
                }
            }
        }
    }
}
//主循环 (程序主体)
void Solution() {
    BSTree<int> tree;
    //第一次输入建立
    first_input(tree);
    //其他输入
    other_input(tree);
}

//主函数
int main() {
    Solution();
    return 0;
}