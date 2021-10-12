/*
输入文件名
输入文本到文件
从文本中读取文件到string 去掉空格 存在trie树中
输入关键字 查找 输出结果 （不区分大小写）
*/

#pragma once
#include <fstream>
#include <iostream>
#include "Trie.h"
using namespace std;

//DEFINITION OF EXCEPTION
#define OPEN_FAILED 1

//输入内容
void input(string& filename, string& route);
//输入关键字
void input_key(string& key);
//输出源文件
void display_src(string route);
//读取文件到Trie树中
void read_file(trie<26, IndexClass>& t, string route);
//检索
int64_t check(string s);
//随机生成一段文字(从文件中读取)
void random_words();

//主程序
void Solution();
