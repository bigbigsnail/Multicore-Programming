//
//  lock.h
//  Project 1 Tournament Algorithm
//
//  Created by bigbigsnail on 9/22/16.
//  Copyright © 2016 bigbigsnail. All rights reserved.
//

#ifndef lock_h
#define lock_h

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

using namespace std;

class PetersonSpinLock
{
public:
    PetersonSpinLock()
    {
        flag[0].store(false, memory_order_release);
        flag[1].store(false, memory_order_release);
        victim.store(0, memory_order_release);
    }
    
    void AcquireLock(int id)
    {
        
        if (id == 0)
        {
            flag[0].store(true, memory_order_relaxed);
            victim.exchange(id, memory_order_acq_rel);
            
            while (flag[1].load(memory_order_acquire) == true && victim.load(memory_order_relaxed) == 0)
            {
                this_thread::yield();
            }
        }
        else
        {
            flag[1].store(true, memory_order_relaxed);
            victim.exchange(id, memory_order_acq_rel);
            
            while (flag[0].load(memory_order_acquire) == true && victim.load(memory_order_relaxed) == 1)
            {
                this_thread::yield();
            }
        }
    }
    
    void ReleaseLock(int id)
    {
        if (id == 0)
        {
            flag[0].store(false, memory_order_release);
        }
        else
        {
            flag[1].store(false, memory_order_release);
        }
    }
    
private:
    atomic<bool> flag[2];
    atomic<int> victim;
};


#endif /* lock_h */
