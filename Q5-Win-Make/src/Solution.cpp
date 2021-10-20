#include "Solution.h"
#include <sys/stat.h>  //用于mkdir
#include "Trie.h"      //Trie树

//输入内容
void input(string& filename, string& route) {
    cout << "文件将储存在项目file文件夹下" << endl;
    mkdir("file");
    cout << "输入文件名 :" << endl;
    cin >> filename;
    route += filename;  //路径
    ofstream out;       //输入到文件中
    out.open(route);
    if (out.fail()) {
        cerr << "Error" << endl;
        exit(1);
    }
    //输入内容 或者 随机生成内容 (不含空格)
    //输入内容
    string text;  //输入的文本内容
    cin.get();
    cout << "请输入一段文字" << endl;
    getline(cin, text);
    out << text;  //输入到文件中
    out.close();
}
//输入关键词
void input_key(string& key) {
    //输入关键词(不含空格)
    cout << "输入关键词" << endl;
    cin >> key;
}
//显示源文件
void display_src(string route) {
    //显示源文件
    cout << "显示源文件" << endl;
    int src;
    fstream out;
    out.open(route);
    if (out.fail()) {
        cerr << "Error" << endl;
        exit(2);
    }
    while ((src = out.get())!=EOF) {
        cout << char(src);
    }
    cout << endl;
    out.close();
}
//读取到Trie树中
void read_file(trie<26, IndexClass>& t, string route) {
    ifstream in(route);
    string str;
    char c;
    while (!in.eof()) {
        c = in.get();
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))  //判断有效
            str += c;
        else {
            if (str.size() == 0)
                continue;
            cout << "插入：" << str << endl;
            t.insert(str.begin(), str.end());
            str.clear();
        }
    }
}
//主程序
void Solution() {
    string filename;          //文件名
    string route = "file//";  //文件路径文件夹
    string key;               //关键词
    trie<26, IndexClass> t;   //Trie树
    input(filename, route);   //输入文件名
    input_key(key);           //输入关键字
    read_file(t, route);      //将文本储存在Trie树中(去掉字母以外的内容)
    t.traverse<StringExe>();  //遍历
    display_src(route);       //输出源文件
    //查找结果
}
