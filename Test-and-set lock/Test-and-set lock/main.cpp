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
#include <new>
#include "test-and-set.h"
#include "TTAS.h"

using namespace std;

TestAndSet TAS_Lock;
TTAS TTAS_Lock;
int counter = 0;
int num_of_thread = 0;
string type;

void DoSomething()
{
    if (type == "TAS")
    {
        TAS_Lock.lock();
    }
    else if (type == "TTAS")
    {
        TTAS_Lock.lock();
    }
    
    unsigned long i = 0;
    counter += 1;
    
    cout<<"\n Job "<<counter<<" started\n";
    
    for (i = 0; i < (0xFFFFFFFF); i++);
    
    cout<<"\n Job "<<counter<<" finished\n";
    
    if (type == "TAS")
    {
        TAS_Lock.lock();
    }
    else if (type == "TTAS")
    {
        TTAS_Lock.unlock();
    }
}

int main(int argc, const char * argv[])
{
    // insert code here...
    time_t start_time, end_time;
    
    num_of_thread = atoi(argv[1]);
    type = atoi(argv[2]);
    
    time(&start_time);
    
    thread *my_thread = new thread[num_of_thread*sizeof(thread*)];
    
    for (int i = 0; i < num_of_thread; i++)
    {
        my_thread[i] = thread(DoSomething);
    }
    
    for (int j = 0; j < num_of_thread; j++)
    {
        my_thread[j].join();
    }
    
    delete[] my_thread;
    
    time(&end_time);
    
    cout<<"Running time: "<<end_time-start_time<<"seconds"<<endl;
    
    return 0;
}
