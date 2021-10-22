/*
@file:        joseph.h
@description: 求解约瑟夫问题
@version:     v1.0.0
@author:      Laobai
@time:        2021年10月22日11:07:25
*/

/*
update notes:

v1.0.0 2021年10月22日11:07:25
    TODO in v1.0.1:
        1. gap过大时，先取余
        2. 其他方式优化计算速度
        3. 注释的位置放在某一行的上一行(***改掉行尾注释)
*/
#include "list_circular.h"
#include "tool.h"
class Joseph {
   private:
    int num;             //旅客个数
    int start;           //开始位置
    int gap;             //间隔
    int rest;            //剩余人数
    CircList<int> List;  //旅客链表
    CircList<int> Del;   //删除的旅客链表
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
            List.Insert(List.Length(), ins);  //初始化
        }
    }
    ~Joseph(){};
    void solve();   //解决Joseph问题，结果储存在List和Del中
};

void Joseph::solve() {
    cout << "起始人数为：" << num << endl;
    cout << "报数间隔为：" << gap << endl;
    cout << "起始位置为：" << start << endl;
    cout << "剩余个数为：" << rest << endl;
    cout << "---------- Start Solving ----------" << endl;

    CircLinkNode<int>* current = new CircLinkNode<int>;
    current = List.getHead();
    int i = start;
    int count = num - rest;
    int del;              //删除的序号
    int pos = start - 1;  //记录删除的位置
    while (i--)           //定位到起始位置
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
        // cout << "第" << num - rest - count + 1 << "次删除的位置: " << pos << ",删除的元素为: " << del << endl;
        // List.output();
        Del.Insert(Del.Length(), del);
        pos--;  //删除后的位置在原链表的位置发生改变
    }
    cout << "死亡序号为： " << endl;
    Del.output();
    cout << "剩余序号为" << endl;
    List.output();

    delete current;
}

void Solution() {
    int num;    //旅客个数
    int start;  //开始位置
    int gap;    //间隔
    int rest;   //剩余人数
    get_input(num, 1, INT32_MAX, "请输入开始总人数(1 ~ INT32_MAX): ");
    get_input(start, 1, num, "请输入开始位置(1 ~ 总人数):      ");
    get_input(gap, 1, num, "请输入间隔(1 ~ 总人数-1):        ");
    get_input(rest, 0, num, "请输入剩余人数(0 ~ 总人数):      ");
    cout<<"---------- 初 始 化 ----------"<<endl;
    Joseph J(num, start, gap, rest);
    cout<<"---------- 已 完 成 ----------"<<endl;
    J.solve();
}
