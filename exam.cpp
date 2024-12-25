#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    vector<int> resourceRequirements;
    vector<int> resourceAllocated;
    int remainingTime;
};

class Scheduler {
protected:
    vector<Process> processes;
    vector<Process> readyQueue;
    int currentTime;

public:
    Scheduler(vector<Process> processes) : processes(processes), currentTime(0) {}

    const vector<Process>& getProcesses() const {
        return processes;
    }

    void executeRoundRobin(int timeQuantum) {
        while (!processes.empty() || !readyQueue.empty()) {
            // Move processes that have arrived to the ready queue
            while (!processes.empty() && processes.front().arrivalTime <= currentTime) {
                readyQueue.push_back(processes.front());
                processes.erase(processes.begin());
            }

            // Execute processes in the ready queue using Round Robin
            for (auto& process : readyQueue) {
                int executionTime = min(process.remainingTime, timeQuantum);
                process.remainingTime -= executionTime;

                // Update statistics or perform any necessary actions

                currentTime += executionTime;
            }

            // Remove completed processes from the ready queue
            readyQueue.erase(
                remove_if(readyQueue.begin(), readyQueue.end(), [](const Process& p) { return p.remainingTime <= 0; }),
                readyQueue.end());
        }
    }
};

class DeadlockAvoidanceScheduler : public Scheduler {
private:
    vector<int> availableResources;
    vector<vector<int>> maxAllocation;

public:
    DeadlockAvoidanceScheduler(vector<Process> processes, vector<int> availableResources, vector<vector<int>> maxAllocation)
        : Scheduler(processes), availableResources(availableResources), maxAllocation(maxAllocation) {}

    bool isSafeState(int processId, const vector<int>& request) const {
        // Implement Banker's algorithm to check if the system remains in a safe state
        // ...

        return false;  // Replace with the actual implementation
    }

    void allocateResources(Process& process, const vector<int>& request) {
        // Check if the allocation is safe before making changes
        if (isSafeState(process.id, request)) {
            // Make the allocation
            for (int i = 0; i < request.size(); ++i) {
                process.resourceAllocated[i] += request[i];
                availableResources[i] -= request[i];
            }

            cout << "Allocated resources to Process " << process.id << ": ";
            for (int i = 0; i < request.size(); ++i) {
                cout << "R" << i + 1 << ": " << request[i] << " ";
            }
            cout << endl;
        } else {
            // Request denied to prevent deadlock
            // You may implement a strategy here (e.g., put the process in a waiting queue)
            cout << "Resource request denied for Process " << process.id << " to prevent deadlock.\n";
        }
    }
};

int main() {
    vector<Process> processes = {
        {1, 0, 5, {1, 1, 0, 0}, {}, 5},
        {2, 1, 3, {0, 0, 1, 0}, {}, 3},
        {3, 2, 8, {0, 1, 0, 1}, {}, 8},
        {4, 3, 6, {1, 0, 1, 1}, {}, 6}
    };

    vector<int> availableResources = {1, 1, 1, 1};
    vector<vector<int>> maxAllocation = {
        {1, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 1}
    };

    DeadlockAvoidanceScheduler scheduler(processes, availableResources, maxAllocation);
    scheduler.executeRoundRobin(2);

    // Check for deadlock
    bool deadlock = false;
    for (const auto& process : scheduler.getProcesses()) {
        if (process.remainingTime > 0) {
            deadlock = true;
            break;
        }
    }

    if (deadlock) {
        cout << "Deadlock detected in the system.\n";
    } else {
        cout << "No deadlock.\n";
    }

    return 0;
}
