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
#include "PetersonLock.h"

const int thread_max = 16;
PetersonSpinLock PLock[thread_max];

class Tournament
{
public:
    void lock(int t_id, int num)
    {
        k = (int)ceil(log2((double)num));
        threads_by_id[t_id].thread_id = t_id + 1;
        threads_by_id[t_id].node_id = threads_by_id[t_id].thread_id + (num - 1);
        
        for (int level = 1; level <= k; level++)
        {
            threads_by_id[t_id].present[level] = threads_by_id[t_id].node_id % 2;
            threads_by_id[t_id].node_id = (int)floor(threads_by_id[t_id].node_id / 2.0);
            node = threads_by_id[t_id].node_id;
            
            PLock[node].AcquireLock(threads_by_id[t_id].present[level]);
        }
    }
    
    void unlock(int t_id, int num)
    {
        k = (int)ceil(log2((double)num));
        
        threads_by_id[t_id].node_id = 1;
        node = threads_by_id[t_id].node_id;
        
        for (int level = k; level >= 1; level--)
        {
            PLock[node].ReleaseLock(threads_by_id[t_id].present[level]);
            node = 2 * node + threads_by_id[t_id].present[level];
            threads_by_id[t_id].node_id = node;
        }
    }
    
private:
    struct thread_node
    {
        int thread_id;
        int node_id;
        int present[thread_max];
    } threads_by_id[thread_max];
    
    int node;
    int k;
};

#endif /* Tournament_h */
