#include <bits/stdc++.h>
using namespace std;

class Process
{
public:
    int PID;
    double arrival_time;
    double execution_time;
    double starting_time;
    double waiting_time;
    double remaining_time;

    Process()
    {
    }

    Process(int PID, double arrival_time, double execution_time)
    {
        this->PID = PID;
        this->arrival_time = arrival_time;
        this->execution_time = execution_time;
        starting_time = 0;
        waiting_time = 0;
        remaining_time = execution_time;
    }

    void Scan()
    {
        cout << "Enter PID : ";
        cin >> PID;
        cout << "Enter Arrival Time : ";
        cin >> arrival_time;
        cout << "Enter Execution Time : ";
        cin >> execution_time;
        starting_time = 0;
        waiting_time = 0;
        remaining_time = execution_time;
    }

    void Print()
    {
        cout << "|" << PID << "\t|\t" << arrival_time << "\t|\t" << execution_time << "\t|\t" << starting_time << "\t|\t" << waiting_time << "\t|" << endl;
    }
};

bool operator<(const Process &p1, const Process &p2)
{
    return p1.remaining_time > p2.remaining_time;
}

bool comparator(Process a, Process b)
{
    return (a.arrival_time < b.arrival_time);
}


void Output(vector<Process> p)
{
    cout << "\n\n-------------------------------------------------------------------------\n";
    cout << "|PID\t|Arrival Time\t|Execution Time\t|Starting Time\t|Waiting Time\t|\n";
    cout << "-------------------------------------------------------------------------\n";
    for (auto i : p)
    {
        i.Print();
    }
    cout << "-------------------------------------------------------------------------\n";
}

int main()
{

    freopen("input_STR.txt", "r", stdin);
    // freopen("output.txt","w",stdout);

    vector<Process> p;

    int n;
    cout << "Enter the number of processes : ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        Process temp;
        temp.Scan();
        p.push_back(temp);
    }

    sort(p.begin(), p.end(), comparator);
    // Output(p);

    priority_queue<Process> pq;
    vector<Process> Final;

    double st = 0, wt = 0;
    pq.push(p[0]);
    int time = 1, i = 1;
    cout<<"\n\tSEQUENCE : \n\t";
    while (!pq.empty())
    {
        Process temp = pq.top();
        cout<<temp.PID<<"->";
        pq.pop();
        if(temp.execution_time==temp.remaining_time && time!=1){
            temp.starting_time = time-1;
        }   

        temp.remaining_time -=1;
        if(temp.remaining_time<=0){
            temp.waiting_time = time - temp.execution_time - temp.arrival_time;
            Final.push_back(temp);
        }else{
            pq.push(temp);
        }

        for(;p[i].arrival_time<=time && i<n; i++){
            pq.push(p[i]);
        }

        time++;
    }
    cout<<"\n";
    Output(Final);

    return 0;
}