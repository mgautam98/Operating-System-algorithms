#include <bits/stdc++.h>
#include "Semaphore.h"
#include <unistd.h>
using namespace std;
#define CHAIRS 4
Semaphore TobaccoAndPaper(0), PaperAndMatches(0), MatchesAndTobacco(0), DoneSmoking(1);

void Agent()
{
    while (true)
    {
        DoneSmoking.wait();
        int r = rand() % 3;

        switch (r)
        {
        case 0:
            cout<<"Agent has Tobacco and Paper"<<endl;
            TobaccoAndPaper.signal();
            break;
        case 1:
            cout<<"Agent has Paper and Matches"<<endl;
            PaperAndMatches.signal();
            break;
        case 2:
            cout<<"Agent has Matches and Tobacco"<<endl;
            MatchesAndTobacco.signal();
            break;
        }
    }
}

void Smoker_A()
{
    while (true)
    {
        TobaccoAndPaper.wait();
        cout << "Smoker A is smoking" << endl;
        sleep(3);
        DoneSmoking.signal();
    }
}

void Smoker_B()
{
    while (true)
    {
        PaperAndMatches.wait();
        cout << "Smoker B is smoking" << endl;
        sleep(3);
        DoneSmoking.signal();
    }
}

void Smoker_C()
{
    while (true)
    {
        MatchesAndTobacco.wait();
        cout << "Smoker C is smoking" << endl;
        sleep(3);
        DoneSmoking.signal();
    }
}

int main()
{
    thread t0(Agent);
    thread t1(Smoker_A);
    thread t2(Smoker_B);
    thread t3(Smoker_C);

    t0.join();
    t1.join();
    t2.join();
    t3.join();
}