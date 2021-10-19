//������ δʹ�ü̳�
#pragma once
#include <iostream>
template <class T>
struct LinkNode  //���
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
class List {
   public:
    List() { first = new LinkNode<T>; }
    List(const T& x) { first = new LinkNode<T>(x); }
    List(List<T>& L);
    ~List() { makeEmpty(); }
    void makeEmpty();
    int Length() const;
    LinkNode<T>* getHead() const { return first; }
    LinkNode<T>* Search(T x);
    LinkNode<T>* Locate(int i);
    T* getData(int i);
    void setData(int i, T& x);
    bool Insert(int i, T& x);
    bool Remove(int i, T& x);
    bool IsEmpty() const {
        if (first->data == NULL)
            return true;
        else
            return false;
    }
    bool IsFull() const {
        return false;
    }
    void Sort();
    void input();
    void output();
    List<T>& operator=(List<T>& L);
    void inputFront(T endTag);  //ǰ�巨����������
    void inputRear(T endTag);   //��巨����������
   protected:
    LinkNode<T>* first;  //�����ͷָ��
};

template <class T>
List<T>::List(List<T>& L) {
    T value;
    LinkNode<T>* srcptr = L.getHead();  //�����������ͷ���λ��
    LinkNode<T>* destptr = first = new LinkNode<T>;
    while (srcptr->link != NULL) {
        //����ڵ㸴��
        value = srcptr->link->data;
        destptr->link = new LinkNode<T>(value);
        destptr = destptr->link;
        srcptr = srcptr->link;
    }
    destptr->link = NULL;
}

template <class T>
void List<T>::makeEmpty() {
    //��������Ϊ�ձ�
    LinkNode<T>* q;
    while (first->link != NULL) {
        q = first->link;
        first->link = q->link;  //���汻ɾ��㣬������ժ�¸ý��
        delete q;
    }
}

template <class T>
int List<T>::Length() const {
    //���������ͷ���ĵ�����ĳ���
    LinkNode<T>* p = first->link;
    int count = 0;
    while (p != NULL) {
        p = p->link;
        count++;
    }
    return count;
}

template <class T>
LinkNode<T>* List<T>::Search(T x) {
    //�ڱ�������������x�Ľ�㣬�����ɹ�ʱ�������ظý���ַ�����򷵻�NULL
    LinkNode<T>* current = first->link;
    while (current != NULL) {
        if (current->data == x)
            break;
        else
            current = current->link;
    }
    return current;
}

template <class T>
LinkNode<T>* List<T>::Locate(int i) {
    if (i < 0)  //i������
        return NULL;
    LinkNode<T>* current = first;
    int k = 0;
    while (current != NULL && k < i) {
        current = current->link;
        k++;
    }
    return current;  //���ص�i������ַ��������NULL��iֵ̫��
}

template <class T>
T* List<T>::getData(int i) {
    //ȡ�������е�i��Ԫ�ص�ֵ
    if (i <= 0)  //iֵ̫С
        return NULL;
    LinkNode<T>* current = Locate(i);  //��λ��i
    if (current == NULL)               //iֵ̫��
        return NULL;
    return &current->data;
}

template <class T>
void List<T>::setData(int i, T& x) {
    if (i <= 0)  //iֵ̫С
        return;
    LinkNode<T>* current = Locate(i);
    if (current == NULL)  //iֵ̫��
        return;
    else
        current->data = x;
}

template <class T>
bool List<T>::Insert(int i, T& x) {
    //����Ԫ��x�����������е�i�����֮��
    LinkNode<T>* current = Locate(i);
    if (current == NULL)  //���벻�ɹ�
        return false;
    LinkNode<T>* newNode = new LinkNode<T>(x);
    if (newNode == NULL) {
        std::cerr << "�洢�������" << std::endl;
        exit(1);
    }
    newNode->link = current->link;  //���ӵ�current֮��
    current->link = newNode;
    return true;  //����ɹ�
}

template <class T>
bool List<T>::Remove(int i, T& x) {
    //�������еĵ�i��Ԫ��ɾȥ��ͨ�������Ͳ���x���ظ�Ԫ�ص�ֵ
    LinkNode<T>* current = Locate(i - 1);
    if (current == NULL || current->link == NULL)  //ɾ�����ɹ�
        return false;
    LinkNode<T>* del = current->link;  //del����Ϊcurrent�ĺ��
    current->link = del->link;         //currentָ��ɾ��λ�õ���һ��
    x = del->data;                     //ȡ��ɾ��λ�õ�ֵ
    delete del;
    return true;  //ɾ���ɹ�
}

template <class T>
void List<T>::output() {
    //��������������������������������ݰ��߼�˳���������Ļ��
    //int i = 0;
    LinkNode<T>* current = first->link;
    while (current != NULL) {
        std::cout << current->data << std::endl;
        current = current->link;
    }
}
//2021��10��19��17:57:27

template <class T>
List<T>& List<T>::operator=(List<T>& L) {
    //���غ�������ֵ��������ʽ��A=B
    //����A�ǵ��ô˲�����List����B����������������Ͳ���L��ϵ�ʵ��
    T value;
    LinkNode<T>* srcptr = L.getHead();  //�����Ʊ�ĸ���ͷ����ַ
    LinkNode<T>* destptr = first = new LinkNode<T>;
    while (srcptr->link != NULL) {
        value = srcptr->link->data;
        destptr->link = new LinkNode<T>(value);
        destptr = destptr->link;
        srcptr = srcptr->link;
    }
    destptr->link = NULL;
    return *this;  //���ز��������ַ
}

template <class T>
void List<T>::inputFront(T endTag) {
    //ǰ�巨����������
    //endTag��Լ�����������н����ı�־�����������������������endTag������0���߸���
    LinkNode<T>* newNode;
    T val;
    first = new LinkNode<T>;  //first->linkĬ��ֵΪNULL
    if (first == NULL) {
        std::cerr << "�洢�������" << std::endl;
        exit(1);
    }
    std::cin >> val;
    while (val != endTag) {
        newNode = new LinkNode<T>(val);  //�����½��
        if (newNode == NULL) {
            std::cerr << "�洢�������" << std::endl;
            exit(1);
        }
        newNode->link = first->link;
        first->link = newNode;  //���뵽��ǰ��
        std::cin >> val;
    }
}

template <class T>
void List<T>::inputRear(T endTag) {
    //��巨����������
    LinkNode<T>*newNode, *last;  //βָ��
    T val;
    first = new LinkNode<T>;  //��������ͷ���
    if (first == NULL) {
        std::cerr << "�洢�������" << std::endl;
        exit(1);
    }
    std::cin >> val;
    last = first;
    while (val != endTag) {
        newNode = new LinkNode<T>(val);  //�����½��
        if (newNode == NULL) {
            std::cerr << "�洢�������" << std::endl;
            exit(1);
        }
        last->link = newNode;
        last = newNode;
        std::cin >> val;
    }
    last->link = NULL;  //����β
}