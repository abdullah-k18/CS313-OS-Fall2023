#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct process_control_block {
    int pid;
    int status; 
    int arrivalTime;
    int burstTime;
    int waitTime;
    int turnaroundTime;
    int priority;
};

// Custom comparator for priority queue based on priority
struct PriorityComparator {
    bool operator()(const process_control_block& a, const process_control_block& b) {
        return a.priority > b.priority; // Higher number -> Higher priority
    }
};

void calculateTimes(vector<process_control_block>& processes) {
    int currentTime = 0;
    float totalWaitTime = 0, totalTurnaroundTime = 0;
    for (auto& process : processes) {
        process.waitTime = currentTime - process.arrivalTime;
        process.turnaroundTime = process.waitTime + process.burstTime;
        totalWaitTime += process.waitTime;
        totalTurnaroundTime += process.turnaroundTime;
        currentTime += process.burstTime;
    }

    float avgWaitTime = totalWaitTime / processes.size();
    float avgTurnaroundTime = totalTurnaroundTime / processes.size();

    // Display results
    cout << "PID\tBurst Time\tWait Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        cout << process.pid << "\t" << process.burstTime << "\t\t"
             << process.waitTime << "\t\t" << process.turnaroundTime << endl;
    }
    cout << "Average Wait Time: " << avgWaitTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
}

void priorityScheduling(vector<process_control_block>& processes) {
    priority_queue<process_control_block, vector<process_control_block>, PriorityComparator> readyQueue;

    for (auto& process : processes) {
        readyQueue.push(process);
    }

    calculateTimes(processes);
}

int main() {
    // Sample processes initialization
    vector<process_control_block> processes = {
        {1, 0, 0, 6, 0, 0, 3},
        {2, 0, 2, 4, 0, 0, 1},
        {3, 0, 4, 2, 0, 0, 4},
        {4, 0, 6, 8, 0, 0, 2}
    };

    priorityScheduling(processes);

    return 0;
}