//
//  Cache.h
//  Cache Simulation
//
//  Created by Salma on 11/11/17.
//  Copyright © 2017 mac. All rights reserved.
//

#ifndef Cache_h
#define Cache_h

#include <vector>
#include <queue>

class Cache{
    
public:
    int cache_size;//number of cache frames
    
    int input_size;//number of addresses we get as input
    
    bool full = false; //indicates whether a cache is full or not
    
    int hit = 0; //counter of hits
    double hitRatio;
    
    std::vector<int>input;
    
    Cache(int cacheSize, int inputSize, std::vector<int>inputSource){
        cache_size = cacheSize;
        input_size = inputSize;
        input = inputSource;
    }

    void FIFO(int cacheSize){
        
        std::vector<int>queue;//holds the values in cache
        
        for(int i=0; i<input.size(); i++){
            for(int j=0; j<queue.size(); j++){
                if(input[i] == queue[j])
                    hit++;
            }
            if(queue.size() == cacheSize){
                queue[cacheSize-1] = NULL;
                queue.push_back(input[i]);
            }
        }
        
        for(int i=0; i<queue.size(); i++)
            printf("%d ", queue[i]);
    }
    
    double getHitRatio(int hit, int inputSize){
        hitRatio = (double)hit/inputSize;
        
        return hitRatio;
    }
};
#endif /* Cache_h */
