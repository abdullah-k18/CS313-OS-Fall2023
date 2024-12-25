#include <iostream>

#include <vector>

using namespace std;

// A structure to represent a memory block struct Block {

int start; // starting address of the block int size; // size of the block

bool allocated; // whether the block is allocated or not };

// A function to find the index of the largest free block that can fit a process int findLargestFreeBlock(vector<Block>& blocks, int processSize) {

int largestIndex = -1; // index of the largest free block int largestSize = 0; // size of the largest free block for (int i = 0; i < blocks.size(); i++) {
// if the block is free and large enough

if (!blocks[i].allocated && blocks[i].size >= processSize)
{

    // update the largest index and size if (blocks[i].size > largestSize) {

    largestIndex = i;
    largestSize = blocks[i].size;
}
}
}

return largestIndex; // return the index or -1 if not found
}

// A function to allocate a process to a block using Worst Fit

void allocateProcess(vector<Block> &blocks, int processSize, int processId)
{ // find the index of the largest free block

    int index = findLargestFreeBlock(blocks, processSize);

    // if the block is found if (index != -1) {

    // mark the block as allocated blocks[index].allocated = true;

    // print the allocation details

    cout << "Process " << processId << " of size " << processSize

         << " is allocated to block " << index << " of size " << blocks[index].size

         << "\n";

    // if the block has extra space, split it into two blocks

    if (blocks[index].size > processSize)
    {

        // create a new block with the remaining space Block newBlock;

        newBlock.start = blocks[index].start + processSize;
        newBlock.size = blocks[index].size - processSize;

        newBlock.allocated = false;

        // insert the new block after the allocated block blocks.insert(blocks.begin() + index + 1, newBlock);

        // update the size of the allocated block blocks[index].size = processSize;
    }
}
else
{

    // print the failure message

    cout << "Process " << processId << " of size " << processSize << " cannot be allocated\n";
}
}

// A function to simulate the Worst Fit memory allocation technique void worstFit(vector<int>& blockSizes, vector<int>& processSizes) {

// create a vector of blocks from the block sizes

vector<Block> blocks;

int start = 0; // starting address of the first block for (int size : blockSizes) {

// create a block with the given size and start address Block block;

block.start = start;
block.size = size;
block.allocated = false;
// add the block to the vector

blocks.push_back(block);

// update the start address for the next block start += size;
}

// allocate each process to a block using Worst Fit for (int i = 0; i < processSizes.size(); i++) {

allocateProcess(blocks, processSizes[i], i + 1);
}
}

// A driver function to test the simulation int main() {

// a sample input of block sizes and process sizes vector<int> blockSizes = {100, 500, 200, 300, 600}; vector<int> processSizes = {212, 417, 112, 426};

// simulate the Worst Fit memory allocation technique worstFit(blockSizes, processSizes);

return 0;
}