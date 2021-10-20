/*
�����ļ���
�����ı����ļ�
���ı��ж�ȡ�ļ���string ȥ���ո� ����trie����
����ؼ��� ���� ������ �������ִ�Сд��
*/

#pragma once
#include <fstream>
#include <iostream>
#include "Trie.h"
using namespace std;

//DEFINITION OF EXCEPTION
#define OPEN_FAILED 1

//��������
void input(string& filename, string& route);
//����ؼ���
void input_key(string& key);
//���Դ�ļ�
void display_src(string route);
//��ȡ�ļ���Trie����
void read_file(trie<26, IndexClass>& t, string route);
//����
int64_t check(string s);
//�������һ������(���ļ��ж�ȡ)
void random_words();

//������
void Solution();
