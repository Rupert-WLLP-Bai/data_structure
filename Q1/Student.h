/*
@version: v1.0.1
@author:  Laobai
@time:    2021��10��21��23:12:08
*/

/*
update notes:
v1.0.0 2021��10��19��17:55:52
v1.0.1 2021��10��21��23:12:08
*/

#include <iomanip>
#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;

class Student {
   private:
    string id;        //���
    string name;      //����
    string gender;    //�Ա�
    int age;          //����
    string category;  //���
   public:
    Student() { age = -1; };
    Student(string ID, string NAME, string GENDER, int AGE, string CATEGORY) {
        id = ID;
        name = NAME;
        gender = GENDER;
        category = CATEGORY;
        age = AGE;
    }
    Student(Student& s1) {
        id = s1.id;
        name = s1.name;
        gender = s1.gender;
        category = s1.category;
        age = s1.age;
    }
    ~Student(){};
    friend ostream& operator<<(ostream& out, Student& Stu);  //�������
    friend istream& operator>>(istream& in, Student& Stu);   //��������
    bool operator==(Student& s1);                            //����==
    bool operator!=(Student& s1);                            //����!=
};

inline ostream& operator<<(ostream& out, Student& Stu) {
    out << setiosflags(ios::left);
    out << setw(12) << Stu.id << setw(16) << Stu.name << setw(8) << Stu.gender
        << setw(8) << Stu.age << setw(10) << Stu.category;
    return out;
}

inline istream& operator>>(istream& in, Student& Stu) {
    cin >> Stu.id >> Stu.name >> Stu.gender >> Stu.age >> Stu.category;
    return in;
}

bool Student::operator!=(Student& s1) {
    if (s1.id != id)
        return true;
    if (s1.category != category)
        return true;
    if (s1.gender != gender)
        return true;
    if (s1.age != age)
        return true;
    if (s1.name != name)
        return true;
    return false;
}

bool Student::operator==(Student& s1) {
    if (s1.id != id)
        return false;
    if (s1.category != category)
        return false;
    if (s1.gender != gender)
        return false;
    if (s1.age != age)
        return false;
    if (s1.name != name)
        return false;
    return true;
}
