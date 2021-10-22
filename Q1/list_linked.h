/*
@file:        linkedlist.h
@description: ������
@version:     v1.0.1
@author:      Laobai
@time:        2021��10��22��22:25:49
*/

/*
update notes:

v1.0.0 2021��9��16�� 14:55:52
    TODO in v1.0.1:
        1. input,sortʵ��
        2. ����ʵ�ּ̳�list.h
        3. ע�͵�λ�÷���ĳһ�е���һ��(***�ĵ���βע��)
        4. �������ʵ��ȫ����������
        5. ���ڵĺ���дע��

v1.0.1 2021��10��22��22:25:49
    TODO in v1.0.2:    
        1. input,sortʵ��
        2. ����ʵ�ּ̳�list.h
*/

#pragma once
#include <iostream>

//���
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
    List() { first = new LinkNode<T>; }               //�޲ι���
    List(const T& x) { first = new LinkNode<T>(x); }  //���ι���
    List(List<T>& L);                                 //��������
    ~List() { makeEmpty(); }                          //����
    void makeEmpty();                                 //���ÿ�
    int Length() const;                               //���س���
    LinkNode<T>* getHead() const { return first; }    //����ͷ����ַ
    LinkNode<T>* Search(T x);                         //���������Ƿ���valueΪx�Ľ��
    LinkNode<T>* Locate(int i);                       //���ص�i��Ԫ�صĽ���ַ
    T* getData(int i);                                //���ص�i��Ԫ�ص�vaule�ĵ�ַ
    void setData(int i, T& x);                        //�޸ĵ�i��Ԫ�ص�valueΪx
    bool Insert(int i, T& x);                         //�ڵ�i��Ԫ��֮�����
    bool Remove(int i, T& x);                         //�Ƴ���i�����
    bool IsEmpty() const;                             //�п�
    bool IsFull() const;                              //����
    void Sort();                                      //����(δʵ��)
    void input();                                     //����(δʵ��)
    void output();                                    //���
    List<T>& operator=(List<T>& L);                   //���ظ�ֵ�����
    void inputFront(T endTag);                        //ǰ�巨����
    void inputRear(T endTag);                         //��巨����
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

//��������Ϊ�ձ�
template <class T>
void List<T>::makeEmpty() {
    LinkNode<T>* q;
    while (first->link != NULL) {
        q = first->link;
        first->link = q->link;  //���汻ɾ��㣬������ժ�¸ý��
        delete q;
    }
}

//���������ͷ���ĵ�����ĳ���
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

//�ڱ�������������x�Ľ�㣬�����ɹ�ʱ�������ظý���ַ�����򷵻�NULL
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

//��λ�����ص�i��λ�õĽ���ַ
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

//ȡ�������е�i��Ԫ�ص�ֵ
template <class T>
T* List<T>::getData(int i) {
    if (i <= 0)  //iֵ̫С
        return NULL;
    LinkNode<T>* current = Locate(i);  //��λ��i
    if (current == NULL)               //iֵ̫��
        return NULL;
    return &current->data;
}

//�޸ĵ�i��Ԫ�ص�valueΪx
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

//����Ԫ��x�����������е�i�����֮��
template <class T>
bool List<T>::Insert(int i, T& x) {
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

//�������еĵ�i��Ԫ��ɾȥ��ͨ�������Ͳ���x���ظ�Ԫ�ص�ֵ
template <class T>
bool List<T>::Remove(int i, T& x) {
    LinkNode<T>* current = Locate(i - 1);
    if (current == NULL || current->link == NULL)  //ɾ�����ɹ�
        return false;
    LinkNode<T>* del = current->link;  //del����Ϊcurrent�ĺ��
    current->link = del->link;         //currentָ��ɾ��λ�õ���һ��
    x = del->data;                     //ȡ��ɾ��λ�õ�ֵ
    delete del;
    return true;  //ɾ���ɹ�
}

//�п�
template <class T>
bool List<T>::IsEmpty() const {
    if (first->data == NULL)
        return true;
    else
        return false;
}

//����
template <class T>
bool List<T>::IsFull() const {
    return false;
}

//��������������������������������ݰ��߼�˳���������Ļ��
template <class T>
void List<T>::output() {
    LinkNode<T>* current = first->link;
    while (current != NULL) {
        std::cout << current->data << std::endl;
        current = current->link;
    }
}

//���غ�������ֵ��������ʽ��A=B
//����A�ǵ��ô˲�����List����B����������������Ͳ���L��ϵ�ʵ��
template <class T>
List<T>& List<T>::operator=(List<T>& L) {
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

//ǰ�巨����������
//endTag��Լ�����������н����ı�־�����������������������endTag������0���߸���
template <class T>
void List<T>::inputFront(T endTag) {
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

//��巨����������
template <class T>
void List<T>::inputRear(T endTag) {
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
