//线性表的抽象基类
#pragma once
template <class T>
class LinearList {
   public:
    LinearList(){};
    ~LinearList(){};
    virtual int Size() const = 0;                 //求空间大小
    virtual int Length() const = 0;               //求长度
    virtual int Search(T& x) const = 0;           //搜索
    virtual int Locate(int i) const = 0;          //定位
    virtual bool getData(int i, T& x) const = 0;  //读取
    virtual bool setData(int i, T&& x) = 0;       //修改
    virtual bool Insert(int i, T& x) = 0;         //插入
    virtual bool Remove(int i, T& x) = 0;         //删除
    virtual bool IsEmpty() const = 0;             //判断空
    virtual bool IsFull() const = 0;              //判断满
    virtual void Sort() = 0;
    virtual void input() = 0;                                //输入
    virtual void output() = 0;                               //输出
    virtual LinearList<T>& operator=(LinearList<T>& L) = 0;  //复制
};
