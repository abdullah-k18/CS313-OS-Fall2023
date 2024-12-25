#include <iostream>

using namespace std;

void firstFit(int blockSize[], int m, int processSize[], int n)

{

    int allocation[n]; // array to store block number assigned to each process bool flags[m]; // array to indicate whether a block is free or allocated

    // initialize the arrays for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < m; i++)
        flags[i] = false;

    // loop through the processes and find the first fit block for (int i = 0; i < n; i++)

    {

        for (int j = 0; j < m; j++)

        {

            if (flags[j] == false && blockSize[j] >= processSize[i])

            {

                allocation[i] = j; // assign the block number to the process flags[j] = true; // mark the block as allocated

                blockSize[j] -= processSize[i]; // reduce the block size by the process size break;
            }
        }
    }

    // display the allocation details

    cout << "\nProcess No.\tProcess Size\tBlock No.\tBlock Size\n";

    for (int i = 0; i < n; i++)

    {

        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)

            cout << allocation[i] + 1 << "\t\t" << blockSize[allocation[i]] << "\n";
        else
            cout << "Not Allocated\n";
    }
}

int main()

{

    int blockSize[] = {100, 500, 200, 300, 600}; // array of memory blocks int processSize[] = {212, 417, 112, 426}; // array of processes

    int m = sizeof(blockSize) / sizeof(blockSize[0]); // number of blocks

    int n = sizeof(processSize) / sizeof(processSize[0]); // number of processes

    firstFit(blockSize, m, processSize, n); // call the first fit function

    return 0;
}