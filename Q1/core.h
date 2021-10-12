#pragma once
//core.h ϵͳ��ʵ��
#include "Student.h"
class Table {
private:
	List<Student> L;  //�������ݵ�����
public:
	Table() {};           //���캯��
	~Table() {};          //��������
	void Print();        //������еĳ�Ա(��ͳ�ƹ���)
	void Spawn();        //���ɳ�ʼ������
	void Insert(int i);  //����
	void Delete(int i);  //ɾ��
	void Search(int i);  //����
	void Revise(int i);  //�޸�
};
//��ȡ���� ������cancel_key��ֵĬ���޸ù���
bool get_input(int& ret, int min, int max, const char* prompt = "", const int cancel = INT32_MIN) {
	while (1) {
		if (cancel != INT32_MIN)
			cout << "(Cancel input key : " << cancel << ")" << endl;
		cout << prompt;
		cin >> ret;
		if (ret == cancel) 		{
			cout << "Canceled." << endl;
			return false;//������
		}if (cin.fail() || ret < min || ret > max)  {
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "Error input" << endl;
		} 		else
			return true;//����
	}
}

void fetch_choice(int& ret, Table& T) {
	int pos;//����λ��
	get_input(ret, 0, 5, "��ѡ�����(0.�˳����� 1.���� 2.ɾ�� 3.���� 4.�޸� 5.ͳ��)��");  //0~5������
	switch (ret) {
	case 0:
		break;
	case 1:
		if (get_input(pos, 0, INT32_MAX, "��ѡ����뿼����λ�ã�����0��ʾ���뵽��ͷ��λ��,����-1ȡ��������", -1))
			T.Insert(pos);
		break;
	case 2:
		if (get_input(pos, 1, INT32_MAX, "������ɾ��������λ�ã�����1��ʾɾ����ͷ��λ��,����0ȡ��������", 0))
			T.Delete(pos);
		break;
	case 3:
		if (get_input(pos, 1, INT32_MAX, "��������ҿ�����λ�ã�����1��ʾ���ҿ�ͷ��λ��,����0ȡ��������", 0))
			T.Search(pos);
		break;
	case 4:
		if (get_input(pos, 1, INT32_MAX, "�������޸Ŀ�����λ�ã�����1��ʾ���ҿ�ͷ��λ��,����0ȡ��������", 0))
			T.Revise(pos);
		break;
	case 5:
		T.Print();
		break;
	}
}

//����
void Table::Spawn() {
	int num;
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	get_input(num, 0, INT32_MAX, "�����뿼��������");
	Student* stu = new Student[num];
	if (num)
		cout << "���������뿼���Ŀ��ţ��������Ա������Լ��������" << endl;
	else {
		cout << "�����ձ�" << endl;
		return;
	}
	for (int count = 0; count != num; count++) {
		if (count == num)
			break;
		while (1) {
			cout << "�������" << count + 1 << "����������Ϣ" << endl;
			cin >> stu[count];
			if (cin.fail()) {
				cin.clear();
				cin.ignore(65536, '\n');
				cerr << "������������������" << count + 1 << "����������Ϣ" << endl;
			} else {
				L.Insert(count, stu[count]);
				break;
			}
		}
	}
}

//���
void Table::Print() {
	cout << "���е���ϢΪ��" << endl;
	cout << setiosflags(ios::left) << setw(12) << "���" << setw(16) << "����"
		<< setw(8) << "�Ա�" << setw(8) << "����" << setw(10) << "�������"
		<< endl;
	L.output();
}

//ɾ��
inline void Table::Delete(int i) {
	Student del;
	if (L.getData(i) == NULL)
		cout << "��ǰλ��û�����ݣ��޷�ɾ��" << endl
		<< endl;
	else {
		L.Remove(i, del);
		cout << "ɾ���Ŀ�����ϢΪ: " << endl;
		cout << setiosflags(ios::left) << setw(12) << "���" << setw(16) << "����"
			<< setw(8) << "�Ա�" << setw(8) << "����" << setw(10) << "�������"
			<< endl;
		cout << del << endl
			<< endl;
	}
	Print();
}

//���뵽��i��֮��
inline void Table::Insert(int i) {
	Student ins;
	if (i == 0) {
		while (1) {
			cout << "�������Ŀ�����Ϣ��˳��Ϊ��ţ��������Ա����䣬�������" << endl;
			cin >> ins;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(65536, '\n');
				cerr << "������������������޸ĺ�Ŀ�������Ϣ" << endl;
			} else {
				L.Insert(0, ins);//����
				break;
			}
		}
	} else if (L.Locate(i) != NULL && i > 0) {
		while (1) {
			cout << "�������Ŀ�����Ϣ��˳��Ϊ��ţ��������Ա����䣬�������" << endl;
			cin >> ins;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(65536, '\n');
				cerr << "������������������޸ĺ�Ŀ�������Ϣ" << endl;
			} else {
				L.Insert(i, ins);//����
				break;
			}
		}
	} else {
		cout << "��" << i << "��λ��֮���ܽ��в���" << endl
			<< endl;
	}
	Print();
}

//����
inline void Table::Search(int i) {
	if (L.Locate(i) != NULL && i > 0) {
		cout << "��" << i << "����������ϢΪ��" << endl;
		cout << setiosflags(ios::left) << setw(8) << "���" << setw(8) << "����"
			<< setw(8) << "�Ա�" << setw(8) << "����" << setw(8) << "�������"
			<< endl;
		cout << *(L.getData(i)) << endl
			<< endl;
	} else {
		cout << "��" << i << "����������Ϣ������" << endl
			<< endl;
	}
}

//�޸�
inline void Table::Revise(int i) {
	if (L.Locate(i) != NULL && i > 0) {
		cout << "��" << i << "����������ϢΪ��" << endl;
		cout << setiosflags(ios::left) << setw(8) << "���" << setw(8) << "����"
			<< setw(8) << "�Ա�" << setw(8) << "����" << setw(8) << "�������"
			<< endl;
		cout << *(L.getData(i)) << endl;
		Student del, ins;
		L.Remove(i, del);//ɾ��
		while (1) {
			cout << "�����޸ĺ�Ŀ�����Ϣ��˳��Ϊ��ţ��������Ա����䣬�������" << endl;
			cin >> ins;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(65536, '\n');
				cerr << "������������������޸ĺ�Ŀ�������Ϣ" << endl;
			} else {
				L.Insert(i - 1, ins);//����
				break;
			}
		}
	} else {
		cout << "��" << i << "����������Ϣ������" << endl
			<< endl;
	}
	Print();
}
