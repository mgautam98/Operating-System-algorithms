#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define NUMBER_OF_PHILOSOPHERS 5

mutex chopsticks[NUMBER_OF_PHILOSOPHERS];
// thread *philosophers[NUMBER_OF_PHILOSOPHERS];

void think(int philosopherNumber) {
    cout<<"\tPhilosopher "<<philosopherNumber<<" is thinking."<<endl;
    sleep(3);
}

void pickUp(int philosopherNumber) {
    int right = philosopherNumber;
    int left = (philosopherNumber + 1)%NUMBER_OF_PHILOSOPHERS;
    if(philosopherNumber%2==0){
        chopsticks[left].lock();
        chopsticks[right].lock();
        cout<<"\tPhilosopher "<<philosopherNumber<<" picked up "<<right<<" and "<<left<<endl;
    }else{
        chopsticks[right].lock();
        chopsticks[left].lock();
        cout<<"\tPhilosopher "<<philosopherNumber<<" picked up "<<left<<" and "<<right<<endl;
    }
}

void eat(int philosopherNumber) {
    cout<<"\tPhilosopher "<<philosopherNumber<<" is Eating."<<endl;
    sleep(3);
}

void putDown(int philosopherNumber) {
    int right = philosopherNumber;
    int left = (philosopherNumber + 1)%NUMBER_OF_PHILOSOPHERS;
    chopsticks[right].unlock();
    chopsticks[left].unlock();
    cout<<"\tPhilosopher "<<philosopherNumber<<" has finished Eating."<<endl;
}

void philosopher(int philosopherNumber){
    while (1) {
		think(philosopherNumber);
		pickUp(philosopherNumber);
		eat(philosopherNumber);
		putDown(philosopherNumber);
	}
}

int main(){
    thread t0(philosopher, 0);
    thread t1(philosopher, 1);
    thread t2(philosopher, 2);
    thread t3(philosopher, 3);
    thread t4(philosopher, 4); 
    t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}