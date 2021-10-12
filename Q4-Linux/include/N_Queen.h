//N_Queen.h 用栈实现
//1.先实现对栈的某一层元素获取的操作
//2.栈的层数表示行号 栈中的数字表示列号
//3.遍历的时候从栈中取出元素
#include <cmath>
#include <iomanip>
#include <iostream>
#include "LinkedStack.h"
using std::cout;
using std::endl;
//实现栈的某一层元素的获取(选用)
template <class T>
T getElementValue(LinkedStack<T> ST, int layer) {  //layer为0 ~ size-1
    T ret;                                         //返回值
    LinkedStack<T> st;                             //将传入的栈逆置
    while (!st.IsEmpty()) {                        //原栈不空
        T element = ST.top();
        st.Push(element);
    }
    //完成逆置之后,再取出元素,第i层需要执行pop()函数i次
    while (layer--) {
        if (st.Pop())
            ;
        else
            __throw_length_error("所求位置超限,正确的范围是0 ~ Size-1");  //抛出异常
    }
    st.getTop(ret);  //获取栈顶元素
    return ret;      //返回该值
}
//place 检查当前行的皇后是否能够放置在第i列的位置上
bool place(LinkedStack<int> st, int k, int N) {
    st.Push(k);             //先放进去再做判断
    bool flag = 0;          //默认不能放置
    if (st.getSize() == 0)  //如果放置在第一行则返回true,此时size为0
        return true;
    else {
        int size = st.getSize();  //得到大小
        int* map = new int[N];    //创建一个动态数组 将stack的内容放入其中
        for (int i = 0; i < N; i++) {
            map[i] = -1;  //-1表示该行未放置
        }
        for (int i = size - 1; i >= 0; i--) {  //存放
            int top;
            st.getTop(top);
            map[i] = top;  //第i行放置的列号是top
            st.Pop();
        }
        //纵向比对 检查每一列的元素true的个数是否超过1
        bool flag1 = 1;
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (map[i] == map[j])
                    flag1 = 0;
            }
        }
        //主副对角线方向比对
        bool flag2 = 1;
        for (int i = 0; i < size - 1; i++) {
            if (map[i] - map[i + 1] < 2 || map[i] - map[i + 1] > -2) {  //绝对值相减小于2则在对角线上
                flag2 = 0;
            }
        }

        flag = flag1 && flag2;
        delete[] map;
        return flag;
    }
}
//display 输出解
void display_solution(LinkedStack<int> st) {
    static int64_t count = 0;
    int N = st.getSize();
    int* arr = new int[N];  //存放N个位置
    for (int i = N - 1; i >= 0; i--) {
        st.getTop(arr[i]);
        st.Pop();
    }
    cout << setiosflags(ios::right) << setfill('0') << setw(10) << ++count << ": ";
    for (int i = 0; i < N; i++) {
        cout << setw(2) << arr[i] << " ";
    }
    cout << endl;
    delete[] arr;
}
//解法
void Solution(int N) {
    LinkedStack<int> st;         //层数表示行号,值表示列号,从0~N-1进行尝试
    int top;                     //栈顶的值
    bool find = false;           //是否找到可放置的位置
    int layer = st.getSize();    //layer表示当前在第几层,即栈的大小
    st.Push(0);                  //从0开始
    while (st.getSize() != 0) {  //结束的时候st为空
        st.getTop(top);          //top存储栈顶的值
        layer = st.getSize();    //获取层数
        cout << layer << endl;
        if (layer == N) {          //如果栈已经有n个元素
            display_solution(st);  //输出解
        }
        find = false;                  //初始化find为false
        for (int i = 0; i < N; i++) {  //从第0列开始试探有无可行位置
            if (place(st, i, N)) {     //如果第i列可以放置
                st.Push(i);            //放入
                find = true;           //标记
            }
        }
        if (!find) {                 //如果没有找到可以放置的位置
            layer = st.getSize();    //得到层数
            while (layer > 0) {      //层数大于0
                st.getTop(top);      //获取栈顶的值
                if (top == N - 1) {  //如果栈顶元素已经在最后的位置
                    st.Pop();        //回溯
                }
                layer = st.getSize();                //得到当前层数
                st.getTop(top);                      //得到当前栈顶元素
                bool flag = 0;                       //标志
                for (int i = top + 1; i < N; i++) {  //i从上一层的下一个位置开始

                    if (place(st, i, N)) {  //如果可以在第i列放置
                        st.Push(i);         //放入
                        flag = 1;
                        break;
                    }
                }
                if (!flag)     //当前行没有可以放的位置
                    st.Pop();  //退栈
                else
                    break;
            }
        }
    }
}