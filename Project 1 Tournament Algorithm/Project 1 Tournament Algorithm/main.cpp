//
//  main.cpp
//  Project 1 Tournament Algorithm
//
//  Created by bigbigsnail on 9/20/16.
//  Copyright © 2016 bigbigsnail. All rights reserved.
//

#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

#define CPU_BARRIER()  __sync_synchronize()
#define COMPILER_BARRIER() __asm__ __volatile__("" : : : "memory")
#define CPU_RELAX() __asm__ __volatile__("pause" : : :"memory")

using namespace std;

int num_of_thread = 0;

class PetersonSpinLock
{
public:
    PetersonSpinLock()
    {
        flag[0] = false;
        flag[1] = false;
    }
    bool acquire_lock(int thread_id)
    {
        flag[thread_id] = true;
        COMPILER_BARRIER();
        victim = thread_id;
        
        CPU_BARRIER();
        while (flag[1-thread_id] == true && victim == thread_id)
        {
            CPU_RELAX();
        }
        
        return true;
    }
    
    bool release_lock(int thread_id)
    {
        flag[thread_id] = false;
        return true;
    }
    
private:
    volatile bool flag[2] = {false,false};
    volatile int victim;
};

class Tournament
{
public:
    void lock(int thread_id, int num_of_threads)
    {
        node_id = thread_id + (num_of_threads-1);
        double tmp = (double)num_of_threads;
        k = (int)log2(tmp);
        
        for (level = 0; level < k; level++)
        {
            p_id[level] = node_id % 2;
            node_id = floor(node_id / 2.0);
            P.acquire_lock(p_id[level]);
        }
        
        return;
    }
    void unlock(int thread_id)
    {
        node_id = 1;
        for (level = k-1; level > 0; k--)
        {
            P.release_lock(thread_id);
            node_id = 2 * node_id + p_id[level];
        }
        
        return;
    }
    
private:
    int node_id;
    int level;
    int p_id[100];
    int k;
    PetersonSpinLock P;
};


void *Do_Something(void *args)
{
    Tournament T;
    int counter = 0;
    unsigned long thread_id;
    
    thread_id = (unsigned long)args;
        
    T.lock(thread_id, num_of_thread);
        
    unsigned long i = 0;
    counter += 1;
    cout<<"\n Job"<<counter<<" started\n";
        
    for(i=0; i<(0xFFFFFFFF);i++);
        
    cout<<"\n Job "<<counter<<"finished\n";
        
        
    T.unlock(thread_id);
    
    return NULL;
}


int main(int argc, const char * argv[]) {
    // insert code here...

    int i,j;
    int thread_result; //check if the thread was created successfully.
    double time_used;
    
    cin>>num_of_thread;
    
    pthread_t my_thread[num_of_thread];
    
    for (i = 0; i < num_of_thread; i++)
    {
        thread_result = pthread_create(&my_thread[i], NULL, Do_Something, (void *)i);
        
        if (thread_result == !0)
        {
            cout<<"Failed to create threads.\n";
            break;
        }
    }
    
    for (j = 0; j < num_of_thread; j++)
    {
        pthread_join(my_thread[i], NULL);
    }
    
    cout<<"DONE"<<endl;
    
    
    return 0;
}
