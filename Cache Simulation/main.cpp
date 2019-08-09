//
//  main.cpp
//  Cache Simulation
//
//  Created by Salma on 11/11/17.
//  Copyright © 2017 mac. All rights reserved.
//

#include <iostream>
#include <vector>


//special nodes for LRU
struct Node{
    int value;
    int frequency =0;
};

int min(int n, int m){
    if(m>n)
        return n;
    else
        return m;
}


//returns true if the special list contains the key value
bool findSpecial(std::vector<Node>list, int key){
    
    bool found = false;
    for(int i=0; i<list.size(); i++){
        if(list[i].value == key){
            list[i].frequency +=1;
            return true;
        }
    }
    return found;
}

//returns the index that contains the least frequency
int getLRUIndex(std::vector<Node>list){
    int index  = 0;
    int minFrequency = list[0].frequency;
    for(int i=0; i<list.size(); i++){
        if(list[i].frequency < minFrequency){
            minFrequency = list[i].frequency;
            index = i;
        }else {
            for(int j=i+1; j<list.size(); j++)
            {
                index = min(i,j);
            }
        }
    }
    return index;
}

//returns true if the queue conatains the key value
bool find(std::vector<int>queue, int key){
    
    bool found =false;
    for(int i=0; i<queue.size(); i++){
        if(queue[i] == key){
            return true;
        }
    }
    return found;
}

//building cache objects
struct Cache{
    
    int cacheSize =0;
    int hit=0;
    double hitRatio =0.0;
    
};


//FIFO Replacement policy
void FIFOcaching(std::vector<int>input, Cache &cache){
    
    //create a queue to hold the cache values
    std::vector<int>queue;
    
    
    for(int i=0; i<input.size(); i++){
        
        //if the input already in the cache, increment the hit counter, and print the marker *
        if(find(queue, input[i])){
            cache.hit +=1;
            printf("* ");
        }
        
        /*
         if the input is not in the cache, an the cache still has available rooms, push the input inside the cache
         */
        else if((!find(queue, input[i])) && (queue.size()< cache.cacheSize)){
            queue.push_back(input[i]);
        }
        
        /*
         if the input is not in the cache and the cache doesn't have available rooms, shift down the elements to eleminate the oldest one, then push the new input
         */
        else if((!find(queue, input[i])) && (queue.size() >= cache.cacheSize)){
            for(int k=0; k<queue.size(); k++){
                queue[k] = queue[k+1];
            }
            queue[cache.cacheSize-1] = input[i];
        }
        
        //this loopm prints the cache content(queue) in each iteration
        for(int j=0; j<queue.size(); j++)
            std::cout << queue[j] << " ";
        std::cout << std::endl;
    }
}



void LRUcaching(std::vector<int>input, Cache &cache){
    //create a queue to hold the cache values
    std::vector<Node>list;
    
    for(int i=0; i<input.size(); i++){
        
        //if the input already in the cache, increment the hit counter, and print the marker *
        if(findSpecial(list, input[i])){
            cache.hit +=1;
            printf("* ");
        }
        
        /*
         if the input is not in the cache, an the cache still has available rooms, push the input inside the cache
         */
        else if((!findSpecial(list, input[i])) && (list.size()< cache.cacheSize)){
            Node a;
            a.value  = input[i];
            list.push_back(a);
        }
        
        /*
         if the input is not in the cache and the cache doesn't have available rooms, replace the node with least frequency with
         the new node
         */
        
        else if((!findSpecial(list, input[i])) && (list.size() >= cache.cacheSize)){
            int index = getLRUIndex(list);
            list[index].value = input[i];
            list[index].frequency = 0;
        }
        
        for(int j=0; j<list.size(); j++)
            std::cout << list[j].value << " ";
        std::cout << std::endl;
    }
    
}

int main(int argc, const char * argv[]) {
    
    
    int N, cache_size, choice;
    double ratio;
    
    std::cout << "Enter the size of the cache: ";
    std::cin >> cache_size;
    std::cout << "\nEnter the size of input: ";
    std::cin >> N;
    
    std::vector<int>inputSource(N);
    
    for(int i=0; i<N; i++){
        std::cout << "Enter the input element: ";
        std::cin >> inputSource[i];
    }
    
    std::cout << "Enter a number to choose Replacement policy: \n1.FIFO Caching \n2.LRU Caching\n";
    std::cin >> choice;
    
    Cache cache;
    cache.cacheSize = cache_size;
    
    switch(choice){
        case 1:
            FIFOcaching(inputSource, cache);
            break;
        case 2:
            LRUcaching(inputSource, cache);
            break;
    }
    
    ratio = (double)cache.hit/N;
    
    std::cout <<"\nHits = "<< cache.hit << "\nHit Ratio = " << ratio << "\n";
    
    return 0;
}

