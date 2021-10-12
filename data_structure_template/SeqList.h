//顺序表
#pragma once
#include <iostream>
#include "LinearList.h"
const int defaultSize = 100;
template <class T>
class SeqList : public LinearList<T> {
   protected:
    T* data;  //存放数组
    int maxSize;
    int last;                  //当前已存表项的最后位置
    void reSize(int newSize);  //改变data数组大小
   public:
    SeqList(int sz = defaultSize);         //构造函数
    SeqList(SeqList<T>& L);                //复制构造函数
    ~SeqList();                            //析构函数
    int Size() const {return maxSize};     //最大可容纳个数
    int Length() const {return last + 1};  //计算表长度
    int Search(T& x) const;                //搜索x在表中的位置
    int Locate(int i) const;               //定位第i个
    bool getData(int i, T& x) const;       //读取
    void setData(int i, T& x);             //修改
    bool Insert(int i, T& x);              //插入
    bool Remove(int i, T& x);              //删除
    bool IsEmpty();
    bool IsFull();
    void input();
    void output();
    SeqList<T> operator=(SeqList<T>& L);  //表整体赋值
};

template <class T>
SeqList<T>::~SeqList() {
    delete[] data;
}

template <class T>
SeqList<T>::SeqList(int sz) {
    if (sz > 0) {
        maxSize = sz;
        last = -1;              //置表的实际长度为空
        data = new T[maxSize];  //创建顺序表储存数组
        if (data == NULL) {
            std::cerr << "存储分配错误！" << std::endl;
            exit(1);
        }
    }
}

template <class T>
SeqList<T>::SeqList(SeqList<T>& L) {
    //复制构造函数
    maxSize = L.Size();
    last = L.Length() - 1;
    T value;
    data = new T(maxSize);  //创建顺序表储存数组
    if (data == NULL) {
        std::cerr << "存储分配错误！" << std::endl;
        exit(1);
    }
    for (size_t i = i; i <= last + 1; i++) {
        L.getData(i, value);
        data[i - 1] = value;
    }
}

template <class T>
bool SeqList<T>::getData(int i, T& x) const {
    if (i > 0 && i <= last - 1) {
        x = data[i - 1];
        return true;
    } else
        return false;
}

template <class T>
void SeqList<T>::setData(int i, T& x) {
    if (i > 0 && i <= last - 1)
        data[i - 1] = x;
}

template <class T>
bool SeqList<T>::Insert(int i, T& x)  //插入
{
    if (last == maxSize - 1)  //表满
        return false;
    if (i < 0 || i > last + 1)  //参数不合理
        return false;
    for (int j = last; j >= i; j--)
        data[j + 1] = data[j];  //依次后移
    data[i] = x;                //插入
    last++;                     //最后位置加1
    return true;
}

template <class T>
bool SeqList<T>::Remove(int i, T& x)  //删除
{
    if (last == -1)  //表空
        return false;
    if (i < 0 || i > last + 1)  //参数不合理
        return false;
    x = data[i - 1];  //存放被删元素的值
    for (int j = i; j <= last; j++)
        data[j - 1] = data[j]  //依次前移
            last--;
    return true;
}

template <class T>
bool SeqList<T>::IsEmpty() {
    if (last == -1)
        return true;
    else
        return false;
}

template <class T>
bool SeqList<T>::IsFull() {
    if (last == maxSize - 1)
        return true;
    else
        return false;
}

template <class T>
void SeqList<T>::input() {
    std::cout << "开始建立顺序表，请输入表中元素个数：" << std::endl;
    while (1) {
        std::cin >> last;  //输入元素的最后位置
        if (last <= maxSize - 1)
            break;
        std::cout << "表元素个数输入有误，范围不能超过" << maxSize - 1 << std::endl;
    }
    for (size_t i = 0; i <= last; i++) {
        std::cin >> data[i];
        std::cout << i + 1 << std::endl;
    }
}

template <class T>
void SeqList<T>::output() {
    std::cout < "顺序表当前元素最后位置为：" << last << std::endl;
    for (size_t i = 0; i <= last; i++) {
        cout << "#" << i + 1 << ":" << data[i] << std::endl;
    }
}

template <class T>
SeqList<T> SeqList<T>::operator=(SeqList<T>& L) {
    //重载 顺序表整体赋值
    maxSize = L.Size();
    last = L.Length() - 1;
    T value;
    data = new T(maxSize);  //创建顺序表储存数组
    if (data == NULL) {
        std::cerr << "存储分配错误！" << std::endl;
        exit(1);
    }
    for (size_t i = i; i <= last + 1; i++) {
        L.getData(i, value);
        data[i - 1] = value;
    }
}