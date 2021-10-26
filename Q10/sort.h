/*
@file:        sort.h
@description: ������
@version:     v1.0.0
@author:      Laobai
@time:        2021��10��26��16:35:17
*/

/*
update notes:

v1.0.0 2021��10��26��16:35:17
    TODO in v1.0.1
        1. rand�ķ�Χ��Windows��Linux�²�ͬ
*/
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include "stop_watch.h" //��ʱ��
#include <iomanip>
#include <iostream>
#include <vector>   //������std::sort���бȽ�

//������
namespace sort_laobai {
void swap(int& a, int& b);                                             //����
void assign(int* num, int* _arr, int N);                               //��ֵ
void std_result(int *_arr);                                            //std::sort�Ľ��
void Bubble_sort(int* _arr);                                           //ð������
void Selection_sort(int* _arr);                                        //ѡ������
void Insertion_sort(int* _arr);                                        //��������
void Shell_sort(int* _arr);                                            //ϣ������
void Quick_sort(int* _arr);                                            //��������(�������Ż�)
void Heap_sort(int* _arr);                                             //������
void Merge_sort(int* _arr);                                            //�鲢����(��·�鲢) (�ɼ���n·�鲢)
void Radix_sort(int* _arr);                                            //��������
int64_t Shell_insert(int* arr, int begin, int gap, int N);             //ϣ���������
int64_t Q_Sort(int left, int right, int* arr);                         //��������ݹ�
int64_t adjustHeap(int* arr, int i, int n);                            //�����Ѻ���
void MergeSort(int* A, int n, int64_t& count);                         //�鲢����
int64_t Merge(int* A, int* L, int leftCount, int* R, int rightCount);  //�鲢
int max_bit(int* arr, int N);                                          //�������������λ��
void radixsort(int* data, int n);                                      //��������ʵ��
}  // namespace sort_laobai

//���Ժ���
namespace test_sort {
void print_arr(int* arr);                   //���һ��*arr,��Χ������ʽ�����
void generate(int* arr, int n, int range);  //���������*arr,����Ϊn,��ΧΪ0~range-1

}  // namespace test_sort

using namespace std;
using namespace test_sort;

//���arr
void test_sort::print_arr(int* arr) {
    using namespace sort_laobai;
    //���*arr��N��ֵ
    int* p = arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    int bit = max_bit(arr, N);
    cout << "Result:";
    for (int i = 0; i < N; i++) {
        cout << setiosflags(ios::left) << setw(bit) << arr[i] << " ";
        if (i % 10 == 9)
            cout << endl
                 << "       ";
    }
    cout << endl;
}
//�������(Windows�µ�RAND_MAX��Linux�²�ͬ)
void test_sort::generate(int* arr, int n, int range) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % range;
    }
    arr[n] = -1;
    if (n < 100)
        print_arr(arr);
}

//namespace sort_laobai��ʵ�� ֻ����������sʵ��
//����
void sort_laobai::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
//��ֵ
void sort_laobai::assign(int* num, int* arr, int N) {
    for (int i = 0; i < N; i++) {
        arr[i] = num[i];
    }
}

//std::sort�Ľ��
void sort_laobai::std_result(int* _arr) {
    //����
    vector<int> L;
    int* p = _arr;
    while (*p != -1) {
        L.push_back(*p);
        p++;
    }
    //��ʱ��ʼ
    stop_watch T;
    T.start();
    //����
    sort(L.begin(), L.end());
    //��ʱ����
    T.stop();
    cout << "------------------std::sort����Ľ��-----------------" << endl;
    cout << "Time  :" << T.elapsed() << "  ��s" << endl;
    cout << "Count :" << "UNKNOWN" << endl;
    //if (N < 100)
        //print_arr(arr);
    cout << "--------------------------------------------------" << endl;
}

//��������(10��)

//1.ð������
void sort_laobai::Bubble_sort(int* _arr) {
    //���*arr��N��ֵ
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //����
    int64_t count = 0;
    //����
    int* arr = new int[N];
    //��ֵ
    sort_laobai::assign(_arr, arr, N);
    //��ʱ��ʼ
    stop_watch T;
    T.start();
    //����
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                sort_laobai::swap(arr[j], arr[j + 1]);
                count++;
            }
        }
    }
    //��ʱ����
    T.stop();
    cout << "--------------------ð������Ľ��-------------------" << endl;
    cout << "Time  :" << T.elapsed() << "  ��s" << endl;
    cout << "Count :" << count << endl;
    //if (N < 100)
        //print_arr(arr);
    cout << "--------------------------------------------------" << endl;
    //�ͷ�
    delete[] arr;
}

//2.ѡ������
void sort_laobai::Selection_sort(int* _arr) {
    //���*arr��N��ֵ
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //����
    int64_t count = 0;
    //����
    int* arr = new int[N];
    //��ֵ
    sort_laobai::assign(_arr, arr, N);
    //��ʱ��ʼ
    stop_watch T;
    T.start();
    //����
    for (int i = 0; i < N; i++) {
        int m = arr[i];
        int index = i;
        for (int j = i + 1; j < N; j++) {
            if (arr[j] < m) {
                count++;
                m = arr[j];
                index = j;
            }
        }
        if (i != index) {
            swap(arr[i], arr[index]);
            count++;
        }
    }
    //��ʱ����
    T.stop();
    cout << "--------------------ѡ������Ľ��-------------------" << endl;
    cout << "Time  :" << T.elapsed() << "  ��s" << endl;
    cout << "Count :" << count << endl;
   // if (N < 100)
        //print_arr(arr);
    cout << "--------------------------------------------------" << endl;
    //�ͷ�
    delete[] arr;
}
//3.ֱ�Ӳ�������
void sort_laobai::Insertion_sort(int* _arr) {
    //���*arr��N��ֵ
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //����
    int64_t count = 0;
    //����
    int* arr = new int[N];
    //��ֵ
    sort_laobai::assign(_arr, arr, N);
    //��ʱ��ʼ
    stop_watch T;
    T.start();
    //����
    for (int i = 1; i < N; i++) {
        int temp = i;
        for (int j = i - 1; j >= 0; j--) {
            if (arr[temp] < arr[j]) {
                swap(arr[temp--], arr[j]);
                count++;
            }
        }
    }
    //��ʱ����
    T.stop();
    cout << "--------------------��������Ľ��-------------------" << endl;
    cout << "Time  :" << T.elapsed() << "  ��s" << endl;
    cout << "Count :" << count << endl;
  //  if (N < 100)
     //   print_arr(arr);
    cout << "--------------------------------------------------" << endl;
    //�ͷ�
    delete[] arr;
}

//4.ϣ������
void sort_laobai::Shell_sort(int* _arr) {
    //���*arr��N��ֵ
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //����
    int64_t count = 0;
    //����
    int* arr = new int[N];
    //��ֵ
    sort_laobai::assign(_arr, arr, N);
    //��ʱ��ʼ    
    stop_watch T;
    T.start();
    //����
    int gap = N / 2;
    while (gap > 0) {
        int begin = gap - 1;
        while (begin >= 0) {
            count += Shell_insert(arr, begin, gap, N);
            begin--;
        }
        gap = gap / 2;
    }
    //��ʱ����
    T.stop();
    cout << "--------------------ϣ������Ľ��-------------------" << endl;
    cout << "Time  :" <<T.elapsed() << "  ��s" << endl;
    cout << "Count :" << count << endl;
   // if (N < 100)
   //     print_arr(arr);
    cout << "--------------------------------------------------" << endl;
    //�ͷ�
    delete[] arr;
}
//4.ϣ������Ĳ���(����ֵΪcount������)
int64_t sort_laobai::Shell_insert(int* arr, int begin, int gap, int N) {
    int64_t count = 0;
    for (int i = begin + gap; i < N; i += gap) {
        int temp = arr[i];
        int j = i - gap;
        for (; j >= 0 && temp < arr[j]; j -= gap) {
            arr[j + gap] = arr[j];
            count++;
        }
        arr[j + gap] = temp;
    }
    return count;
}

//5.��������
void sort_laobai::Quick_sort(int* _arr) {
    //���*arr��N��ֵ
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //����
    int64_t count = 0;
    //����
    int* arr = new int[N];
    //��ֵ
    sort_laobai::assign(_arr, arr, N);
    //��ʱ��ʼ
    stop_watch T;
    T.start();
    //����
    count = Q_Sort(0, N - 1, arr);
    //��ʱ����
    T.stop();
    cout << "--------------------��������Ľ��-------------------" << endl;
    cout << "Time  :" << T.elapsed() << " ��s" << endl;
    cout << "Count :" << count << endl;
  //  if (N < 100)
   //     print_arr(arr);
    cout << "--------------------------------------------------" << endl;
    //�ͷ�
    delete[] arr;
}
//5.��������ݹ�
int64_t sort_laobai::Q_Sort(int left, int right, int* arr) {
    static int64_t count = 0;
    if (left >= right)
        return 0;
    int i, j, base;
    i = left, j = right;
    base = arr[left];  //ȡ����ߵ���Ϊ��׼��
    while (i < j) {
        while (arr[j] >= base && i < j)
            j--;
        while (arr[i] <= base && i < j)
            i++;
        if (i < j) {
            sort_laobai::swap(arr[i], arr[j]);
            count++;
        }
    }
    //��׼����λ
    arr[left] = arr[i];
    arr[i] = base;
    Q_Sort(left, i - 1, arr);   //�ݹ����
    Q_Sort(i + 1, right, arr);  //�ݹ��ұ�
    return count;
}

//6.������
void sort_laobai::Heap_sort(int* _arr) {
    //���*arr��N��ֵ
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //����
    int64_t count = 0;
    //����
    int* arr = new int[N];
    //��ֵ
    sort_laobai::assign(_arr, arr, N);
    //��ʱ��ʼ
    stop_watch T;
    T.start();
    //����
    //1.����󶥶�
    count += adjustHeap(arr, 0, N);
    //2.����ѭ��
    for (int i = N - 1; i > 0; i--) {
        sort_laobai::swap(arr[0], arr[i]);
        count++;
        count += adjustHeap(arr, 0, i);
    }
    //��ʱ����
    T.stop();
    cout << "----------------------������Ľ��-------------------" << endl;
    cout << "Time  :" << T.elapsed() << "  ��s" << endl;
    cout << "Count :" << count << endl;
  //  if (N < 100)
  //      print_arr(arr);
    cout << "--------------------------------------------------" << endl;
    //�ͷ�
    delete[] arr;
}
//6.������
int64_t sort_laobai::adjustHeap(int* arr, int i, int n) {
    int64_t count = 0;
    int parent = i;         // ���ڵ��±�
    int child = 2 * i + 1;  // �ӽڵ��±�
    while (child < n) {
        if (child + 1 < n && arr[child] < arr[child + 1]) {  // �ж��ӽڵ��Ǹ��󣬴���븸�ڵ�Ƚ�
            child++;
        }
        if (arr[parent] < arr[child]) {                  // �жϸ��ڵ��Ƿ�С���ӽڵ�
            sort_laobai::swap(arr[parent], arr[child]);  // �������ڵ���ӽڵ�
            count++;
            parent = child;  // �ӽڵ��±� ���� ���ڵ��±�
        }
        child = child * 2 + 1;  // ���У��Ƚ�����ĸ��ڵ���ӽڵ�
    }
    return count;
}

//7.��·�鲢����
void sort_laobai::Merge_sort(int* _arr) {
    //���*arr��N��ֵ
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //����
    int64_t count = 0;
    //����
    int* arr = new int[N];
    //��ֵ
    sort_laobai::assign(_arr, arr, N);
    //��ʱ��ʼ
    stop_watch T;
    T.start();
    //����
    MergeSort(arr, N, count);
    //��ʱ����
    T.stop();
    cout << "----------------------�鲢����Ľ��-------------------" << endl;
    cout << "Time  :" << T.elapsed() << "  ��s" << endl;
    cout << "Count :" << count << endl;
  //  if (N < 100)
  //      print_arr(arr);
    cout << "----------------------------------------------------" << endl;
    //�ͷ�
    delete[] arr;
}
//�ϲ�
int64_t sort_laobai::Merge(int* A, int* L, int leftCount, int* R, int rightCount) {
    int i, j, k;
    int64_t count = 0;
    // i - to mark the index of left aubarray (L)
    // j - to mark the index of right sub-raay (R)
    // k - to mark the index of merged subarray (A)
    i = 0;
    j = 0;
    k = 0;

    while (i < leftCount && j < rightCount) {
        if (L[i] < R[j])
            A[k++] = L[i++];
        else {
            A[k++] = R[j++];
            count++;
        }
        while (i < leftCount)
            A[k++] = L[i++];
        while (j < rightCount)
            A[k++] = R[j++];
    }
    return count;
}
// Recursive function to sort an array of integers.
void sort_laobai::MergeSort(int* A, int n, int64_t& count) {
    int mid, i, *L, *R;
    if (n < 2)
        return;  // base condition. If the array has less than two element, do nothing.

    mid = n / 2;  // find the mid index.

    // create left and right subarrays
    // mid elements (from index 0 till mid-1) should be part of left sub-array
    // and (n-mid) elements (from mid to n-1) will be part of right sub-array
    L = new int[mid];
    R = new int[n - mid];

    for (i = 0; i < mid; i++)
        L[i] = A[i];  // creating left subarray
    for (i = mid; i < n; i++)
        R[i - mid] = A[i];  // creating right subarray

    MergeSort(L, mid, count);               // sorting the left subarray
    MergeSort(R, n - mid, count);           // sorting the right subarray
    count += Merge(A, L, mid, R, n - mid);  // Merging L and R into A as sorted list.
    // the delete operations is very important
    delete[] R;
    delete[] L;
}

//8.��������
void sort_laobai::Radix_sort(int* _arr) {
    //���*arr��N��ֵ
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //����
    int64_t count = 0;
    //����
    int* arr = new int[N];
    //��ֵ
    sort_laobai::assign(_arr, arr, N);
    //��ʱ��ʼ
    stop_watch T;
    T.start();
    //����
    radixsort(arr, N);
    //��ʱ����
    T.stop();
    cout << "----------------------��������Ľ��-------------------" << endl;
    cout << "Time  :" << T.elapsed() << "  ��s" << endl;
    cout << "Count :" << count << endl;
  //  if (N < 100)
  //      print_arr(arr);
    cout << "--------------------------------------------------" << endl;
    //�ͷ�
    delete[] arr;
}
//��������
void sort_laobai::radixsort(int* data, int n) {
    int d = max_bit(data, n);
    int* tmp = new int[n];
    int* count = new int[10];  //������
    int i, j, k;
    int radix = 1;
    for (i = 1; i <= d; i++)  //����d������
    {
        for (j = 0; j < 10; j++)
            count[j] = 0;  //ÿ�η���ǰ��ռ�����
        for (j = 0; j < n; j++) {
            k = (data[j] / radix) % 10;  //ͳ��ÿ��Ͱ�еļ�¼��
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j];  //��tmp�е�λ�����η����ÿ��Ͱ
        for (j = n - 1; j >= 0; j--)             //������Ͱ�м�¼�����ռ���tmp��
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for (j = 0; j < n; j++)  //����ʱ��������ݸ��Ƶ�data��
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete[] tmp;
    delete[] count;
}
//8.�������������λ��
int sort_laobai::max_bit(int* arr, int N) {
    int max = arr[0];
    int bit = 0;
    for (int i = 0; i < N; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    bit = int(log10(max)) + 1;
    return bit;
}

//2021��10��19��17:41:07