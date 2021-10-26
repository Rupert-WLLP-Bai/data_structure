/*
@file:        list_circular.h
@description: ����ѭ������
@version:     v1.0.1
@author:      Laobai
@time:        2021��10��23��11:53:47
*/

/*
update notes:

v1.0.0 2021��10��22��11:07:25
    TODO in v1.0.1:
        1. ע�͵�λ�÷���ĳһ�е���һ��(***�ĵ���βע��)

v1.0.1 2021��10��23��11:53:47
    TODO in v1.0.2
        1. �̳�list.h ���������һ��ͷ�ļ���
*/

#pragma once
#include <iomanip>
#include <iostream>
using namespace std;

//�����㶨��
template <class T>
struct CircLinkNode
{
    T data;
    CircLinkNode<T>* Link;
    CircLinkNode(CircLinkNode<T>* Link = NULL)
        : data(0), Link(Link){};
    CircLinkNode(T d, CircLinkNode<T>* Link = NULL)
        : data(d), Link(Link) {}
};

//ѭ������
template <class T>
class CircList {
   public:
    CircList();                                            //�޲ι��캯��
    CircList(const T& x);                                  //���캯��
    CircList(CircList<T>& L);                              //���ƹ��캯��
    ~CircList(){};                                         //��������
    int Length() const { return length; }                  //����ѭ��������
    bool IsEmpty() { return length == 0 ? true : false; }  //�п�
    CircLinkNode<T>* getHead() const { return head; }      //���ظ���ͷ����ַ
    CircLinkNode<T>* Search(T x);                          //����������x��Ԫ��
    CircLinkNode<T>* Locate(int i);                        //������i��Ԫ�صĵ�ַ
    T* getData(int i);                                     //ȡ����i��Ԫ�ص�ֵ
    void setData(int i, T& x);                             //��x�޸ĵ�i��Ԫ�ص�ֵ
    bool Insert(int i, T& x);                              //�ڵ�i��Ԫ�غ����x
    bool Remove(int i, T& x);                              //ɾ����i��Ԫ�أ�x���ظ�Ԫ�ص�ֵ
    void output();                                         //���

   private:
    CircLinkNode<T>* head;  //ͷָ��
    int length;             //������
};

//�޲ι���
template <class T>
CircList<T>::CircList() {
    length = 0;
    head = new CircLinkNode<T>;
    head->Link = head;
}

//���ι���
template <class T>
CircList<T>::CircList(const T& x) {
    length = 0;
    head = new CircLinkNode<T>;
    CircLinkNode<T>* newNode = new CircLinkNode<T>(x);
    head->Link = newNode;
    newNode->Link = head;
    length++;
}

//��������
template <class T>
CircList<T>::CircList(CircList<T>& L) {
    length = 0;
    T value;
    CircLinkNode<T>* srcptr = L.getHead();  //�����������ͷ���λ��
    head = new CircLinkNode<T>;
    CircLinkNode<T>* destptr = head;
    while (srcptr->Link != L.getHead()) {
        //����ڵ㸴��
        value = srcptr->Link->data;
        destptr->Link = new CircLinkNode<T>(value);
        destptr = destptr->Link;
        srcptr = srcptr->Link;
        length++;
    }
    destptr->Link = head;
}

//����Ԫ��x�ĵ�ַ
template <class T>
CircLinkNode<T>* CircList<T>::Search(T x) {
    CircLinkNode<T>* current = head->Link;
    while (current != head) {
        if (current->data == x)
            return current;
        else
            current = current->Link;
    }
    return NULL;  //δ�ҵ�
}

//��λ
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

//��λ����i��Ԫ�ص�λ��,����data�ĵ�ַ
template <class T>
T* CircList<T>::getData(int i) {
    if (i <= 0 || i > length)
        return NULL;
    CircLinkNode<T>* current = Locate(i);
    return &current->data;
}

//����valaue
template <class T>
void CircList<T>::setData(int i, T& x) {
    if (i <= 0 || i > length)
        return;
    else {
        CircLinkNode<T>* current = Locate(i);
        current->data = x;
    }
}

//����
template <class T>
bool CircList<T>::Insert(int i, T& x) {
    CircLinkNode<T>* current = Locate(i);
    if (current == NULL)
        return false;  //���벻�ɹ�
    CircLinkNode<T>* newNode = new CircLinkNode<T>(x);
    if (newNode == NULL) {
        cerr << "�洢�������" << endl;
        exit(1);
    }
    newNode->Link = current->Link;  //���ӵ�current֮��
    current->Link = newNode;
    length++;     //����+1
    return true;  //����ɹ�
}

//�������еĵ�i��Ԫ��ɾȥ��ͨ�������Ͳ���x���ظ�Ԫ�ص�ֵ
template <class T>
bool CircList<T>::Remove(int i, T& x) {
    if (IsEmpty() == true)
        return false;  //�ձ�,ɾ��ʧ��
    CircLinkNode<T>* current = Locate(i - 1);
    if (current == NULL)
        return false;  //λ�ò���
    CircLinkNode<T>* del = current->Link;
    current->Link = del->Link;
    x = del->data;
    delete del;
    length--;
    return true;  //ɾ���ɹ�
}

//���
template <class T>
void CircList<T>::output() {
    if (length == 0)
        cout << "(HEAD)NULL �� �ձ�" << endl;
    else {
        int num = 1;
        CircLinkNode<T>* current = head;
        while (current->Link != head) {
            current = current->Link;
            cout << current->data;
            cout << "(ID:" << num++ << ")";  //���Id
            cout << " --> ";
        }
        cout << head->Link->data << "(HEAD)"
             << "  ������Ϊ��" << length << endl;
    }
}