//
// Created by dtchorni on 07/11/18.
//

#ifndef A4_OPTIONS_H
#define A4_OPTIONS_H

#include <vector>
//#include <boost/thread.hpp>
#include <thread>

struct Opts{
    bool diffuse=true;
    bool spec=true;
    bool ambient=true;
    bool bound=false;
    bool shadows=true;
    bool phong=true;
    bool thread=true;
    bool gourard=true;
    bool unionAll=false;
    int samples=16;
    int cores=std::thread::hardware_concurrency()*2*samples;

    std::vector<std::thread*> pool;
};

extern Opts options;

#endif //A4_OPTIONS_H
