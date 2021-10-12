//链式栈
#include <assert.h>
#include <iostream>
using namespace std;

template <class T>
struct LinkNode  //结点
{
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
class LinkedStack {
   public:
    LinkedStack()
        : top(NULL) {}
    ~LinkedStack() { makeEmpty(); }
    void Push(const T& x);
    bool Pop(T& x);
    bool Pop();
    bool getTop(T& x) const;
    bool IsEmpty() const { return (top == NULL) ? true : false; }
    bool IsFull() const { return false; }
    int getSize() const;
    void makeEmpty();  //清空栈的内容
    friend ostream& operator<<(ostream& os, LinkedStack<T>& s);

   private:
    LinkNode<T>* top;  //栈顶指针，即链头指针
};

template <class T>
void LinkedStack<T>::makeEmpty() {
    LinkNode<T>* p;
    while (top != NULL) {
        p = top;
        top = top->link;
        delete p;
    }
}

template <class T>
void LinkedStack<T>::Push(const T& x) {
    top = new LinkNode<T>(x, top);
    assert(top != NULL);
}

template <class T>
bool LinkedStack<T>::Pop(T& x) {
    //删除栈顶结点，返回被删除栈顶元素的值
    if (IsEmpty() == true)
        return false;
    LinkNode<T>* p = top;
    top = top->link;
    x = p->data;
    delete p;
    return true;
}

template <class T>
bool LinkedStack<T>::Pop() {
    //删除栈顶结点
    if (IsEmpty() == true)
        return false;
    LinkNode<T>* p = top;
    top = top->link;
    delete p;
    return true;
}

template <class T>
bool LinkedStack<T>::getTop(T& x) const {
    if (IsEmpty() == true)
        return false;
    x = top->data;
    return true;
}

template <class T>
int LinkedStack<T>::getSize() const {
    LinkNode<T>* p = top;
    int k = 0;
    while (p != NULL) {
        p = p->link;
        k++;
    }
    return k;
}

template <class T>
ostream& operator<<(ostream& os, LinkedStack<T>& s) {
    os << "栈中元素的个数 = " << s.getSize() << endl;
    LinkNode<T>* p = s.top;
    int i = 0;
    while (p != NULL)
        os << ++i << "：" << p->data << endl;
    return os;
}

//LinkNode<T> *s =new LinkNode<T>[n]; 同时使用n个链式栈