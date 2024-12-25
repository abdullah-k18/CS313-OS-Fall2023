#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Structure to represent a memory partition
struct MemoryPartition {
    int id;          // Partition ID
    int size;        // Size of the partition
    bool allocated;  // Flag indicating whether the partition is allocated or not
};

// Structure to represent a page table entry
struct PageTableEntry {
    int frameNumber;  // Frame number in memory
    bool valid;       // Flag indicating whether the entry is valid or not
};

// Function to perform Worst Fit allocation
void worstFit(MemoryPartition memory[], int numPartitions, int processID, int processSize) {
    int worstFitIndex = -1;
    int maxSize = INT_MIN;

    for (int i = 0; i < numPartitions; ++i) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            // Find the largest free partition that can accommodate the process
            if (memory[i].size > maxSize) {
                maxSize = memory[i].size;
                worstFitIndex = i;
            }
        }
    }

    if (worstFitIndex != -1) {
        // Allocate the memory partition to the process
        memory[worstFitIndex].allocated = true;
        memory[worstFitIndex].id = processID;
        cout << "Process " << processID << " allocated to Partition " << worstFitIndex << endl;
    } else {
        cout << "Process " << processID << " cannot be allocated. Insufficient memory." << endl;
    }
}

// Function to simulate two-level paging
void twoLevelPaging(int numPages, int numFrames, int processID, int processSize) {
    const int pageSize = 100;  // Example: Each page is 100 KB
    const int entriesPerPageTable = 4;  // Example: Each page table has 4 entries

    vector<vector<PageTableEntry>> pageTables(numPages / entriesPerPageTable, vector<PageTableEntry>(entriesPerPageTable));
    vector<bool> frames(numFrames, false);

    int remainingSize = processSize;

    for (int i = 0; i < pageTables.size(); ++i) {
        for (int j = 0; j < entriesPerPageTable; ++j) {
            if (remainingSize > 0) {
                int frameNumber = rand() % numFrames;
                while (frames[frameNumber]) {
                    frameNumber = rand() % numFrames;
                }

                // Assign the frame to the page table entry
                pageTables[i][j].frameNumber = frameNumber;
                pageTables[i][j].valid = true;

                // Mark the frame as allocated
                frames[frameNumber] = true;

                cout << "Page " << (i * entriesPerPageTable + j) << " of Process " << processID << " allocated to Frame " << frameNumber << endl;

                remainingSize -= pageSize;
            } else {
                // No more pages needed for the process
                return;
            }
        }
    }
}

// Function to display the current state of memory
void displayMemory(MemoryPartition memory[], int numPartitions) {
    cout << "\nMemory Status:" << endl;
    for (int i = 0; i < numPartitions; ++i) {
        cout << "Partition " << i << ": ";
        if (memory[i].allocated)
            cout << "Allocated to Process " << memory[i].id;
        else
            cout << "Free";
        cout << " (Size: " << memory[i].size << " KB)" << endl;
    }
    cout << "------------------------\n";
}

int main() {
    const int numPartitions = 5;  // Number of memory partitions
    MemoryPartition memory[numPartitions];

    // Initialize memory partitions
    for (int i = 0; i < numPartitions; ++i) {
        memory[i].id = -1;        // -1 indicates no process allocated
        memory[i].size = 200;     // Example: Each partition is 200 KB
        memory[i].allocated = false;
    }

    // Simulate memory allocation for processes using Worst Fit
    worstFit(memory, numPartitions, 1, 250);
    displayMemory(memory, numPartitions);

    // Simulate two-level paging for a process
    twoLevelPaging(8, 16, 2, 500);

    return 0;
    }