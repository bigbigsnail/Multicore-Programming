//
//  main.cpp
//  Test-and-set lock
//
//  Created by bigbigsnail on 9/25/16.
//  Copyright © 2016 bigbigsnail. All rights reserved.
//

#include <iostream>
#include <atomic>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <chrono>
#include "test-and-set.h"
#include "TTAS.h"

using namespace std;

TestAndSet TAS_Lock;
TTAS TTAS_Lock;
int counter = 0;
int num_of_thread = 0;

void DoSomething()
{
//    TAS_Lock.lock();
    TTAS_Lock.lock();
    
    counter += 1;
    
    cout<<"\n Job "<<counter<<" started\n";
    
    this_thread::sleep_for(chrono::seconds(10));
    
    cout<<"\n Job "<<counter<<" finished\n";
    
//    TAS_Lock.unlock();
    TTAS_Lock.unlock();
}

timespec dur(timespec start, timespec end)
{
    timespec temp;
    if ((end.tv_nsec - start.tv_nsec) < 0)
    {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    }
    else
    {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}


int main(int argc, const char * argv[])
{
    // insert code here...
    double duration;
    timespec start_time, end_time, diff;
    
    num_of_thread = atoi(argv[1]);
    
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
    
    thread *my_thread = new thread[num_of_thread * sizeof(thread*)];
    
    for (int i = 0; i < num_of_thread; i++)
    {
        my_thread[i] = thread(DoSomething);
    }
    
    for (int j = 0; j < num_of_thread; j++)
    {
        my_thread[j].join();
    }
    
    delete[] my_thread;
    
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
    diff = dur(start_time, end_time);
    duration = diff.tv_sec * 1000.0 + diff.tv_nsec / 1000000.0;
    
    cout<<"Running time: "<<duration<<" ms."<<endl;
    
    return 0;
}
