#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct real_time_process {
    int pid;
    int status;
    int readyTime;
    int startingTime;
    int completionTime;
    int processingTime;
    int priority;
    int deadline; // New field for EDF
};

struct CompareDeadline { // Comparator for EDF
    bool operator()(const real_time_process& p1, const real_time_process& p2) {
        return p1.deadline > p2.deadline;
    }
};

void simulateEDFScheduling(vector<real_time_process>& processes) {
    int time = 0;
    priority_queue<real_time_process, vector<real_time_process>, CompareDeadline> readyQueue;

    sort(processes.begin(), processes.end(), [](const real_time_process& p1, const real_time_process& p2) {
        return p1.readyTime < p2.readyTime;
    });

    int totalProcesses = processes.size();
    int currentProcess = 0;

    while (currentProcess < totalProcesses || !readyQueue.empty()) {
        while (currentProcess < totalProcesses && processes[currentProcess].readyTime <= time) {
            readyQueue.push(processes[currentProcess]);
            currentProcess++;
        }

        if (!readyQueue.empty()) {
            real_time_process current = readyQueue.top();
            readyQueue.pop();

            current.startingTime = max(time, current.readyTime);
            current.completionTime = current.startingTime + current.processingTime;
            current.processingTime = current.completionTime - current.startingTime;

            cout << "Process ID: " << current.pid << ", Ready Time: " << current.readyTime << ", Starting Time: " << current.startingTime
                 << ", Completion Time: " << current.completionTime << ", Processing Time: " << current.processingTime << ", Priority: " << current.priority << endl;

            time = current.completionTime;
        } else {
            time = processes[currentProcess].readyTime;
        }
    }
}

int main() {
    // Example processes
    vector<real_time_process> processes = {
        {1, 0, 0, 0, 0, 5, 1, 8},
        {2, 0, 2, 0, 0, 3, 2, 6},
        {3, 0, 4, 0, 0, 2, 3, 10},
        {4, 0, 6, 0, 0, 4, 4, 12}
    };

    simulateEDFScheduling(processes);

    return 0;
}