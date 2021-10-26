/*
@file:        joseph.h
@description: ���Լɪ������
@version:     v1.0.2
@author:      Laobai
@time:       2021��10��25��12:23:47
*/

/*
update notes:

v1.0.0 2021��10��22��11:07:25
    TODO in v1.0.1:
        1. gap����ʱ����ȡ��
        2. ������ʽ�Ż������ٶ�
        3. ע�͵�λ�÷���ĳһ�е���һ��(***�ĵ���βע��)

v1.0.1 2021��10��23��11:52:45
    TODO in v1.0.2:
        1. ��ʼ��ʱ��Ϊͷ�����룬����ÿ�μ���������Ч�ʺܵ�

v1.0.2 2021��10��25��12:23:47
*/

#include <iomanip>
#include "list_circular.h"
#include "tool.h"
class Joseph {
   private:
    int num;             //�ÿ͸���
    int start;           //��ʼλ��
    int gap;             //���
    int rest;            //ʣ������
    CircList<int> List;  //�ÿ�����
    CircList<int> Del;   //ɾ�����ÿ�
   public:
    Joseph(int NUM, int START, int GAP, int REST) {
        num = NUM;
        start = START;
        gap = GAP;
        rest = REST;
        for (int i = num; i > 0; --i) {
            List.Insert(0, i);  //��ʼ��
        }
    }
    ~Joseph(){};   //��������
    void solve();  //���Joseph���⣬���������List��Del��
};

//���Joseph���⣬���������List��Del��
void Joseph::solve() {
    cout << "��ʼ����Ϊ��" << num << endl;
    cout << "�������Ϊ��" << gap << endl;
    cout << "��ʼλ��Ϊ��" << start << endl;
    cout << "ʣ�����Ϊ��" << rest << endl;
    cout << "------ Please wait -------" << endl;
    CircLinkNode<int>* current = List.getHead();  //��ǰλ��
    int i = start;                                //���ڶ�λcurrentָ��
    int count = num - rest;                       //����Ҫɾ��������
    int del;                                      //ɾ�������
    int pos = start - 1;                          //��¼ɾ����λ��
    while (i--)                                   //��λ����ʼλ��
        current = current->Link;
    while (count) {
        for (int i = 0; i < gap; i++) {
            if (current == List.getHead()) {
                current = current->Link;
                pos = 0;
            }
            current = current->Link;
            pos++;
        }
        del = current->data;
        List.Remove(pos, del);
        Del.Insert(Del.Length(), del);
        pos--;
        count--;
    }
    cout << "--------  �����  --------" << endl;
    cout << "�������Ϊ�� " << endl;
    Del.output();
    cout << endl;
    cout << "ʣ�����Ϊ" << endl;
    List.output();

    delete current;
}

//����ۺϵ�����
void Solution() {
    int num;    //�ÿ͸���
    int start;  //��ʼλ��
    int gap;    //���
    int rest;   //ʣ������
    get_input(num, 1, INT32_MAX, "�����뿪ʼ������(1 ~ INT32_MAX): ");
    get_input(start, 1, num, "�����뿪ʼλ��(1 ~ ������):      ");
    get_input(gap, 1, num, "��������(1 ~ ������-1):        ");
    get_input(rest, 0, num, "������ʣ������(0 ~ ������):      ");
    cout << "---------- �� ʼ �� ----------" << endl;
    Joseph J(num, start, gap, rest);
    cout << "---------- �� �� �� ----------" << endl;
    J.solve();
}
