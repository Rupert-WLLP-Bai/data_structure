//双向链表
#pragma once
#include <iostream>
#include "LinearList.h"

template <class T>
struct DblNode  //链表结点类定义
{
    T data;                    //链表结点数据
    DblNode<T>*lLink, *rLInk;  //链表前驱（左链）、后继（右链）指针
    DblNode(DblNode<T>* left = NULL, DblNode<T>* right = NULL)
        : lLink(left), rLInk(right) {}  //构造函数
    DblNode(T value, DblNode<T>* left = NULL, DblNode<T>* right = NULL)
        : data(value), lLink(left), rLInk(right) {}  //构造函数
};

template <class T>
class DblList : public LinearList<T> {
   public:
    DblList(T uniqueVal);  //构造函数，建立附加头结点
    ~DblList();            //析构函数，释放所用储存
    int Length() const;    //计算双向链表的长度
    bool IsEmpty() { return first->rLInk == first; }
    DblNode<T>* getHead() const() { return first; }  //获取附加头结点地址
    void setHead(DblNode<T>* ptr) { first = ptr; }   //设置附加头结点地址
    DblNode<T>* Search(const T& x);
    DblNode<T>* Locate(int i, int d);  //d=0按前驱方向，d≠0按后继方向
    bool Insert(int i, const T& x, int d);
    bool Remove(int i, const T& x, int d);

   private:
    DblNode<T>* first;
};

template <class T>
DblList<T>::DblList(T uniqueVal) {
    //构造函数,包含一个用于某些特定情况的值
    first = new DblNode<T>(uniqueVal);
    if (first == NULL) {
        std::cerr << "存储分配错误！" << std::endl;
        exit(1);
    }
    first->rLInk = first->lLink = first;
}

template <class T>
int DblList<T>::Length() const {
    //计算带附加头结点的双向循环链表的长度，通过函数返回
    DblNode<T>* current = first->rLInk;
    int count = 0;
    while (current != first) {
        current = current->rLInk;
        count++;
    }
    return count;
}

template <class T>
DblNode<T>* DblList<T>::Search(const T& x) {
    DblNode<T>* current = first->rLInk;
    while (current != first && current->data != x)
        current = current->rLInk;  //沿着右边搜索
    if (current != first)          //搜索成功
        return current;
    else  //搜索失败
        return NULL;
}

template <class T>
DblNode<T>* DblList<T>::Locate(int i, int d) {
    //按d所指方向寻找第i个元素
    if (first->rLInk == first || i == 0)
        return first;
    DblNode<T>* current;
    if (d == 0)
        current = first->lLink;  //d=0 左侧
    else
        current = first->rLInk;
    for (int j = 1; j < i; j++) {
        if (current = first)
            break;
        else if (d == 0)
            current = current->lLInk;
        else
            current = current->rLink;
    }
    if (current != first)
        return current;
    else
        return NULL;
}

template <class T>
bool DblList<T>::Insert(int i, const T& x, int d) {
    DblNode<T>* current = LOcate(i, d);
    if (current == NULL)
        return false;
    DblNode<T>* newNode = new DblNode<T>(x);
    if (newNode == NULL) {
        std::cerr << "存储分配错误！" << std::endl;
        exit(1);
    }
    if (d == 0)  //前驱方向插入
    {
        newNode->lLink = current->lLink;
        current->lLink = newNode;
        newNode->lLink->rLInk = newNode;
        newNode->rLInk = current;
    } else  //后继方向插入
    {
        newNode->rLInk = current->rLInk;
        current->rLInk = newNode;
        newNode->rLInk->lLink = newNode;
        newNode->lLink = current;
    }
    return true;  //插入成功
}

template <class T>
bool DblList<T>::Remove(int i, const T& x, int d) {
    DblNode<T>* current = Locate(i, d);
    if (current == NULL)  //删除位置不合理
        return false;
    current->rLInk->lLink = current->lLink;  //删除
    current->lLink->rLInk = current->lLink;
    x = current->data;
    delete current;
    return true;
}