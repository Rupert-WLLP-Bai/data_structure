/*
@file:        N_Queen.h
@description: N�ʺ�
@version:     v1.0.1
@author:      Laobai
@time:        2021��10��25��22:27:39
*/

/*
update notes:

v1.0.0 2021��9��29��17:55:52
    TODO in v1.0.1:
        1. ����ݹ�ⷨ

v1.0.1 2021��10��25��22:27:39
    TODO in v1.0.2:
        1. ������߳̽ⷨ(��Java����ʵ��)
*/

#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

class N_Queen {
   private:
    int max;                      //���������
    int* array;                   //��Żʺ��������������
    bool judge(int n);            //�жϷ���λ���Ƿ����
    void solve_Recursive(int n);  //�ݹ�ⷨ(Private)
   public:
    N_Queen(int max);
    ~N_Queen();
    void solve_Recursive();       //�ݹ�ⷨ
    void solve_noRecursive();     //�ǵݹ�ⷨ
    void solve_Multithreading();  //���߳̽ⷨ
};

N_Queen::N_Queen(int max) {
    this->array = new int[max];
    this->max = max;
    for (int j = 0; j < max; j++) {
        this->array[j] = -1;
    }
}

N_Queen::~N_Queen() {
    delete[] array;
}

//�жϷ���λ���Ƿ����
bool N_Queen::judge(int n) {
    for (int i = 0; i < n; i++) {
        if (array[i] == array[n] || abs(n - i) == abs(array[i] - array[n])) {
            return false;
        }
    }
    return true;
}

//�ݹ�ⷨ(Private)
inline void N_Queen::solve_Recursive(int N) {
    static int count = 0;  //��¼��ǰ�ǵڼ������
    for (int i = 0; i < max; i++) {
        array[N] += i + 1;
        if (judge(N)) {
            /*�������һ�㣬������*/
            if (N == max - 1) {
                printf("��%10d�������", ++count);
                /*��ӡ���*/
                for (int i = 0; i < max; ++i)
                    printf("%2d ", array[i] + 1);
                printf("\n");
            }
            /*δ�������һ�㣬��������*/
            else {
                solve_Recursive(N + 1);
            }
        }
        array[N] = -1;
    }
}
//�ݹ�ⷨ(Public)
inline void N_Queen::solve_Recursive() {
    solve_Recursive(0);
}
//�ǵݹ�ⷨ
inline void N_Queen::solve_noRecursive() {
    int n = max;    //max���ʺ�
    int count = 0;  //��¼��ǰ�ڼ����
    int k = 0;      //��ʼ��kΪ��һ��

    while (k > -1) {                           //k==-1ʱ����ʾ�ڷŵ�1���ʺ�ͳ������еײ������Ѿ��������������
        array[k] += 1;                         //a[k]λ�ã��ڷ�һ���ʺ�
        while ((array[k] < n) && (!judge(k)))  //���a[k]�����ʺ�ڷ�λ�ã�û�е�����ײ����Ұڷų�ͻ��
            array[k] += 1;                     //���ʺ�������һλ
        if (array[k] < n) {                    //�ʺ�ڷ�λ��û�е�������ײ�
            if (k == (n - 1)) {                //k==n-1��ʾ��max�лʺ�ȫ���ڷ����
                printf("��%10d�������", ++count);
                for (int i = 0; i < n; ++i)  //��ӡ���
                    printf("%2d ", array[i] + 1);
                printf("\n");
            } else {            //�ʺ�δ�ڷ����
                k += 1;         //�����ڷ���һ��
                array[k] = -1;  //���г�ʼ��a[k] = -1;��ʾ��k�У��ӵ�һ�п�ʼ�ڷŻʺ�
            }
        } else       //���ݣ���a[k]>max����else,��ʾ�ڵ�k����û���ҵ����ʵİڷ�λ��
            k -= 1;  //���ݵ�k-1����k��ʾ�ڼ����ʺ�a[k]��ʾ��k���ʺ�ڷŵ�λ��
    }
}

//���߳̽ⷨ
inline void N_Queen::solve_Multithreading() {
}