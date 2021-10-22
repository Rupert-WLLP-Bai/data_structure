/*
@file:        joseph.h
@description: ���Լɪ������
@version:     v1.0.0
@author:      Laobai
@time:        2021��10��22��11:07:25
*/

/*
update notes:

v1.0.0 2021��10��22��11:07:25
    TODO in v1.0.1:
        1. gap����ʱ����ȡ��
        2. ������ʽ�Ż������ٶ�
        3. ע�͵�λ�÷���ĳһ�е���һ��(***�ĵ���βע��)
*/
#include "list_circular.h"
#include "tool.h"
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
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < 10; j++) {
                    if (i == num * j / 10)
                        cout << "----------    " << j * 10 << "%    ----------" << endl;
            }
            int ins = i + 1;
            List.Insert(List.Length(), ins);  //��ʼ��
        }
    }
    ~Joseph(){};
    void solve();   //���Joseph���⣬���������List��Del��
};

void Joseph::solve() {
    cout << "��ʼ����Ϊ��" << num << endl;
    cout << "�������Ϊ��" << gap << endl;
    cout << "��ʼλ��Ϊ��" << start << endl;
    cout << "ʣ�����Ϊ��" << rest << endl;
    cout << "---------- Start Solving ----------" << endl;

    CircLinkNode<int>* current = new CircLinkNode<int>;
    current = List.getHead();
    int i = start;
    int count = num - rest;
    int del;              //ɾ�������
    int pos = start - 1;  //��¼ɾ����λ��
    while (i--)           //��λ����ʼλ��
        current = current->Link;
    while (count--) {
        for(int i = 0;i<10;i++){
            if (count == (num - rest) * i / 10)
                cout << "---------- " << (10 - i) * 10 << "% ----------" << endl;
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
        // cout << "��" << num - rest - count + 1 << "��ɾ����λ��: " << pos << ",ɾ����Ԫ��Ϊ: " << del << endl;
        // List.output();
        Del.Insert(Del.Length(), del);
        pos--;  //ɾ�����λ����ԭ�����λ�÷����ı�
    }
    cout << "�������Ϊ�� " << endl;
    Del.output();
    cout << "ʣ�����Ϊ" << endl;
    List.output();

    delete current;
}

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
