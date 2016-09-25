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
#include "test-and-set.h"

using namespace std;

TestAndSet TAS_Lock;
int counter = 0;

void DoSomething()
{
    TAS_Lock.lock();
    
    unsigned long i = 0;
    counter += 1;
    
    cout<<"\n Job "<<counter<<" started\n";
    
    for (i = 0; i < (0xFFFFFFFF); i++);
    
    cout<<"\n Job "<<counter<<" finished\n";
    
    TAS_Lock.unlock();
}

int main(int argc, const char * argv[])
{
    // insert code here...
    int num_of_thread = 8;
    static const int num = 8;
    
    thread my_thread[num];
    
    for (int i = 0; i < num_of_thread; i++)
    {
        my_thread[i] = thread(DoSomething);
    }
    
    for (int j = 0; j < num_of_thread; j++)
    {
        my_thread[j].join();
    }
    

    return 0;
}
