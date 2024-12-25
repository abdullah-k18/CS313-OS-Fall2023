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


void calculateHRRNTimes(vector<process_control_block>& processes) {
    int currentTime = 0;
    float totalWaitTime = 0, totalTurnaroundTime = 0;
    while (!processes.empty()) {
        float highestRatio = -1;
        int selectedProcess = -1;

        for (size_t i = 0; i < processes.size(); ++i) {
            float ratio = (currentTime - processes[i].arrivalTime + processes[i].burstTime) / float(processes[i].burstTime);
            if (ratio > highestRatio) {
                highestRatio = ratio;
                selectedProcess = i;
            }
        }

        process_control_block selected = processes[selectedProcess];
        processes.erase(processes.begin() + selectedProcess);

        selected.waitTime = currentTime - selected.arrivalTime;
        selected.turnaroundTime = selected.waitTime + selected.burstTime;

        totalWaitTime += selected.waitTime;
        totalTurnaroundTime += selected.turnaroundTime;

        currentTime += selected.burstTime;

        cout << "PID: " << selected.pid << ", Burst Time: " << selected.burstTime
             << ", Wait Time: " << selected.waitTime << ", Turnaround Time: " << selected.turnaroundTime << endl;
    }

    float avgWaitTime = totalWaitTime / processes.size();
    float avgTurnaroundTime = totalTurnaroundTime / processes.size();

    cout << "Average Wait Time: " << avgWaitTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
}

void HRRNScheduling(vector<process_control_block>& processes) {
    calculateHRRNTimes(processes);
}

int main() {
    // Sample processes initialization
    vector<process_control_block> processes = {
        {1, 0, 0, 6, 0, 0, 1},
        {2, 0, 2, 4, 0, 0, 2},
        {3, 0, 4, 2, 0, 0, 3},
        {4, 0, 6, 8, 0, 0, 4}
    };

    HRRNScheduling(processes);

    return 0;
}
