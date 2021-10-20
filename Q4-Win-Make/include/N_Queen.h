#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stack>
using namespace std;

class N_Queen {
   private:
    int max;  //���������
    int* array;
    bool judge(int n);

   public:
    N_Queen(int max);
    ~N_Queen();
    void solve_Recursive();    //�ݹ�ⷨ
    void solve_noRecursive();  //�ǵݹ�ⷨ
};

N_Queen::N_Queen(int max) {
    this->array = new int[max];
    this->max = max;
}

N_Queen::~N_Queen() {
    delete[] array;
}

bool N_Queen::judge(int n) {
    for (int i = 0; i < n; i++) {
        if (array[i] == array[n] || abs(n - i) == abs(array[i] - array[n])) {
            return false;
        }
    }
    return true;
}

//�ǵݹ�ⷨ
inline void N_Queen::solve_noRecursive() {
    //�˻ʺ����⣺���ݷ����ǵݹ飩
    int n = max;    //max���ʺ�
    int count = 0;  //��¼��ǰ�ڼ����
    int i, k = 0;   //��ʼ��kΪ��һ��
    for (int j = 0; j < max; j++) {
        array[j] = -1;
    }
    while (k > -1) {                           //k==-1ʱ����ʾ�ڷŵ�1���ʺ�ͳ������еײ������Ѿ��������������
        array[k] += 1;                         //a[k]λ�ã��ڷ�һ���ʺ�
        while ((array[k] < n) && (!judge(k)))  //���a[k]�����ʺ�ڷ�λ�ã�û�е�����ײ����Ұڷų�ͻ��
            array[k] += 1;                     //���ʺ�������һλ
        if (array[k] < n) {                    //�ʺ�ڷ�λ��û�е�������ײ�
            if (k == (n - 1)) {                //k==n-1��ʾ��max�лʺ�ȫ���ڷ����
                printf("��%10d�������",++count);
                for (i = 0; i < n; ++i)  //��ӡ���
                    //cout << setw(2) << array[i] + 1 << " ";
                    printf("%2d ",array[i]+1);
                printf("\n");
            } else {            //�ʺ�δ�ڷ����
                k += 1;         //�����ڷ���һ��
                array[k] = -1;  //���г�ʼ��a[k] = -1;��ʾ��k�У��ӵ�һ�п�ʼ�ڷŻʺ�
            }
        } else       //���ݣ���a[k]>max����else,��ʾ�ڵ�k����û���ҵ����ʵİڷ�λ��
            k -= 1;  //���ݵ�k-1����k��ʾ�ڼ����ʺ�a[k]��ʾ��k���ʺ�ڷŵ�λ��
    }
}

//�ݹ�ⷨ
inline void N_Queen::solve_Recursive() {

}