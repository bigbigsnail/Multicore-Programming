//
//  Tournament.h
//  Project 1 Tournament Algorithm
//
//  Created by bigbigsnail on 9/23/16.
//  Copyright © 2016 bigbigsnail. All rights reserved.
//

#ifndef Tournament_h
#define Tournament_h

#include <iostream>
#include <thread>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <atomic>
#include "PetersonLock.h"

const int thread_max = 100;
PetersonSpinLock PLock[thread_max];

class Tournament
{
public:
    void lock(int t_id, int num)
    {
        int k;
        int tmp;
        
        tmp = t_id + (num - 1);
        node_id.exchange(tmp);
        
        k = (int)ceil(log2((double)num));
        cout<<k<<"\n";
        
        for (int level = 1; level <= k; level++)
        {
            p_id[level].store((node_id % 2));
            node_id.store(floor(node_id / 2.0));
            
            PLock[node_id.load()].AcquireLock(p_id[level].load());
        }
    }
    
    void unlock(int t_id, int num)
    {
        int tmp;
        node_id.exchange(1, memory_order_acq_rel);
        int k = (int)ceil(log2((double)num));
        
        for (int level = k; level >= 1; level--)
        {
            PLock[node_id.load()].ReleaseLock(p_id[level].load());
            
            tmp = p_id[level].load();
            node_id.store((2 * (node_id.load()) + tmp));
        }
    }
    
private:
    atomic<int> node_id;
    atomic<int> p_id[thread_max];
};

#endif /* Tournament_h */
