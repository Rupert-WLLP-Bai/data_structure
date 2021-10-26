/*
@file:        sort.h
@description: 排序函数
@version:     v1.0.0
@author:      Laobai
@time:        2021年10月26日16:35:17
*/

/*
update notes:

v1.0.0 2021年10月26日16:35:17
    TODO in v1.0.1
        1. rand的范围在Windows和Linux下不同
*/
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include "stop_watch.h" //计时器
#include <iomanip>
#include <iostream>
#include <vector>   //用于与std::sort进行比较

//排序函数
namespace sort_laobai {
void swap(int& a, int& b);                                             //交换
void assign(int* num, int* _arr, int N);                               //赋值
void std_result(int *_arr);                                            //std::sort的结果
void Bubble_sort(int* _arr);                                           //冒泡排序
void Selection_sort(int* _arr);                                        //选择排序
void Insertion_sort(int* _arr);                                        //插入排序
void Shell_sort(int* _arr);                                            //希尔排序
void Quick_sort(int* _arr);                                            //快速排序(还可以优化)
void Heap_sort(int* _arr);                                             //堆排序
void Merge_sort(int* _arr);                                            //归并排序(二路归并) (可加入n路归并)
void Radix_sort(int* _arr);                                            //基数排序
int64_t Shell_insert(int* arr, int begin, int gap, int N);             //希尔排序插入
int64_t Q_Sort(int left, int right, int* arr);                         //快速排序递归
int64_t adjustHeap(int* arr, int i, int n);                            //调整堆函数
void MergeSort(int* A, int n, int64_t& count);                         //归并排序
int64_t Merge(int* A, int* L, int leftCount, int* R, int rightCount);  //归并
int max_bit(int* arr, int N);                                          //基数排序求最大位数
void radixsort(int* data, int n);                                      //基数排序实现
}  // namespace sort_laobai

//测试函数
namespace test_sort {
void print_arr(int* arr);                   //输出一个*arr,范围决定格式化输出
void generate(int* arr, int n, int range);  //生成随机的*arr,数量为n,范围为0~range-1

}  // namespace test_sort

using namespace std;
using namespace test_sort;

//输出arr
void test_sort::print_arr(int* arr) {
    using namespace sort_laobai;
    //算出*arr中N的值
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
//随机生成(Windows下的RAND_MAX和Linux下不同)
void test_sort::generate(int* arr, int n, int range) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % range;
    }
    arr[n] = -1;
    if (n < 100)
        print_arr(arr);
}

//namespace sort_laobai的实现 只考虑整数的s实现
//交换
void sort_laobai::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
//赋值
void sort_laobai::assign(int* num, int* arr, int N) {
    for (int i = 0; i < N; i++) {
        arr[i] = num[i];
    }
}

//std::sort的结果
void sort_laobai::std_result(int* _arr) {
    //复制
    vector<int> L;
    int* p = _arr;
    while (*p != -1) {
        L.push_back(*p);
        p++;
    }
    //计时开始
    stop_watch T;
    T.start();
    //排序
    sort(L.begin(), L.end());
    //计时结束
    T.stop();
    cout << "------------------std::sort排序的结果-----------------" << endl;
    cout << "Time  :" << T.elapsed() << "  μs" << endl;
    cout << "Count :" << "UNKNOWN" << endl;
    //if (N < 100)
        //print_arr(arr);
    cout << "--------------------------------------------------" << endl;
}

//八种排序(10种)

//1.冒泡排序
void sort_laobai::Bubble_sort(int* _arr) {
    //算出*arr中N的值
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //计数
    int64_t count = 0;
    //申请
    int* arr = new int[N];
    //赋值
    sort_laobai::assign(_arr, arr, N);
    //计时开始
    stop_watch T;
    T.start();
    //排序
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                sort_laobai::swap(arr[j], arr[j + 1]);
                count++;
            }
        }
    }
    //计时结束
    T.stop();
    cout << "--------------------冒泡排序的结果-------------------" << endl;
    cout << "Time  :" << T.elapsed() << "  μs" << endl;
    cout << "Count :" << count << endl;
    //if (N < 100)
        //print_arr(arr);
    cout << "--------------------------------------------------" << endl;
    //释放
    delete[] arr;
}

//2.选择排序
void sort_laobai::Selection_sort(int* _arr) {
    //算出*arr中N的值
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //计数
    int64_t count = 0;
    //申请
    int* arr = new int[N];
    //赋值
    sort_laobai::assign(_arr, arr, N);
    //计时开始
    stop_watch T;
    T.start();
    //排序
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
    //计时结束
    T.stop();
    cout << "--------------------选择排序的结果-------------------" << endl;
    cout << "Time  :" << T.elapsed() << "  μs" << endl;
    cout << "Count :" << count << endl;
   // if (N < 100)
        //print_arr(arr);
    cout << "--------------------------------------------------" << endl;
    //释放
    delete[] arr;
}
//3.直接插入排序
void sort_laobai::Insertion_sort(int* _arr) {
    //算出*arr中N的值
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //计数
    int64_t count = 0;
    //申请
    int* arr = new int[N];
    //赋值
    sort_laobai::assign(_arr, arr, N);
    //计时开始
    stop_watch T;
    T.start();
    //排序
    for (int i = 1; i < N; i++) {
        int temp = i;
        for (int j = i - 1; j >= 0; j--) {
            if (arr[temp] < arr[j]) {
                swap(arr[temp--], arr[j]);
                count++;
            }
        }
    }
    //计时结束
    T.stop();
    cout << "--------------------插入排序的结果-------------------" << endl;
    cout << "Time  :" << T.elapsed() << "  μs" << endl;
    cout << "Count :" << count << endl;
  //  if (N < 100)
     //   print_arr(arr);
    cout << "--------------------------------------------------" << endl;
    //释放
    delete[] arr;
}

//4.希尔排序
void sort_laobai::Shell_sort(int* _arr) {
    //算出*arr中N的值
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //计数
    int64_t count = 0;
    //申请
    int* arr = new int[N];
    //赋值
    sort_laobai::assign(_arr, arr, N);
    //计时开始    
    stop_watch T;
    T.start();
    //排序
    int gap = N / 2;
    while (gap > 0) {
        int begin = gap - 1;
        while (begin >= 0) {
            count += Shell_insert(arr, begin, gap, N);
            begin--;
        }
        gap = gap / 2;
    }
    //计时结束
    T.stop();
    cout << "--------------------希尔排序的结果-------------------" << endl;
    cout << "Time  :" <<T.elapsed() << "  μs" << endl;
    cout << "Count :" << count << endl;
   // if (N < 100)
   //     print_arr(arr);
    cout << "--------------------------------------------------" << endl;
    //释放
    delete[] arr;
}
//4.希尔排序的插入(返回值为count的增量)
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

//5.快速排序
void sort_laobai::Quick_sort(int* _arr) {
    //算出*arr中N的值
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //计数
    int64_t count = 0;
    //申请
    int* arr = new int[N];
    //赋值
    sort_laobai::assign(_arr, arr, N);
    //计时开始
    stop_watch T;
    T.start();
    //排序
    count = Q_Sort(0, N - 1, arr);
    //计时结束
    T.stop();
    cout << "--------------------快速排序的结果-------------------" << endl;
    cout << "Time  :" << T.elapsed() << " μs" << endl;
    cout << "Count :" << count << endl;
  //  if (N < 100)
   //     print_arr(arr);
    cout << "--------------------------------------------------" << endl;
    //释放
    delete[] arr;
}
//5.快速排序递归
int64_t sort_laobai::Q_Sort(int left, int right, int* arr) {
    static int64_t count = 0;
    if (left >= right)
        return 0;
    int i, j, base;
    i = left, j = right;
    base = arr[left];  //取最左边的数为基准数
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
    //基准数归位
    arr[left] = arr[i];
    arr[i] = base;
    Q_Sort(left, i - 1, arr);   //递归左边
    Q_Sort(i + 1, right, arr);  //递归右边
    return count;
}

//6.堆排序
void sort_laobai::Heap_sort(int* _arr) {
    //算出*arr中N的值
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //计数
    int64_t count = 0;
    //申请
    int* arr = new int[N];
    //赋值
    sort_laobai::assign(_arr, arr, N);
    //计时开始
    stop_watch T;
    T.start();
    //排序
    //1.构造大顶堆
    count += adjustHeap(arr, 0, N);
    //2.交换循环
    for (int i = N - 1; i > 0; i--) {
        sort_laobai::swap(arr[0], arr[i]);
        count++;
        count += adjustHeap(arr, 0, i);
    }
    //计时结束
    T.stop();
    cout << "----------------------堆排序的结果-------------------" << endl;
    cout << "Time  :" << T.elapsed() << "  μs" << endl;
    cout << "Count :" << count << endl;
  //  if (N < 100)
  //      print_arr(arr);
    cout << "--------------------------------------------------" << endl;
    //释放
    delete[] arr;
}
//6.调整堆
int64_t sort_laobai::adjustHeap(int* arr, int i, int n) {
    int64_t count = 0;
    int parent = i;         // 父节点下标
    int child = 2 * i + 1;  // 子节点下标
    while (child < n) {
        if (child + 1 < n && arr[child] < arr[child + 1]) {  // 判断子节点那个大，大的与父节点比较
            child++;
        }
        if (arr[parent] < arr[child]) {                  // 判断父节点是否小于子节点
            sort_laobai::swap(arr[parent], arr[child]);  // 交换父节点和子节点
            count++;
            parent = child;  // 子节点下标 赋给 父节点下标
        }
        child = child * 2 + 1;  // 换行，比较下面的父节点和子节点
    }
    return count;
}

//7.二路归并排序
void sort_laobai::Merge_sort(int* _arr) {
    //算出*arr中N的值
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //计数
    int64_t count = 0;
    //申请
    int* arr = new int[N];
    //赋值
    sort_laobai::assign(_arr, arr, N);
    //计时开始
    stop_watch T;
    T.start();
    //排序
    MergeSort(arr, N, count);
    //计时结束
    T.stop();
    cout << "----------------------归并排序的结果-------------------" << endl;
    cout << "Time  :" << T.elapsed() << "  μs" << endl;
    cout << "Count :" << count << endl;
  //  if (N < 100)
  //      print_arr(arr);
    cout << "----------------------------------------------------" << endl;
    //释放
    delete[] arr;
}
//合并
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

//8.基数排序
void sort_laobai::Radix_sort(int* _arr) {
    //算出*arr中N的值
    int* p = _arr;
    int N = 0;
    while (*p != -1) {
        N++;
        p++;
    }
    //计数
    int64_t count = 0;
    //申请
    int* arr = new int[N];
    //赋值
    sort_laobai::assign(_arr, arr, N);
    //计时开始
    stop_watch T;
    T.start();
    //排序
    radixsort(arr, N);
    //计时结束
    T.stop();
    cout << "----------------------基数排序的结果-------------------" << endl;
    cout << "Time  :" << T.elapsed() << "  μs" << endl;
    cout << "Count :" << count << endl;
  //  if (N < 100)
  //      print_arr(arr);
    cout << "--------------------------------------------------" << endl;
    //释放
    delete[] arr;
}
//基数排序
void sort_laobai::radixsort(int* data, int n) {
    int d = max_bit(data, n);
    int* tmp = new int[n];
    int* count = new int[10];  //计数器
    int i, j, k;
    int radix = 1;
    for (i = 1; i <= d; i++)  //进行d次排序
    {
        for (j = 0; j < 10; j++)
            count[j] = 0;  //每次分配前清空计数器
        for (j = 0; j < n; j++) {
            k = (data[j] / radix) % 10;  //统计每个桶中的记录数
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j];  //将tmp中的位置依次分配给每个桶
        for (j = n - 1; j >= 0; j--)             //将所有桶中记录依次收集到tmp中
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for (j = 0; j < n; j++)  //将临时数组的内容复制到data中
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete[] tmp;
    delete[] count;
}
//8.基数排序求最大位数
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

//2021年10月19日17:41:07