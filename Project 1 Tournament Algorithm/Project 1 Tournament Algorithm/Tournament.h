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

const int thread_max = 4;
PetersonSpinLock PLock[thread_max];

class Tournament
{
public:
    void lock(int t_id, int num)
    {
//        if (num == 2)
//        {
//            PLock[0].AcquireLock(t_id);
//        }
//        else
//        {
            int k = (int)ceil(log2((double)num));
            
            threads_by_id[t_id].thread_id.store(t_id);
            threads_by_id[t_id].node_id.store((t_id + num - 1));
            
            for (int level = 1; level <= k; level++)
            {
                threads_by_id[t_id].present[level].store((threads_by_id[t_id].node_id.load() % 2));
                threads_by_id[t_id].node_id.store((int)floor(threads_by_id[t_id].node_id.load() / 2.0));
                
                PLock[threads_by_id[t_id].node_id.load()].AcquireLock(threads_by_id[t_id].present[level]);
            }
//        }
    }
    
    void unlock(int t_id, int num)
    {
        //if (num == 2)
        //{
        //    PLock[0].ReleaseLock(t_id);
//        }
//        else
//        {
            int k;
            
            k = (int)ceil(log2((double)num));
            threads_by_id[t_id].thread_id.store(t_id);
            threads_by_id[t_id].node_id.store(0);
            node = threads_by_id[t_id].node_id.load();
            
            for (int level = k; level >= 1; level--)
            {
                PLock[node].ReleaseLock(threads_by_id[t_id].present[level]);
                node = (2 * threads_by_id[t_id].node_id.load()) + threads_by_id[t_id].present[level];
            }
            
//        }
    }
    
private:
    struct thread_node
    {
        atomic<int> thread_id;
        atomic<int> node_id;
        atomic<int> present[thread_max];
    } threads_by_id[thread_max];
    
    atomic<int> node;
};

#endif /* Tournament_h */
