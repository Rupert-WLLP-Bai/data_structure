#include <iostream>
#include "core.h"
int main() {
	int ret;
	Table T;
	T.Spawn();  //����
	T.Print();//������еı�
	while (1) {
		fetch_choice(ret,T);
		if (ret == 0) {
			cout << "�˳�����" << endl;
			break;
		}
	}
	return 0;
}