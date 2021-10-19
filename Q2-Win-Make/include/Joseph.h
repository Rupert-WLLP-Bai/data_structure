//约瑟夫问题
/*本游戏要求用户输入的内容包括：

1. 旅客的个数，也就是N的值；

2. 离开旅客的间隔书，也就是M的值；

3. 所有旅客的序号作为一组数据要求存放在某种数据结构中。

   本游戏要求输出的内容是包括：

4. 离开旅客的序号；

5. 剩余旅客的序号。*/
#include "CircularList.h"
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
            int ins = i + 1;
            List.Insert(List.Length(), ins);  //初始化
        }
    }
    ~Joseph(){};
    void solve();   //解决Joseph问题，结果储存在List和Del中
    void output();  //输出结果
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

    delete[] current;
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
