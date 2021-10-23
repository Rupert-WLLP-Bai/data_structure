/*
@file:        joseph.h
@description: ���Լɪ������
@version:     v1.0.1
@author:      Laobai
@time:        2021��10��23��11:52:45
*/

/*
update notes:

v1.0.0 2021��10��22��11:07:25
    TODO in v1.0.1:
        1. gap����ʱ����ȡ��
        2. ������ʽ�Ż������ٶ�
        3. ע�͵�λ�÷���ĳһ�е���һ��(***�ĵ���βע��)

v1.0.1 2021��10��23��11:52:45
*/

#include "list_circular.h"
#include "tool.h"
#include<iomanip>
class Joseph {
   private:
    int num;             //�ÿ͸���
    int start;           //��ʼλ��
    int gap;             //���
    int rest;            //ʣ������
    CircList<int> List;  //�ÿ�����
    CircList<int> Del;   //ɾ�����ÿ�����
   public:
    Joseph(int NUM, int START, int GAP, int REST) {
        num = NUM;
        start = START;
        gap = GAP;
        rest = REST;
        int process = 0;//����
        for (int i = 0; i < num; i++) {
            if (i == num * process / 10) {
                cout << "----------  " << setw(3) << process * 10 << "%    ----------" << endl;
                process++;
            }
            int ins = i + 1;
            List.Insert(List.Length(), ins);  //��ʼ��
        }
    }
    ~Joseph(){};
    void solve();   //���Joseph���⣬���������List��Del��
};

//���Joseph���⣬���������List��Del��
void Joseph::solve() {
    cout << "��ʼ����Ϊ��" << num << endl;
    cout << "�������Ϊ��" << gap << endl;
    cout << "��ʼλ��Ϊ��" << start << endl;
    cout << "ʣ�����Ϊ��" << rest << endl;
    cout << "------ Please wait -------" << endl;
    int process = 10;//����
    CircLinkNode<int>* current = new CircLinkNode<int>;//��ǰλ��
    current = List.getHead();
    int i = start;//���ڶ�λcurrentָ��
    int count = num - rest;//����Ҫɾ��������
    int del;              //ɾ�������
    int pos = start - 1;  //��¼ɾ����λ��
    while (i--)           //��λ����ʼλ��
        current = current->Link;
    while (count) {
        if (count == (num - rest) * process / 10) {
            cout << "---------- " << setw(3) << (10 - process) * 10 << "% ----------" << endl;
            process--;
        }
        
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
    cout<<"---------- �� ʼ �� ----------"<<endl;
    Joseph J(num, start, gap, rest);
    cout<<"---------- �� �� �� ----------"<<endl;
    J.solve();
}
