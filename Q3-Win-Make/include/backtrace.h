#pragma once
#define BACKTRACE_SIZE 16
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <iostream>
using namespace std;
void dump(void) {
    int j, nptrs;
    void* buffer[BACKTRACE_SIZE];
    char** strings;

    nptrs = backtrace(buffer, BACKTRACE_SIZE);

    printf("backtrace() returned %d addresses\n", nptrs);

    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }

    for (j = 0; j < nptrs; j++)
        printf("  [%02d] %s\n", j, strings[j]);

    free(strings);
}

void signal_handler(int signo) {
#if 0	
	char buff[64] = {0x00};
		
	sprintf(buff,"cat /proc/%d/maps", getpid());
		
	system((const char*) buff);
#endif

    printf("\n=========>>>catch signal %d <<<=========\n", signo);

    printf("Dump stack start...\n");
    dump();
    printf("Dump stack end...\n");

    signal(signo, SIG_DFL); /* �ָ��ź�Ĭ�ϴ��� */
    raise(signo);           /* ���·����ź� */
}