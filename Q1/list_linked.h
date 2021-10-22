/*
@file:        linkedlist.h
@description: 单链表
@version:     v1.0.1
@author:      Laobai
@time:        2021年10月22日22:25:49
*/

/*
update notes:

v1.0.0 2021年9月16日 14:55:52
    TODO in v1.0.1:
        1. input,sort实现
        2. 考虑实现继承list.h
        3. 注释的位置放在某一行的上一行(***改掉行尾注释)
        4. 把链表的实现全部放在外面
        5. 类内的函数写注释

v1.0.1 2021年10月22日22:25:49
    TODO in v1.0.2:    
        1. input,sort实现
        2. 考虑实现继承list.h
*/

#pragma once
#include <iostream>

//结点
template <class T>
struct LinkNode {
    T data;
    LinkNode<T>* link;
    LinkNode(LinkNode<T>* ptr = NULL) {
        link = ptr;
    }
    LinkNode(const T& item, LinkNode<T>* ptr = NULL) {
        data = item;
        link = ptr;
    }
};

template <class T>
class List {
   public:
    List() { first = new LinkNode<T>; }               //无参构造
    List(const T& x) { first = new LinkNode<T>(x); }  //带参构造
    List(List<T>& L);                                 //拷贝构造
    ~List() { makeEmpty(); }                          //析构
    void makeEmpty();                                 //表置空
    int Length() const;                               //返回长度
    LinkNode<T>* getHead() const { return first; }    //返回头结点地址
    LinkNode<T>* Search(T x);                         //搜索表中是否有value为x的结点
    LinkNode<T>* Locate(int i);                       //返回第i个元素的结点地址
    T* getData(int i);                                //返回第i个元素的vaule的地址
    void setData(int i, T& x);                        //修改第i个元素的value为x
    bool Insert(int i, T& x);                         //在第i个元素之后插入
    bool Remove(int i, T& x);                         //移除第i个结点
    bool IsEmpty() const;                             //判空
    bool IsFull() const;                              //判满
    void Sort();                                      //排序(未实现)
    void input();                                     //输入(未实现)
    void output();                                    //输出
    List<T>& operator=(List<T>& L);                   //重载赋值运算符
    void inputFront(T endTag);                        //前插法建立
    void inputRear(T endTag);                         //后插法建立
   protected:
    LinkNode<T>* first;  //链表的头指针
};

template <class T>
List<T>::List(List<T>& L) {
    T value;
    LinkNode<T>* srcptr = L.getHead();  //被复制链表的头结点位置
    LinkNode<T>* destptr = first = new LinkNode<T>;
    while (srcptr->link != NULL) {
        //逐个节点复制
        value = srcptr->link->data;
        destptr->link = new LinkNode<T>(value);
        destptr = destptr->link;
        srcptr = srcptr->link;
    }
    destptr->link = NULL;
}

//将链表置为空表
template <class T>
void List<T>::makeEmpty() {
    LinkNode<T>* q;
    while (first->link != NULL) {
        q = first->link;
        first->link = q->link;  //保存被删结点，从链上摘下该结点
        delete q;
    }
}

//计算带附加头结点的单链表的长度
template <class T>
int List<T>::Length() const {
    LinkNode<T>* p = first->link;
    int count = 0;
    while (p != NULL) {
        p = p->link;
        count++;
    }
    return count;
}

//在表中搜索含数据x的结点，搜索成功时函数返回该结点地址，否则返回NULL
template <class T>
LinkNode<T>* List<T>::Search(T x) {
    LinkNode<T>* current = first->link;
    while (current != NULL) {
        if (current->data == x)
            break;
        else
            current = current->link;
    }
    return current;
}

//定位，返回第i个位置的结点地址
template <class T>
LinkNode<T>* List<T>::Locate(int i) {
    if (i < 0)  //i不合理
        return NULL;
    LinkNode<T>* current = first;
    int k = 0;
    while (current != NULL && k < i) {
        current = current->link;
        k++;
    }
    return current;  //返回第i个结点地址，若返回NULL则i值太大
}

//取出链表中第i个元素的值
template <class T>
T* List<T>::getData(int i) {
    if (i <= 0)  //i值太小
        return NULL;
    LinkNode<T>* current = Locate(i);  //定位到i
    if (current == NULL)               //i值太大
        return NULL;
    return &current->data;
}

//修改第i个元素的value为x
template <class T>
void List<T>::setData(int i, T& x) {
    if (i <= 0)  //i值太小
        return;
    LinkNode<T>* current = Locate(i);
    if (current == NULL)  //i值太大
        return;
    else
        current->data = x;
}

//将新元素x插入在链表中第i个结点之后
template <class T>
bool List<T>::Insert(int i, T& x) {
    LinkNode<T>* current = Locate(i);
    if (current == NULL)  //插入不成功
        return false;
    LinkNode<T>* newNode = new LinkNode<T>(x);
    if (newNode == NULL) {
        std::cerr << "存储分配错误！" << std::endl;
        exit(1);
    }
    newNode->link = current->link;  //链接到current之后
    current->link = newNode;
    return true;  //插入成功
}

//将链表中的第i个元素删去，通过引用型参数x返回该元素的值
template <class T>
bool List<T>::Remove(int i, T& x) {
    LinkNode<T>* current = Locate(i - 1);
    if (current == NULL || current->link == NULL)  //删除不成功
        return false;
    LinkNode<T>* del = current->link;  //del定义为current的后继
    current->link = del->link;         //current指向删除位置的下一个
    x = del->data;                     //取出删除位置的值
    delete del;
    return true;  //删除成功
}

//判空
template <class T>
bool List<T>::IsEmpty() const {
    if (first->data == NULL)
        return true;
    else
        return false;
}

//判满
template <class T>
bool List<T>::IsFull() const {
    return false;
}

//单链表输出函数：将单链表中所有数据按逻辑顺序输出到屏幕上
template <class T>
void List<T>::output() {
    LinkNode<T>* current = first->link;
    while (current != NULL) {
        std::cout << current->data << std::endl;
        current = current->link;
    }
}

//重载函数：赋值操作，形式如A=B
//其中A是调用此操作的List对象，B是与参数表中引用型参数L结合的实参
template <class T>
List<T>& List<T>::operator=(List<T>& L) {
    T value;
    LinkNode<T>* srcptr = L.getHead();  //被复制表的附加头结点地址
    LinkNode<T>* destptr = first = new LinkNode<T>;
    while (srcptr->link != NULL) {
        value = srcptr->link->data;
        destptr->link = new LinkNode<T>(value);
        destptr = destptr->link;
        srcptr = srcptr->link;
    }
    destptr->link = NULL;
    return *this;  //返回操作对象地址
}

//前插法建立单链表
//endTag是约定的输入序列结束的标志。如果输入序列是正整数，endTag可以是0或者负数
template <class T>
void List<T>::inputFront(T endTag) {
    LinkNode<T>* newNode;
    T val;
    first = new LinkNode<T>;  //first->link默认值为NULL
    if (first == NULL) {
        std::cerr << "存储分配错误！" << std::endl;
        exit(1);
    }
    std::cin >> val;
    while (val != endTag) {
        newNode = new LinkNode<T>(val);  //创建新结点
        if (newNode == NULL) {
            std::cerr << "存储分配错误！" << std::endl;
            exit(1);
        }
        newNode->link = first->link;
        first->link = newNode;  //插入到表前端
        std::cin >> val;
    }
}

//后插法建立单链表
template <class T>
void List<T>::inputRear(T endTag) {
    LinkNode<T>*newNode, *last;  //尾指针
    T val;
    first = new LinkNode<T>;  //新链表附加头结点
    if (first == NULL) {
        std::cerr << "存储分配错误！" << std::endl;
        exit(1);
    }
    std::cin >> val;
    last = first;
    while (val != endTag) {
        newNode = new LinkNode<T>(val);  //创建新结点
        if (newNode == NULL) {
            std::cerr << "存储分配错误！" << std::endl;
            exit(1);
        }
        last->link = newNode;
        last = newNode;
        std::cin >> val;
    }
    last->link = NULL;  //表收尾
}
