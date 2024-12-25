#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitTime;
    int turnaroundTime;
};

bool compareByArrivalTime(const process& a, const process& b) {
    return a.arrivalTime < b.arrivalTime;
}

int main() {
    vector<process> processes;
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        process p;
        p.pid = i + 1;
        cout << "Enter arrival time and burst time for process " << p.pid << ": ";
        cin >> p.arrivalTime >> p.burstTime;
        p.remainingTime = p.burstTime;
        processes.push_back(p);
    }

    sort(processes.begin(), processes.end(), compareByArrivalTime);

    int currentTime = 0;
    int completedProcesses = 0;
    vector<int> executionOrder;

    while (completedProcesses < n) {
        int minRemainingTime = INT_MAX;
        int shortestProcessIndex = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < minRemainingTime && processes[i].remainingTime > 0) {
                minRemainingTime = processes[i].remainingTime;
                shortestProcessIndex = i;
            }
        }

        if (shortestProcessIndex == -1) {
            currentTime++;
        } else {
            executionOrder.push_back(processes[shortestProcessIndex].pid);
            processes[shortestProcessIndex].remainingTime--;
            currentTime++;

            if (processes[shortestProcessIndex].remainingTime == 0) {
                completedProcesses++;
                int processIndex = shortestProcessIndex;
                processes[processIndex].turnaroundTime = currentTime - processes[processIndex].arrivalTime;
                processes[processIndex].waitTime = processes[processIndex].turnaroundTime - processes[processIndex].burstTime;
            }
        }
    }

    cout << "Execution Order: ";
    for (int pid : executionOrder) {
        cout << "P" << pid << " ";
    }
    cout << endl;

    double totalWaitTime = 0;
    double totalTurnaroundTime = 0;

    cout << "Process\tBurst Time\tWait Time\tTurnaround Time\n";
    for (const process& p : processes) {
        cout << "P" << p.pid << "\t\t" << p.burstTime << "\t\t" << p.waitTime << "\t\t" << p.turnaroundTime << "\n";
        totalWaitTime += p.waitTime;
        totalTurnaroundTime += p.turnaroundTime;
    }

    double avgWaitTime = totalWaitTime / n;
    double avgTurnaroundTime = totalTurnaroundTime / n;

    cout << "Average Wait Time: " << avgWaitTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;

    return 0;
}