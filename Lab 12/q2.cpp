#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Structure to represent a memory segment
struct MemorySegment {
    int id;          // Segment ID
    int size;        // Size of the segment
    bool allocated;  // Flag indicating whether the segment is allocated or not
};

// Function to perform Worst Fit allocation for virtual memory segmentation
void worstFitSegmentation(MemorySegment memory[], int numSegments, int processID, int processSize) {
    int worstFitIndex = -1;
    int maxSize = INT_MIN;

    for (int i = 0; i < numSegments; ++i) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            // Find the largest free segment that can accommodate the process
            if (memory[i].size > maxSize) {
                maxSize = memory[i].size;
                worstFitIndex = i;
            }
        }
    }

    if (worstFitIndex != -1) {
        // Allocate the memory segment to the process
        memory[worstFitIndex].allocated = true;
        memory[worstFitIndex].id = processID;
        cout << "Process " << processID << " allocated to Segment " << worstFitIndex << endl;
    } else {
        cout << "Process " << processID << " cannot be allocated. Insufficient memory." << endl;
    }
}

// Function to display the current state of virtual memory
void displayVirtualMemory(MemorySegment memory[], int numSegments) {
    cout << "\nVirtual Memory Status:" << endl;
    for (int i = 0; i < numSegments; ++i) {
        cout << "Segment " << i << ": ";
        if (memory[i].allocated)
            cout << "Allocated to Process " << memory[i].id;
        else
            cout << "Free";
        cout << " (Size: " << memory[i].size << " KB)" << endl;
    }
    cout << "------------------------\n";
}

int main() {
    const int numSegments = 6;  // Number of virtual memory segments
    MemorySegment virtualMemory[numSegments];

    // Initialize virtual memory segments
    virtualMemory[0] = { -1, 100, false };
    virtualMemory[1] = { -1, 200, false };
    virtualMemory[2] = { -1, 150, false };
    virtualMemory[3] = { -1, 120, false };
    virtualMemory[4] = { -1, 180, false };
    virtualMemory[5] = { -1, 250, false };

    // Simulate memory allocation for processes using Worst Fit
    worstFitSegmentation(virtualMemory, numSegments, 1, 180);
    displayVirtualMemory(virtualMemory, numSegments);

    return 0;
}