//
//  test-and-set.h
//  Test-and-set lock
//
//  Created by bigbigsnail on 9/25/16.
//  Copyright © 2016 bigbigsnail. All rights reserved.
//

#ifndef test_and_set_h
#define test_and_set_h

#include <iostream>
#include <atomic>
#include <thread>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class TestAndSet
{
public:
    TestAndSet()
    {
        flag = 0;
    }
    void lock()
    {
        while (__sync_lock_test_and_set(&flag, 1))
        {
            this_thread::yield();
        }
    }
    
    void unlock()
    {
        __sync_lock_release(&flag, 0);
    }
private:
    volatile int flag;
};


#endif /* test_and_set_h */
