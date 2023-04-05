#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

bool compareArrivalTime(const Process &a, const Process &b) {
    return a.arrival_time < b.arrival_time;
}

bool comparePriority(const Process &a, const Process &b) {
    return a.priority < b.priority;
}

int main() {
    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        std::cout << "Enter arrival time, burst time, and priority for process " << i + 1 << ": ";
        std::cin >> processes[i].arrival_time >> processes[i].burst_time >> processes[i].priority;
    }

    std::sort(processes.begin(), processes.end(), compareArrivalTime);
    int current_time = processes[0].arrival_time;

    while (!processes.empty()) {
        std::vector<Process> ready_queue;
        for (const auto &p : processes) {
            if (p.arrival_time <= current_time) {
                ready_queue.push_back(p);
            } else {
                break;
            }
        }

        if (!ready_queue.empty()) {
            std::sort(ready_queue.begin(), ready_queue.end(), comparePriority);
            Process &selected_process = ready_queue.front();
            selected_process.completion_time = current_time + selected_process.burst_time;
            selected_process.turnaround_time = selected_process.completion_time - selected_process.arrival_time;
            selected_process.waiting_time = selected_process.turnaround_time - selected_process.burst_time;
            current_time = selected_process.completion_time;

            processes.erase(std::remove_if(processes.begin(), processes.end(),
                                           [&](const Process &p) { return p.id == selected_process.id; }),
                            processes.end());
            std::cout << "P" << selected_process.id << "\t" << selected_process.arrival_time << "\t"
                      << selected_process.burst_time << "\t" << selected_process.priority << "\t"
                      << selected_process.completion_time << "\t" << selected_process.turnaround_time << "\t"
                      << selected_process.waiting_time << std::endl;
        } else {
            current_time++;
        }
    }

    // Calculate performance metrics
    double avg_turnaround_time = 0;
    double avg_waiting_time = 0;
    double throughput = 0;
    double cpu_utilization = 0;

    for (const auto &p : processes)
    {
        avg_turnaround_time += p.turnaround_time;
        avg_waiting_time += p.waiting_time;
    }
    avg_turnaround_time /= n;
    avg_waiting_time /= n;

    throughput = double(n) / current_time;

    cpu_utilization = (current_time - processes.front().arrival_time) / double(current_time)*100;

    // Display performance metrics

    std::cout << "Throughput: " << throughput*100 << std::endl;
    std::cout << "CPU utilization: " << cpu_utilization << std::endl;

    return 0;
}
