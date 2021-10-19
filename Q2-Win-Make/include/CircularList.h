//单向循环链表
#pragma once
#include <iomanip>
#include <iostream>
using namespace std;

template <class T>
struct CircLinkNode  //链表结点定义
{
    T data;
    CircLinkNode<T>* Link;
    CircLinkNode(CircLinkNode<T>* Link = NULL)
        : Link(Link){};
    CircLinkNode(T d, CircLinkNode<T>* Link = NULL)
        : data(d), Link(Link) {}
};

template <class T>
class CircList  //链表类定义
{
   public:
    CircList();                                            //无参构造函数
    CircList(const T& x);                                  //构造函数
    CircList(CircList<T>& L);                              //复制构造函数
    ~CircList(){};                                         //析构函数
    int Length() const { return length; }                  //计算循环链表长度
    bool IsEmpty() { return length == 0 ? true : false; }  //判空
    CircLinkNode<T>* getHead() const { return head; }      //返回附加头结点地址
    CircLinkNode<T>* Search(T x);                          //搜索含数据x的元素
    CircLinkNode<T>* Locate(int i);                        //搜索第i个元素的地址
    T* getData(int i);                                     //取出第i个元素的值
    void setData(int i, T& x);                             //用x修改第i个元素的值
    bool Insert(int i, T& x);                              //在第i个元素后插入x
    bool Remove(int i, T& x);                              //删除第i个元素，x返回该元素的值
    void output();                                         //输出

   private:
    CircLinkNode<T>* head;  //头指针
    int length;             //链表长度
};

template <class T>
CircList<T>::CircList() {
    //无参构造
    length = 0;
    head = new CircLinkNode<T>;
    head->Link = head;
}

template <class T>
CircList<T>::CircList(const T& x) {
    //带参构造
    length = 0;
    head = new CircLinkNode<T>;
    CircLinkNode<T>* newNode = new CircLinkNode<T>(x);
    head->Link = newNode;
    newNode->Link = head;
    length++;
}

template <class T>
CircList<T>::CircList(CircList<T>& L) {
    //拷贝构造
    length = 0;
    T value;
    CircLinkNode<T>* srcptr = L.getHead();  //被复制链表的头结点位置
    //cout << "srcptr的头结点地址为:" << srcptr << endl;
    //cout << "srcptr的下一结点地址为:" << srcptr->Link << endl;
    head = new CircLinkNode<T>;
    CircLinkNode<T>* destptr = head;
    //cout << "destptr的头结点地址为:" << head << endl;
    while (srcptr->Link != L.getHead()) {
        //逐个节点复制
        value = srcptr->Link->data;
        destptr->Link = new CircLinkNode<T>(value);
        destptr = destptr->Link;
        srcptr = srcptr->Link;
        length++;
    }
    destptr->Link = head;
}

template <class T>
CircLinkNode<T>* CircList<T>::Search(T x) {
    //搜索元素x的地址
    CircLinkNode<T>* current = head->Link;
    while (current != head) {
        if (current->data == x)
            return current;
        else
            current = current->Link;
    }
    return NULL;  //未找到
}

template <class T>
CircLinkNode<T>* CircList<T>::Locate(int i) {
    if (i < 0 || i > length)
        return NULL;
    CircLinkNode<T>* current = head;
    while (i--) {
        current = current->Link;
    }
    return current;
}

template <class T>
T* CircList<T>::getData(int i) {
    if (i <= 0 || i > length)
        return NULL;
    CircLinkNode<T>* current = Locate(i);  //定位到第i个元素的位置
    return &current->data;                 //返回data的地址
}
template <class T>
void CircList<T>::setData(int i, T& x) {
    if (i <= 0 || i > length)
        return;
    else {
        CircLinkNode<T>* current = Locate(i);
        current->data = x;
    }
}

template <class T>
bool CircList<T>::Insert(int i, T& x) {
    CircLinkNode<T>* current = Locate(i);
    if (current == NULL)
        return false;  //插入不成功
    CircLinkNode<T>* newNode = new CircLinkNode<T>(x);
    if (newNode == NULL) {
        cerr << "存储分配错误！" << endl;
        exit(1);
    }
    newNode->Link = current->Link;  //链接到current之后
    current->Link = newNode;
    length++;     //长度+1
    return true;  //插入成功
}

template <class T>
bool CircList<T>::Remove(int i, T& x) {
    //将链表中的第i个元素删去，通过引用型参数x返回该元素的值
    if (IsEmpty() == true)
        return false;  //空表,删除失败
    CircLinkNode<T>* current = Locate(i - 1);
    if (current == NULL)
        return false;  //位置不对
    CircLinkNode<T>* del = current->Link;
    current->Link = del->Link;
    x = del->data;
    delete del;
    length--;
    return true;  //删除成功
}

template <class T>
void CircList<T>::output() {
    if (length == 0)
        cout << "(HEAD)NULL ， 空表" << endl;
    else {
        int num = 1;
        CircLinkNode<T>* current = head;
        while (current->Link != head) {
            current = current->Link;
            cout << current->data;
            cout << "(ID:" << num++ << ")";  //输出Id
            cout << " --> ";
        }
        cout << head->Link->data << "(HEAD)"
             << "  链表长度为：" << length << endl;
    }
}