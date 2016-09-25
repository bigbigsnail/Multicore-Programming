//
//  TTAS.h
//  Test-and-set lock
//
//  Created by bigbigsnail on 9/25/16.
//  Copyright © 2016 bigbigsnail. All rights reserved.
//

#ifndef TTAS_h
#define TTAS_h

#include <iostream>
#include <atomic>
#include <thread>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

class TTAS
{
public:
    TTAS()
    {
        flag = 0;
    }
    
    void lock()
    {
        while (true)
        {
            while (flag == 1)
            {
                this_thread::yield();
            }
            if (!(__sync_lock_test_and_set(&flag, 1)))
            {
                break;
            }
            
        }
    }
    
    void unlock()
    {
        __sync_lock_release(&flag, 0);
    }
    
private:
    volatile int flag;
};
#endif /* TTAS_h */
