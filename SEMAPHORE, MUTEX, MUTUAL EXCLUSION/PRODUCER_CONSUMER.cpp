#include <bits/stdc++.h>
#include "Semaphore.h"
#include <unistd.h>

using namespace std;

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int Index  =0;

Semaphore full,empt(BUFFER_SIZE);
mutex mu;

void produce(){
	while(1){
		sleep(1);
		empt.wait();
		mu.lock();
		int item = rand()%100;
		buffer[Index++] = item;
		cout<<"Produced "<<item<<endl;
		mu.unlock();
		full.signal();
	}
}

void consume(){
	while(1){
		sleep(1);
		full.wait();
		mu.lock();
		int item = buffer[--Index];
		cout<<"Consumed "<<item<<endl;
		mu.unlock();
		empt.signal();
	}
}

int main(){
	empt.signal();
    thread t1(produce);
    thread t2(consume);
    t1.join();
    t2.join();
}