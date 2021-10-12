//顺序栈
#pragma once
#include <assert.h>
#include <iostream>
#include "Stack.h"
using namespace std;
const int StackIncreament = 20;  //栈溢出时扩展空间的增量
template <class T>
class SeqStack : public Stack<T> {
   public:
    SeqStack(int sz = 50);              //建立一个空栈
    ~SeqStack() { delete[] elements; }  //析构函数
    void Push(const T& x);              //IsFull则溢出处理，否则x插入到栈的栈顶
    bool Pop(T& x);                     //IsEmpty则不执行退栈
    bool getTop(T& x);                  //IsEmpty返回false
    bool IsEmpty() const {
        return (top == -1) ? true : false;
    }
    bool IsFull() const {
        return (top == maxSize - 1) ? true : false;
    }
    int getSize() const { return top + 1; }
    void MakeEmpty() { top = -1; }                            //清空栈的内容
    friend ostream& operator<<(ostream& os, SeqStack<T>& s);  //重载<<输出栈的内容

   private:
    T* elements;             //存放栈中元素的栈数组
    int top;                 //栈顶指针
    int maxSize;             //栈最大可容纳元素个数
    void OverflowProcess();  //栈的溢出处理
};

template <class T>
SeqStack<T>::SeqStack(int sz)
    : top(-1), maxSize(sz) {
    //建立一个最大尺寸为sz的空栈，若分配不成功则错误处理
    elements = new T[maxSize];
    assert(elements != NULL);  //断言：动态储存分配成功
}

template <class T>
void SeqStack<T>::OverflowProcess() {
    //私有函数，扩充栈的储存空间
    T* newArray = new T[maxSize + StackIncreament];
    if (newArray == NULL) {
        cerr << "存储分配失败！" << endl;
        exit(1);
    }
    for (int i = 0; i <= top; i++)
        newArray[i] = elements[i];
    maxSize = maxSize + StackIncreament;
    delete[] elements;
    elements = newArray;
}

template <class T>
void SeqStack<T>::Push(const T& x) {
    if (IsFull() == true)
        OverflowProcess();
    elements[++top] = x;  //栈顶指针先加1，再进栈
}

template <class T>
bool SeqStack<T>::Pop(T& x) {
    if (IsEmpty() == true)
        return false;
    x = elements[top--];  //退栈，栈顶指针减1
    return true;
}

template <class T>
bool SeqStack<T>::getTop(T& x) {
    if (IsEmpty() == true)
        return false;
    x = elements[top];
    return true;
}

template <class T>
ostream& operator<<(ostream& os, SeqStack<T>& s) {
    //输出栈中元素的重载操作<<
    os << "top = " << s.top << endl;  //输出栈顶位置
    for (size_t i = 0; i <= s.top; i++) {
        os << i << "：" << s.elements[i] << endl;
        return os;
    }
}