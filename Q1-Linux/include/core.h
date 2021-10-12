#pragma once
//core.h 系统的实现
#include "Student.h"
class Table {
   private:
    List<Student> L;  //保存数据的链表
   public:
    Table(){};           //构造函数
    ~Table(){};          //析构函数
    void Print();        //输出现有的成员(即统计功能)
    void Spawn();        //生成初始的内容
    void Insert(int i);  //插入
    void Delete(int i);  //删除
    void Search(int i);  //搜索
    void Revise(int i);  //修改
};
//获取输入 不输入cancel_key的值默认无该功能
bool get_input(int& ret, int min, int max, const char* prompt = "", const int cancel = INT32_MIN) {
    while (1) {
        if (cancel != INT32_MIN)
            cout << "(Cancel input key : " << cancel << ")" << endl;
        cout << prompt;
        cin >> ret;
        if (ret == cancel) {
            cout << "Canceled." << endl;
            return false;  //不操作
        }
        if (cin.fail() || ret < min || ret > max) {
            cin.clear();
            cin.ignore(65536, '\n');
            cout << "Error input" << endl;
        } else
            return true;  //操作
    }
}

void fetch_choice(int& ret, Table& T) {
    int pos;                                                                              //操作位置
    get_input(ret, 0, 5, "请选择操作(0.退出程序 1.插入 2.删除 3.查找 4.修改 5.统计)：");  //0~5的输入
    switch (ret) {
        case 0:
            break;
        case 1:
            if (get_input(pos, 0, INT32_MAX, "请选择插入考生的位置，输入0表示插入到开头的位置,输入-1取消操作：", -1))
                T.Insert(pos);
            break;
        case 2:
            if (get_input(pos, 1, INT32_MAX, "请输入删除考生的位置，输入1表示删除开头的位置,输入0取消操作：", 0))
                T.Delete(pos);
            break;
        case 3:
            if (get_input(pos, 1, INT32_MAX, "请输入查找考生的位置，输入1表示查找开头的位置,输入0取消操作：", 0))
                T.Search(pos);
            break;
        case 4:
            if (get_input(pos, 1, INT32_MAX, "请输入修改考生的位置，输入1表示查找开头的位置,输入0取消操作：", 0))
                T.Revise(pos);
            break;
        case 5:
            T.Print();
            break;
    }
}

//建立
void Table::Spawn() {
    int num;
    cout << "首先请建立考生信息系统！" << endl;
    get_input(num, 0, INT32_MAX, "请输入考生人数：");
    Student* stu = new Student[num];
    if (num)
        cout << "请依次输入考生的考号，姓名，性别，年龄以及报考类别！" << endl;
    else {
        cout << "建立空表" << endl;
        return;
    }
    for (int count = 0; count != num; count++) {
        if (count == num)
            break;
        while (1) {
            cout << "请输入第" << count + 1 << "个考生的信息" << endl;
            cin >> stu[count];
            if (cin.fail()) {
                cin.clear();
                cin.ignore(65536, '\n');
                cerr << "输入错误，请重新输入第" << count + 1 << "个考生的信息" << endl;
            } else {
                L.Insert(count, stu[count]);
                break;
            }
        }
    }
}

//输出
void Table::Print() {
    cout << "现有的信息为：" << endl;
    cout << setiosflags(ios::left) << setw(12) << "序号" << setw(16) << "姓名"
         << setw(8) << "性别" << setw(8) << "年龄" << setw(10) << "报考类别"
         << endl;
    L.output();
}

//删除
inline void Table::Delete(int i) {
    Student del;
    if (L.getData(i) == NULL)
        cout << "当前位置没有数据，无法删除" << endl
             << endl;
    else {
        L.Remove(i, del);
        cout << "删除的考生信息为: " << endl;
        cout << setiosflags(ios::left) << setw(12) << "序号" << setw(16) << "姓名"
             << setw(8) << "性别" << setw(8) << "年龄" << setw(10) << "报考类别"
             << endl;
        cout << del << endl
             << endl;
    }
    Print();
}

//插入到第i个之后
inline void Table::Insert(int i) {
    Student ins;
    if (i == 0) {
        while (1) {
            cout << "输入插入的考生信息，顺序为序号，姓名，性别，年龄，报考类别：" << endl;
            cin >> ins;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(65536, '\n');
                cerr << "输入错误，请重新输入修改后的考生的信息" << endl;
            } else {
                L.Insert(0, ins);  //插入
                break;
            }
        }
    } else if (L.Locate(i) != NULL && i > 0) {
        while (1) {
            cout << "输入插入的考生信息，顺序为序号，姓名，性别，年龄，报考类别：" << endl;
            cin >> ins;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(65536, '\n');
                cerr << "输入错误，请重新输入修改后的考生的信息" << endl;
            } else {
                L.Insert(i, ins);  //插入
                break;
            }
        }
    } else {
        cout << "第" << i << "个位置之后不能进行插入" << endl
             << endl;
    }
    Print();
}

//搜索
inline void Table::Search(int i) {
    if (L.Locate(i) != NULL && i > 0) {
        cout << "第" << i << "个考生的信息为：" << endl;
        cout << setiosflags(ios::left) << setw(8) << "序号" << setw(8) << "姓名"
             << setw(8) << "性别" << setw(8) << "年龄" << setw(8) << "报考类别"
             << endl;
        cout << *(L.getData(i)) << endl
             << endl;
    } else {
        cout << "第" << i << "个考生的信息不存在" << endl
             << endl;
    }
}

//修改
inline void Table::Revise(int i) {
    if (L.Locate(i) != NULL && i > 0) {
        cout << "第" << i << "个考生的信息为：" << endl;
        cout << setiosflags(ios::left) << setw(8) << "序号" << setw(8) << "姓名"
             << setw(8) << "性别" << setw(8) << "年龄" << setw(8) << "报考类别"
             << endl;
        cout << *(L.getData(i)) << endl;
        Student del, ins;
        L.Remove(i, del);  //删除
        while (1) {
            cout << "输入修改后的考生信息，顺序为序号，姓名，性别，年龄，报考类别：" << endl;
            cin >> ins;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(65536, '\n');
                cerr << "输入错误，请重新输入修改后的考生的信息" << endl;
            } else {
                L.Insert(i - 1, ins);  //插入
                break;
            }
        }
    } else {
        cout << "第" << i << "个考生的信息不存在" << endl
             << endl;
    }
    Print();
}
