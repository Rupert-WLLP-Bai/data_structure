<<<<<<< HEAD
//表达式计算
//输入表达式建立二叉树
=======
//表达式计算
//输入表达式建立二叉树
#include <iostream>
#include <string>
#include "BinTree.h"
using namespace std;
template <class T>
void print(BinTreeNode<T>* p) {
    cout << p->data << " ";
}

void create() {
    BinaryTree<string> tree;       //存放表达式的二叉树(数用string存储，可实现大数的计算)
    cout << "输入表达式" << endl;  //输入提示
    cin >> tree;                   //输入表达式建立二叉树(广义表形式)
    cout << "前序遍历" << endl;
    tree.preOrder(print);  //前序遍历
    cout << endl;

    cout << "中序遍历" << endl;
    tree.inOrder(print);
    cout << endl;

    cout << "后序遍历" << endl;
    tree.postOrder(print);
    cout << endl;
}
>>>>>>> develop
