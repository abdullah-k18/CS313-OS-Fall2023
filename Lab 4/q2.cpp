4.#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct process {
    int pid;
    int arrivalTime;
    int burstTime;
    int waitTime;
    int turnaroundTime;
};

bool compareByArrivalTime(const process& a, const process& b) {
    return a.arrivalTime < b.arrivalTime;
}

void calculateWaitTimeTurnaroundTime(vector<process>& processes) {
    int n = processes.size();
    processes[0].waitTime = 0;

    for (int i = 1; i < n; i++) {
        processes[i].waitTime = processes[i - 1].waitTime + processes[i - 1].burstTime;
    }

    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].waitTime + processes[i].burstTime;
    }
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
        processes.push_back(p);
    }

    sort(processes.begin(), processes.end(), compareByArrivalTime);
    calculateWaitTimeTurnaroundTime(processes);

    double totalWaitTime = 0;
    double totalTurnaroundTime = 0;

    cout << "Process\tBurst Time\tWait Time\tTurnaround Time\n";
    for (const process& p : processes) {
        cout << p.pid << "\t\t" << p.burstTime << "\t\t" << p.waitTime << "\t\t" << p.turnaroundTime << "\n";
        totalWaitTime += p.waitTime;
        totalTurnaroundTime += p.turnaroundTime;
    }

    double avgWaitTime = totalWaitTime / n;
    double avgTurnaroundTime = totalTurnaroundTime / n;

    cout << "Average Wait Time: " << avgWaitTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;

    return 0;
5.}