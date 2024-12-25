#include <iostream>

#include <vector>

using namespace std;

struct Process
{

    int id;

    int size;
};

struct Partition
{

    int size;

    bool allocated;

    int processId; // ID of the process currently occupying the partition (if any)
};

vector<Partition> memory;

vector<Process> processes;

void createMemory()
{

    int totalMemory;

    cout << "Enter total memory size: ";

    cin >> totalMemory;

    int numPartitions;

    cout << "Enter number of partitions: ";

    cin >> numPartitions;

    for (int i = 0; i < numPartitions; i++)
    {

        int partitionSize;

        cout << "Enter size of partition " << i + 1 << ": ";
        cin >> partitionSize;

        memory.push_back({partitionSize, false, -1}); // Initially unallocated
    }
}

void createProcesses()
{

    int numProcesses;

    cout << "Enter number of processes: ";

    cin >> numProcesses;
    for (int i = 0; i < numProcesses; i++)
    {

        int processSize;

        cout << "Enter size of process " << i + 1 << ": ";
        cin >> processSize;

        processes.push_back({i + 1, processSize});
    }
}

bool allocateProcess(int processId)
{

    for (Partition &partition : memory)
    {

        if (!partition.allocated && partition.size >= processes[processId].size)
        {
            partition.allocated = true;

            partition.processId = processId;

            cout << "Process " << processId << " allocated in partition of size " << partition.size << endl;

            return true;
        }
    }

    cout << "Process " << processId << " could not be allocated." << endl;
    return false;
}

int main()
{
    createMemory();

    createProcesses();

    for (Process &process : processes)
    {

        allocateProcess(process.id);
    }

    return 0;
}