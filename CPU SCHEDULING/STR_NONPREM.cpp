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
        cout << "|" << PID << "\t|\t" << arrival_time << "\t|\t" << execution_time << "\t|\t" << starting_time << "\t|\t" << waiting_time << "\t|" << endl;
    }
};

bool operator<(const Process &p1, const Process &p2)
{
    return p1.execution_time > p2.execution_time;
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

    freopen("input_STR_NONPREM.txt", "r", stdin);
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
    int i = 1;
    while (!pq.empty())
    {   
        // priority_queue<Process> tpq;
        // while(!pq.empty()){
        //     Process tp = pq.top();
        //     tp.Print();
        //     tpq.push(tp);
        //     pq.pop();
        // }
        // while(!tpq.empty()){
        //     Process tp = tpq.top();
        //     pq.push(tp);
        //     tpq.pop();
        // }
        // cout<<endl;

        Process temp = pq.top();
        wt = st - temp.arrival_time;
        temp.starting_time = st;
        temp.waiting_time = wt;
        st += temp.execution_time;
        Final.push_back(temp);
        pq.pop();
        
        double upto = temp.starting_time + temp.execution_time;
        // cout<<upto<<endl;
        for(;p[i].arrival_time<=upto && i<n; i++){
            // cout<<p[i].PID<<","<<p[i].arrival_time<<","<<upto<<endl;
            pq.push(p[i]);
        }
    }

    Output(Final);

    return 0;
}