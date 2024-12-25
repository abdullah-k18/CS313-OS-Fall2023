#include <iostream>

#include <vector>

#include <algorithm>

using namespace std;

struct Partition
{

    int id;

    int size;

    bool occupied;
};

struct Process
{

    int id;

    int size;

    bool allocated;
};

class MFTMemoryManager
{

private:
    vector<Partition> partitions;

    vector<Process> processes;

public:
    MFTMemoryManager(const vector<int> &partitionSizes)
    {
        int partitionId = 1;

        for (int size : partitionSizes)
        {

            partitions.push_back({partitionId++, size, false});
        }
    }

    void allocateMemory(const Process &process)
    {

        auto it = find_if(partitions.begin(), partitions.end(), [&](const Partition &p)
                          {
                              return !p.occupied && p.size >= process.size;
                          });

        if (it != partitions.end())
        {

            Partition &partition = *it;

            partition.occupied = true;

            processes.push_back(process);

            processes.back().allocated = true;

            cout << "Process " << process.id << " allocated to Partition " << partition.id << endl;
        }
        else
        {

            cout << "Process " << process.id << " cannot be allocated. No suitable partition available." << endl;
        }
    }

    void deallocateMemory(int processId)
    {

        auto it = find_if(processes.begin(), processes.end(), [&](const Process &p)
                          {
                              return p.id == processId && p.allocated;
                          });

        if (it != processes.end())
        {

            Process &process = *it;

            process.allocated = false;

            auto partitionIt = find_if(partitions.begin(), partitions.end(), [&](const Partition &p)
                                       {
                                           return p.id == process.id;
                                       });

            if (partitionIt != partitions.end())
            {

                Partition &partition = *partitionIt;

                partition.occupied = false;

                cout << "Memory deallocated for Process " << processId << " from Partition " << partition.id << endl;
            }
        }
        else
        {

            cout << "Process " << processId << " not found or not allocated." << endl;
        }
    }

    void displayMemoryStatus()
    {

        cout << "Memory Status:" << endl;

        for (const Partition &partition : partitions)
        {

            cout << "Partition " << partition.id << ": ";

            if (partition.occupied)
            {

                auto it = find_if(processes.begin(), processes.end(), [&](const Process &p)
                                  {
                                      return p.id == partition.id && p.allocated;
                                  });

                if (it != processes.end())
                {

                    const Process &process = *it;

                    cout << "Process " << process.id << " (Size: " << process.size << ")";
                }
            }
            else
            {

                cout << "Free";
            }

            cout << endl;
        }

        cout << endl;
    }
};

int main()
{

    // Initialize memory partitions with unequal sizes vector<int> partitionSizes = {100, 200, 150, 300};

    MFTMemoryManager memoryManager(partitionSizes);

    // Create processes with different sizes

    vector<Process> processes = {{1, 120, false}, {2, 250, false}, {3, 180, false}, {4, 80, false}};

    // Allocate memory for processes

    for (const Process &process : processes)
    {

        memoryManager.allocateMemory(process);

        memoryManager.displayMemoryStatus();
    }

    // Deallocate memory for a process memoryManager.deallocateMemory(2); memoryManager.displayMemoryStatus();

    return 0;
}