#include <bits/stdc++.h>
#include "Semaphore.h"
#include <unistd.h>
using namespace std;
Semaphore mu(1), wrt(1);
int readCount = 0;

void writer(){
    while(true){
        wrt.wait();
        cout<<"Writing is Performed"<<endl;
        wrt.signal();
    }
}

void reader(){
    while(true){
        mu.wait();
        readCount++;
        if(readCount==1) //first reader
        {
            wrt.wait();
        }
        mu.signal();

        cout<<"Reader is reading"<<endl;

        mu.wait();
        readCount--;
        if(readCount==0)
        {
            wrt.signal();
        }
        mu.signal();
    }
}

int main()
{
    thread t0(writer);
    thread t1(reader);

    t0.join();
    t1.join();
}