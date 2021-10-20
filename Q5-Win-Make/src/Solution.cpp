#include "Solution.h"
#include <sys/stat.h>  //����mkdir
#include "Trie.h"      //Trie��

//��������
void input(string& filename, string& route) {
    cout << "�ļ�����������Ŀfile�ļ�����" << endl;
    mkdir("file");
    cout << "�����ļ��� :" << endl;
    cin >> filename;
    route += filename;  //·��
    ofstream out;       //���뵽�ļ���
    out.open(route);
    if (out.fail()) {
        cerr << "Error" << endl;
        exit(1);
    }
    //�������� ���� ����������� (�����ո�)
    //��������
    string text;  //������ı�����
    cin.get();
    cout << "������һ������" << endl;
    getline(cin, text);
    out << text;  //���뵽�ļ���
    out.close();
}
//����ؼ���
void input_key(string& key) {
    //����ؼ���(�����ո�)
    cout << "����ؼ���" << endl;
    cin >> key;
}
//��ʾԴ�ļ�
void display_src(string route) {
    //��ʾԴ�ļ�
    cout << "��ʾԴ�ļ�" << endl;
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
//��ȡ��Trie����
void read_file(trie<26, IndexClass>& t, string route) {
    ifstream in(route);
    string str;
    char c;
    while (!in.eof()) {
        c = in.get();
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))  //�ж���Ч
            str += c;
        else {
            if (str.size() == 0)
                continue;
            cout << "���룺" << str << endl;
            t.insert(str.begin(), str.end());
            str.clear();
        }
    }
}
//������
void Solution() {
    string filename;          //�ļ���
    string route = "file//";  //�ļ�·���ļ���
    string key;               //�ؼ���
    trie<26, IndexClass> t;   //Trie��
    input(filename, route);   //�����ļ���
    input_key(key);           //����ؼ���
    read_file(t, route);      //���ı�������Trie����(ȥ����ĸ���������)
    t.traverse<StringExe>();  //����
    display_src(route);       //���Դ�ļ�
    //���ҽ��
}
