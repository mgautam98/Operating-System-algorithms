#include <bits/stdc++.h>
using namespace std;

class Process
{
public:
    int PID;
    double remaining_time;
    double arrival_time;
    double execution_time;
    double last_time;
    double waiting_time;

    Process()
    {
    }

    Process(int PID, double arrival_time, double execution_time)
    {
        this->PID = PID;
        this->arrival_time = arrival_time;
        this->execution_time = execution_time;
        last_time = arrival_time;
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
        last_time = arrival_time;
        waiting_time = 0;
        remaining_time = execution_time;
    }

    void Print()
    {
        cout << "|" << PID << "\t|\t" << arrival_time << "\t|\t" << execution_time << "\t|\t" << last_time << "\t|\t" << waiting_time << "\t|" << endl;
    }
};

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

    freopen("input_RR.txt", "r", stdin);
    // freopen("output.txt","w",stdout);

    vector<Process> p;

    int n;
    double t;
    cout << "Enter the time/process : ";
    cin >> t;
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

    queue<Process> q;
    vector<Process> Final;
    q.push(p[0]);
    int i = 1;
    double time_elasped = 0;
    cout<<endl;
    while (!q.empty())
    {
        Process temp = q.front();

        q.pop();
        temp.waiting_time+= time_elasped - temp.last_time;
        time_elasped += min(t, temp.remaining_time);
        for (; p[i].arrival_time <= time_elasped && i < n; i++)
        {
            q.push(p[i]);
        }

        temp.last_time = time_elasped; 

        temp.remaining_time -= t;
        if (temp.remaining_time <= 0)
        {
            Final.push_back(temp);
        }
        else
        {
            q.push(temp);
        }
    }

    Output(Final);

    return 0;
}