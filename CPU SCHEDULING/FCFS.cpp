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
    }

    void Print()
    {
        cout << "|" << PID << "\t|\t" << arrival_time << "\t|\t" << execution_time << "\t|\t" << starting_time << "\t|\t" << waiting_time <<"\t|"<< endl;
    }
};

bool comparator(Process a, Process b)
{
    return (a.arrival_time < b.arrival_time);
}

void Output(vector<Process> p)
{
    cout<<"\n\n-------------------------------------------------------------------------\n";
    cout << "|PID\t|Arrival Time\t|Execution Time\t|Starting Time\t|Waiting Time\t|\n";
    cout<<"-------------------------------------------------------------------------\n";
    for (auto i : p)
    {
        i.Print();
    }
    cout<<"-------------------------------------------------------------------------\n";
}

int main()
{

    freopen("input_FCFS.txt", "r", stdin);
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

    double st = 0, wt = 0;
    for (int i = 0; i < n; i++)
    {
        wt = st - p[i].arrival_time;
        p[i].starting_time = st, p[i].waiting_time = wt;
        st += p[i].execution_time;
    }

    Output(p);

    return 0;
}