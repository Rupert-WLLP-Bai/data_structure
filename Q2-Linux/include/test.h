//测试函数
#pragma once
#include "CircularList.h"
class test {
   public:
    test(){};
    ~test(){};
    void init_test();
    void insert_test();
    void del_test();
    void circle_count_test();  //循环计数
};

void test::init_test() {
    //检查初始化
    cout << "初始化检测" << endl;
    CircList<int> L1;
    CircList<int> L2(L1);  //拷贝构造
    int start_3 = 999;
    CircList<int> L3(start_3);  //带参构造
    CircList<int> L4(L3);       //拷贝构造L3
    L1.output();
    L2.output();
    L3.output();
    L4.output();
    cout << endl;
}

void test::insert_test() {
    //检查插入
    cout << "插入检测" << endl;
    cout << "空表的插入" << endl;
    CircList<int> L1;  //空表的插入
    L1.output();
    int ins = 1;
    L1.Insert(2, ins);  //非法插入
    L1.output();
    L1.Insert(1, ins);  //非法插入
    L1.output();
    L1.Insert(0, ins);  //空表的插入位置只能是0，与在头部插入等效
    L1.output();

    cout << "尾部插入" << endl;
    for (int i = 1; i <= 5; i++) {
        int tail_ins = i * i + 3;
        L1.Insert(L1.Length(), tail_ins);
        L1.output();
    }

    cout << "头部插入" << endl;
    for (int i = 1; i <= 5; i++) {
        int head_ins = i * i + 3;
        L1.Insert(0, head_ins);
        L1.output();
    }

    cout << "中间位置插入" << endl;
    for (int i = 1; i <= 5; i++) {
        //1 ~ length - 1的位置为中间位置
        int pos = (rand() % L1.Length() - 1) + 1;
        int mid_ins = rand() % 100;
        cout << "第" << i << "次插入位置为第" << pos << "个元素之后" << endl;
        cout << "第" << i << "次插入元素为：" << mid_ins << endl;
        L1.Insert(pos, mid_ins);
        L1.output();
    }
}

void test::del_test() {
    //删除测试
    cout << "删除测试" << endl;
    CircList<int> L1;
    for (int i = 0; i < 20; i++) {
        int ins = rand() % 1000;
        L1.Insert(i, ins);
    }
    cout << "现有的链表为：" << endl;
    L1.output();

    //头部删除
    cout << "头部删除" << endl;
    for (int i = 0; i < 5; i++) {
        int del = 0;
        L1.Remove(1, del);
        cout << "第" << i + 1 << "次删除的元素为" << del << endl;
        L1.output();
    }

    //尾部删除
    cout << "尾部删除" << endl;
    for (int i = 0; i < 5; i++) {
        int del = 0;
        L1.Remove(L1.Length(), del);
        cout << "第" << i + 1 << "次删除的元素为" << del << endl;
        L1.output();
    }

    //中间删除
    cout << "中间删除" << endl;
    for (int i = 0; i < 5; i++) {
        int del = 0;
        int pos = (rand() % L1.Length() - 2) + 2;  //删除的起始位置为1，终止位置为length，故中间位置为2 ~ length-1
        L1.Remove(pos, del);
        cout << "第" << i + 1 << "次删除的位置为" << pos << endl;
        cout << "第" << i + 1 << "次删除的元素为" << del << endl;
        L1.output();
    }

    //删除至空表
    cout << "删除至空表" << endl;
    while (L1.IsEmpty() != true) {
        int del = 0;
        int pos = rand() % L1.Length() + 1;
        cout << "删除位置为：" << pos << endl;
        L1.Remove(pos, del);
        cout << "删除元素为" << del << endl;
        L1.output();
    }
    cout << "删除结束" << endl;

    //空表删除
    cout << "空表删除" << endl;
    L1.output();
    for (int i = 0; i < 1; i++) {
        int del = 0;
        cout << "从头部删除空表" << endl;
        L1.Remove(1, del);  //从头部删除空表
        L1.output();
        cout << "从尾部删除空表" << endl;
        L1.Remove(L1.Length(), del);  //从尾部删除
        L1.output();
    }
}

void test::circle_count_test() {
    const int L = 5;        //随机链表长度
    const int range = 300;  //数字范围
    CircList<int> List;
    srand(time(NULL));
    for (int i = 0; i < L; i++) {
        int ins = rand() % range;
        List.Insert(i, ins);  //随机生成链表
    }
    List.output();

    //测试计数
    cout << "测试_计数" << endl;
    int id = 0;                                      //报数的值，默认为head的值0
    const int start = rand() % List.Length() + 1;    //起始位置为1 ~ length
    const int count = rand() % 10000;                //往后数count
    const int actual_count = count % List.Length();  //实际上的count
    const int times = (count - 1) / 5;               //循环计数次数，经过头结点的次数
    CircLinkNode<int>* current = List.getHead();
    for (int i = 0; i < start; i++) {
        current = current->Link;  //移动指针到起始位置
        id++;
    }
    cout << "起始位置为：" << start << "，起始位置序号为：" << id << endl;
    cout << "起始位置的元素为：" << current->data << endl;
    cout << "从起始位置往后报数的次数为：" << count << "，等价的报数的次数为：" << actual_count << endl;
    for (int i = 1; i < count; i++) {           //报数次数1就是current移动的次数
        if (current->Link == List.getHead()) {  //满足这个条件表示current在尾节点
            current = current->Link->Link;      //指向第一个元素
            id = 1;                             //id重置为1
        } else {
            current = current->Link;
            id++;
        }
    }
    cout << "起始到终止数的轮次数为：" << times << endl;
    cout << "终止位置的序号应该为：" << start + count - List.Length() * times - 1 << endl;
    cout << "终止位置序号为：" << id << endl;
    cout << "终止位置的元素为：" << current->data << endl;

    // //加入间隔删除
    // cout << "测试_加入间隔删除" << endl;
    // List.output();                               //输出初始链表
    // const int gap = rand() % List.Length() + 1;  //间隔范围是1~legnth
    // const int rest = rand() % List.Length();     //剩余人数为0~length-1，即至少删除一个
    // const int del_count = List.Length() - rest;  //范围是1~length
    // for (int i = 0; i < del_count; i++) {
    //     for (int i = 0; i < gap; i++) {
    //         if (current->Link == List.getHead())
    //             current = current->Link;  //遇到头结点跳过
    //         current = current->Link;
    //     }
    //     cout << "删除位置的元素为：" << current->data << endl;
    //     //获取current指针的位置，然后删除
    // }
}

void CircList_Test() {
    srand(time(NULL));
    test T;
    T.init_test();
    T.insert_test();
    T.del_test();
    T.circle_count_test();
}

void f() {
    srand(time(NULL));
    CircList<int> L;
    CircList<int> Del;
    for (int i = 0; i < 15; i++) {
        int ins = i+1;
        L.Insert(i, ins);
    }
    L.output();

    cout << "使用current指针进行遍历" << endl;
    CircLinkNode<int>* current = L.getHead();
    int ID = 0;   //ID
    int GAP = 9;  //删除间隔
    for (int i = 0, count = 103; i < count; i++) {
        if (current == L.getHead()) {
            current = current->Link;
            cout << "(HEAD) --> ";
            i--;
        } else {
            if (ID== GAP) {
                int del;
                L.Remove(ID, del);
                cout << "##删除" << del << "## --> ";
                Del.Insert(Del.Length(), del);
                ID = 0;
                i--;
                continue;
            }
            cout << current->data << "(ID:" << (ID++) % L.Length() + 1 << ") --> ";
            current = current->Link;  //指向下一个
        }
    }
    cout << "END" << endl;
    Del.output();
}