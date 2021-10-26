/*
@file:        menu.h
@description: �˵�����
@version:     v1.0.0
@author:      Laobai
@time:        2021��10��26��16:35:17
*/

/*
update notes:

v1.0.0 2021��10��26��16:35:17
    TODO in v1.0.1:
        1. ����������ʾ
        2. fetch_choice�����ݸ�Ϊö��
*/
#include <iomanip>
#include <iostream>
using namespace std;

//����˵�
void print_menu();
//��ȡ����
void fetch_choice(int* arr);
//��ѭ��
void mainloop();
//��ȡ����
void get_input(int&, int, int, const char*);

#include "sort.h"
using namespace sort_laobai;
using namespace test_sort;
void print_menu() {
    cout << "**" << setw(15) << " "
         << "�����㷨�Ƚ�" << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "1---ð������" << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "2---ѡ������" << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "3---��������" << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "4---ϣ������" << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "5---��������" << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "6---������  " << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "7---�鲢����" << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "8---��������" << setw(15) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "9---std::sort" << setw(14) << " "
         << "**" << endl;
    cout << "**" << setw(15) << ""
         << "0---�˳�����" << setw(15) << " "
         << "**" << endl;
}

void input(int*& arr) {
    int num, range;
    get_input(num, 0, INT32_MAX, "Input num of random numbers : ");
    get_input(range, 1, INT32_MAX, "Input range of random numbers : ");
    arr = new int[num];
    generate(arr, num, range);
}

void get_input(int& ret, int min, int max, const char* prompt = "") {
    while (1) {
        cout << prompt;
        cin >> ret;
        if (cin.fail() || ret < min || ret > max) {
            cin.clear();
            cin.ignore(65536, '\n');
            cout << "Error input" << endl;
        } else
            break;
    }
}

void fetch_choice(int* arr) {
    int ret;
    string NAME[10] = {"Exit", "Bubble_sort", "Selection_sort", "Insertion_sort", "Quick_sort", "Shell_sort", "Heap_sort", "Merge_sort", "Radix_sort", "std::sort"};
    get_input(ret, 0, 9, "Choose type of sort : ");  //0~8������
    cout << NAME[ret] << endl;
    switch (ret) {
        case 0:  //�˳�
            delete[] arr;
            exit(0);
        case 1:  //ð������
            Bubble_sort(arr);
            break;
        case 2:  //ѡ������
            Selection_sort(arr);
            break;
        case 3:  //��������
            Insertion_sort(arr);
            break;
        case 4:  //ϣ������
            Shell_sort(arr);
            break;
        case 5:  //��������
            Quick_sort(arr);
            break;
        case 6:  //������
            Heap_sort(arr);
            break;
        case 7:  //��·�鲢����
            Merge_sort(arr);
            break;
        case 8:  //��������
            Radix_sort(arr);
            break;
        case 9:  //std::sort()
            std_result(arr);
            break;
    }
}

void mainloop() {
    int* arr = nullptr; //��Ҫ��ʼ��
    int i = 1;
    while (1) {
        if (i) {
            print_menu();
            input(arr);
            i = 0;
        }
        fetch_choice(arr);
    }
}

//2021��10��19��17:40:47