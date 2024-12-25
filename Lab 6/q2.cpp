#include <iostream>
#include <vector>
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
    int deadline;
    int period; // New field for MD-DM
};

bool compareDeadline(const real_time_process& p1, const real_time_process& p2) {
    return p1.deadline < p2.deadline;
}

void simulateMDDMScheduling(vector<real_time_process>& processes) {
    int time = 0;

    sort(processes.begin(), processes.end(), compareDeadline);

    int totalProcesses = processes.size();

    while (true) {
        bool allCompleted = true;

        for (int i = 0; i < totalProcesses; ++i) {
            if (processes[i].completionTime < time) {
                processes[i].completionTime = time;
            }

            if (processes[i].completionTime < processes[i].deadline) {
                processes[i].completionTime += processes[i].period;
            } else {
                processes[i].completionTime = processes[i].readyTime + processes[i].period;
            }

            if (processes[i].completionTime >= processes[i].deadline + processes[i].period) {
                processes[i].completionTime = processes[i].deadline + processes[i].period;
            }

            if (processes[i].completionTime >= processes[i].deadline) {
                processes[i].completionTime = processes[i].deadline;
            }

            if (processes[i].completionTime > processes[i].readyTime) {
                processes[i].startingTime = processes[i].completionTime - processes[i].processingTime;
                processes[i].status = 1;

                cout << "Process ID: " << processes[i].pid << ", Ready Time: " << processes[i].readyTime
                     << ", Starting Time: " << processes[i].startingTime << ", Completion Time: " << processes[i].completionTime
                     << ", Processing Time: " << processes[i].processingTime << ", Priority: " << processes[i].priority << endl;

                allCompleted = true;
            }
        }
        

        if (allCompleted) {
            break;
        }

        time++;
    }
}

int main() {
    // Example processes
    vector<real_time_process> processes = {
        {1, 0, 0, 0, 0, 5, 1, 8, 10},
        {2, 0, 2, 0, 0, 3, 2, 6, 12},
        {3, 0, 4, 0, 0, 2, 3, 10, 15},
        {4, 0, 6, 0, 0, 4, 4, 12, 20}
    };

    simulateMDDMScheduling(processes);

    return 0;
}