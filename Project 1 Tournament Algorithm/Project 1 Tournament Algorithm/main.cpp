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
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <atomic>
#include "lock.h"

#define CPU_BARRIER()  __sync_synchronize()
#define COMPILER_BARRIER() __asm__ __volatile__("" : : : "memory")
#define CPU_RELAX() __asm__ __volatile__("pause" : : :"memory")

using namespace std;

static int num_of_thread = 0;
int counter = 0;
PetersonSpinLock P;

void DoSomething(int thread_id)
{
    P.AcquireLock(thread_id);
    
    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d started\n", counter);
    
    for(i = 0; i < (0xFFFFFFFF); i++);
    
    printf("\n Job %d finished\n", counter);
    
    P.ReleaseLock(thread_id);

}


int main(int argc, const char * argv[])
{
    // insert code here...
    //num_of_thread = atoi(argv[1]);
    num_of_thread = 2;
    static const int num = 2;
    
    thread my_thread[num];
    
    for (int i = 0; i < num_of_thread; i++)
    {
        my_thread[i] = thread(DoSomething, i);
    }
    
    for (int j = 0; j < num_of_thread; j++)
    {
        my_thread[j].join();
    }
    
    return 0;
}
