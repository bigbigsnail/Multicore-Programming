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
string type;

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

int main(int argc, const char * argv[])
{
    // insert code here...
    time_t start_time, end_time;
    
    num_of_thread = atoi(argv[1]);
    
    time(&start_time);
    
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
    
    time(&end_time);
    
    cout<<"Running time: "<<end_time-start_time<<"seconds"<<endl;
    
    return 0;
}
