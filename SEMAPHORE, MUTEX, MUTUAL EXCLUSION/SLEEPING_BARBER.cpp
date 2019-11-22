#include <bits/stdc++.h>
#include "Semaphore.h"
#include <unistd.h>
using namespace std;
#define CHAIRS 4
Semaphore customers(0), barbers(0);
mutex mu;
int waiting = 0;

void barber()
{
    while (1)
    {
        customers.wait();
        mu.unlock();
        waiting = waiting - 1;
        barbers.signal();
        mu.unlock();
        cout << "Barber is cutting Hair" << endl;
        sleep(2);
    }
}

void customer()
{
    while (1)
    {
        mu.lock();
        if (waiting < CHAIRS)
        {
            waiting += 1;
            customers.signal();
            mu.unlock();
            barbers.wait();
            cout << "Customer is getting Haircut." << endl;
            sleep(2);
        }
        else
        {
            mu.lock();
        }
    }
}

int main()
{
    thread t2(customer);
    thread t1(barber);

    t2.join();
    t1.join();
}