//Լɪ������
/*����ϷҪ���û���������ݰ�����

1. �ÿ͵ĸ�����Ҳ����N��ֵ��

2. �뿪�ÿ͵ļ���飬Ҳ����M��ֵ��

3. �����ÿ͵������Ϊһ������Ҫ������ĳ�����ݽṹ�С�

   ����ϷҪ������������ǰ�����

4. �뿪�ÿ͵���ţ�

5. ʣ���ÿ͵���š�*/
#include "CircularList.h"
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
            int ins = i + 1;
            List.Insert(List.Length(), ins);  //��ʼ��
        }
    }
    ~Joseph(){};
    void solve();   //���Joseph���⣬���������List��Del��
    void output();  //������
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

    delete[] current;
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
