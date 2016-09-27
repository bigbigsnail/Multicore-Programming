//
//  main.cpp
//  Project 1 Tournament Algorithm
//
//  Created by bigbigsnail on 9/20/16.
//  Copyright © 2016 bigbigsnail. All rights reserved.
//

#include <iostream>
#include <thread>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <atomic>
#include <chrono>
#include <time.h>
#include "PetersonLock.h"
#include "Tournament.h"

#define CPU_BARRIER()  __sync_synchronize()
#define COMPILER_BARRIER() __asm__ __volatile__("" : : : "memory")
#define CPU_RELAX() __asm__ __volatile__("pause" : : :"memory")

using namespace std;

int num_of_thread = 0;
int counter = 0;
Tournament T;


void DoSomething(int thread_id)
{
    T.lock(thread_id, num_of_thread);
    //P.AcquireLock(thread_id);
    
    counter += 1;
    printf("\n Job %d started\n", counter);
    
    this_thread::sleep_for(chrono::seconds(10));
    
    printf("\n Job %d finished\n", counter);
    
    T.unlock(thread_id, num_of_thread);
    //P.ReleaseLock(thread_id);
}

timespec dur(timespec start, timespec end)
{
    timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}


int main(int argc, const char * argv[])
{
    // insert code here...
    timespec start_time, end_time, duration;
    
    num_of_thread = atoi(argv[1]);
    
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
    
    thread *my_thread = new thread[num_of_thread * sizeof(thread*)];
    
    for (int i = 0; i < num_of_thread; i++)
    {
        my_thread[i] = thread(DoSomething, i);
    }
    
    for (int j = 0 ; j < num_of_thread; j++)
    {
        my_thread[j].join();
    }
    
    delete [] my_thread;
    
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
    
    duration = dur(start_time, end_time);
    
    cout<<"Running time: "<<duration.tv_sec<<"secondes"<<endl;
    cout<<"Running time: "<<duration.tv_nsec<<endl;
    
    return 0;
}
