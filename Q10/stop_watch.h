/*
@file:        stop_watch.h
@description: 实现计时器
@version:     v1.0.0
@author:      Laobai
@time:        2021年10月22日11:27:48
*/

/*
update notes:

v1.0.0 2021年10月22日11:27:48
    TODO in v1.0.1:
        1. 注释的位置放在某一行的上一行(***改掉行尾注释)
        2. 初始化private中的两个LARGE_INTEGER
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
    //微秒
    double elapsed() {
        return static_cast<double>(elapsed_);
    }
    //毫秒
    double elapsed_ms() {
        return elapsed_ / 1000.0;
    }
    //秒
    double elapsed_second() {
        return elapsed_ / 1000000.0;
    }

   private:
    LARGE_INTEGER freq_;
    LARGE_INTEGER begin_time_;
    long long elapsed_;
};

//2021年10月19日17:41:00