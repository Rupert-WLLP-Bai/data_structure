/*
@file:        stop_watch.h
@description: ʵ�ּ�ʱ��
@version:     v1.0.0
@author:      Laobai
@time:        2021��10��22��11:27:48
*/

/*
update notes:

v1.0.0 2021��10��22��11:27:48
    TODO in v1.0.1:
        1. ע�͵�λ�÷���ĳһ�е���һ��(***�ĵ���βע��)
        2. ��ʼ��private�е�����LARGE_INTEGER
*/

#pragma once
#include <Windows.h>
class stop_watch {
   public:
    stop_watch()
        : elapsed_(0) {
        QueryPerformanceFrequency(&freq_);
    }
    ~stop_watch() {}

   public:
    void start() {
        QueryPerformanceCounter(&begin_time_);
    }
    void stop() {
        LARGE_INTEGER end_time;
        QueryPerformanceCounter(&end_time);
        elapsed_ += (end_time.QuadPart - begin_time_.QuadPart) * 1000000 / freq_.QuadPart;
    }
    void restart() {
        elapsed_ = 0;
        start();
    }
    //΢��
    double elapsed() {
        return static_cast<double>(elapsed_);
    }
    //����
    double elapsed_ms() {
        return elapsed_ / 1000.0;
    }
    //��
    double elapsed_second() {
        return elapsed_ / 1000000.0;
    }

   private:
    LARGE_INTEGER freq_;
    LARGE_INTEGER begin_time_;
    long long elapsed_;
};

//2021��10��19��17:41:00