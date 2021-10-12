//约瑟夫问题
/*本游戏要求用户输入的内容包括：

1. 旅客的个数，也就是N的值；

2. 离开旅客的间隔书，也就是M的值；

3. 所有旅客的序号作为一组数据要求存放在某种数据结构中。

   本游戏要求输出的内容是包括：

4. 离开旅客的序号；

5. 剩余旅客的序号。*/
#include "CircularList.h"
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
            List.Insert(i, ins);  //初始化
        }
    }
    ~Joseph(){};
    void solve();   //解决Joseph问题，结果储存在List和Del中
    void output();  //输出结果
};

void Joseph::solve() {
    int id = 0;
    // //List.output();  //输出初始链表
    cout << "起始人数为：" << num << endl;
    cout << "报数间隔为：" << gap << endl;
    cout << "起始位置为：" << start << endl;
    cout << "剩余个数为：" << rest << endl;
    cout << "Start Solving." << endl;

    // // //使用current遍历
    // // CircLinkNode<int>* current = List.getHead();  //current指针
    // // if (current == NULL) {
    // //     cerr << "起始位置错误！" << endl;
    // //     exit(1);
    // // }

    // // for (int i = 0; i < start; i++) {
    // //     current = current->Link;  //移动指针到起始位置
    // //     id++;
    // // }
    // // for (int i = 0; i < num - rest; i++) {  //删除次数
    // //     for (int j = 1; j < gap; j++) {     //起始位置为1，很重要!
    // //         // // cout << "current指针的地址为:" << current << endl;
    // //         // // cout << "current->Link的地址为：" << current->Link << endl;
    // //         // // cout << "head的地址为：" << List.getHead() << endl;
    // //         // // cout << "地址偏移量为：" << hex << (current - List.getHead()) * sizeof(current) << endl
    // //         // //      << endl;
    // //         // // cout << dec;
    // //         if (current->Link == List.getHead()) {  //满足这个条件表示current在尾节点
    // //             current = current->Link->Link;      //指向第一个元素
    // //             id = 1;                             //id重置为1
    // //         } else {
    // //             current = current->Link;
    // //             id++;
    // //         }
    // //     }
    // //     cout << "第" << i + 1 << "次删除:";
    // //     cout << "current指向位置的元素为" << current->data << endl;
    // //     int del;
    // //     List.Remove(id, del);

    //使用id计数删除
    id = start;
    for (int i = 0; i < num - rest; i++) {  //删除次数
        for (int j = 1; j < gap; j++) {     //起始位置为1，很重要!
            id++;
        }
        int del;
        id = (id - 1) % List.Length() + 1;
        List.Remove(id, del);
        Del.Insert(Del.Length(), del);  //尾部插入删除的元素，存储
    }
    cout << endl;
    cout << "死亡序号为： " << endl;
    Del.output();
    cout << "剩余序号为" << endl;
    List.output();
}

void Solution() {
    //还需加入四个参数的输入
    //注意四个参数的范围关系
    Joseph J(30, 1, 9, 15);
    J.solve();
}
