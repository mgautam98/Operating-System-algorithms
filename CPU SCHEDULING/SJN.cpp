#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
};

bool compare_arrival_time(Process a, Process b)
{
    return a.arrival_time < b.arrival_time;
}

bool compare_burst_time(Process a, Process b)
{
    return a.burst_time < b.burst_time;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Enter the process ID, arrival time, and burst time for process " << i + 1 << ": ";
        cin >> processes[i].id >> processes[i].arrival_time >> processes[i].burst_time;
    }

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), compare_arrival_time);

    vector<int> completion_times(n);
    vector<int> waiting_times(n);
    vector<int> turnaround_times(n);

    int current_time = 0;

    for (int i = 0; i < n; i++)
    {
        // Sort processes based on burst time among those that have arrived
        sort(processes.begin() + i, processes.end(), compare_burst_time);

        // Calculate completion time of the current process
        completion_times[i] = max(current_time, processes[i].arrival_time) + processes[i].burst_time;

        // Calculate waiting time and turnaround time of the current process
        waiting_times[i] = max(0, current_time - processes[i].arrival_time);
        turnaround_times[i] = completion_times[i] - processes[i].arrival_time;

        // Update current time
        current_time = completion_times[i];
    }

    // Calculate average waiting time and turnaround time
    double avg_waiting_time = 0;
    double avg_turnaround_time = 0;
    for (int i = 0; i < n; i++)
    {
        avg_waiting_time += waiting_times[i];
        avg_turnaround_time += turnaround_times[i];
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    // Print the Gantt chart
    cout << "Gantt chart:" << endl;
    current_time = processes[0].arrival_time;
    for (int i = 0; i < n; i++)
    {
        cout << "| P" << processes[i].id << " ";
        current_time = completion_times[i];
    }
    cout << "|" << endl;

    // Print process details, completion times, waiting times, and turnaround times
    cout << endl
         << "Process Details:" << endl;
    cout << "ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].id << "\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << completion_times[i] << "\t\t" << waiting_times[i] << "\t\t" << turnaround_times[i] << endl;
    }

    // Print average waiting time and turnaround time
    cout << endl
         << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;

    return 0;
}
