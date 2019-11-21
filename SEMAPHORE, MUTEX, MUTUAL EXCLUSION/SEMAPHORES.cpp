#include <bits/stdc++.h>
#include "Semaphore.h"
#include <unistd.h>
using namespace std;
#define ll long long

Semaphore sem;

void Illstration()
{
    //wait
    sem.wait();
    printf("\nEntered..\n");

    //critical section
    sleep(4);

    //signal
    printf("\nJust Exiting...\n");
    sem.signal();
}

int main()
{
    sem.signal();
    std::thread t1(Illstration);
    std::thread t2(Illstration);

    t1.join();
    t2.join();
}