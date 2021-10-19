//menu.h �˵�����
#include <iomanip>
#include <iostream>
using namespace std;

//����˵�
void print_menu();
//��ȡ����
void fetch_choice(int* arr);
//��ѭ��
void mainloop();
//��ȡ����(promptΪ��ʾ��,�ṩcompare�����Լ�һ�����·�Χ)
//template <typename T>
//void get_input(const char* prompt,T min,T max,bool *compare());

void get_input(int&, int, int, const char*);

#include "sort_repair.h"
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

void input(int* arr) {
    int num, range;
    get_input(num, 0, INT32_MAX, "Input num of random numbers : ");
    get_input(range, 1, INT32_MAX, "Input range of random numbers : ");
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
    const char* NAME[10] = {"Exit", "Bubble_sort", "Selection_sort", "Insertion_sort", "Quick_sort", "Shell_sort", "Heap_sort", "Merge_sort", "Radix_sort","std::sort"};
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
    //���ṩһ�����������ѡ�� ͬʱ���´�ӡ�˵� ��ֱ�Ӵӳ���ͷ����ִ��
    //����˵�
    //��ȡ���� �Լ���Χ
    //������� ͣ�� clear �����ʼ
    //��ȡ�û�����
    //����������»�ȡ�û����� ����������
    const int N = 100000000;
    int* arr = new int[N];
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