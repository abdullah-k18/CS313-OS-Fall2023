#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

// Function to find the number of page faults using the FIFO algorithm
int countPageFaults(const int pages[], int n, int numFrames) {
    queue<int> frameQueue;          // Queue to maintain the order of pages in frames
    unordered_set<int> frameSet;    // Set to check whether a page is present in frames

    int pageFaults = 0;  // Counter for page faults

    // Iterate through each page in the reference string
    for (int i = 0; i < n; ++i) {
        int currentPage = pages[i];

        // Check if the page is not present in the frames
        if (frameSet.find(currentPage) == frameSet.end()) {
            // Page fault occurred
            ++pageFaults;

            // If the frames are full, remove the oldest page
            if (frameQueue.size() == numFrames) {
                int oldestPage = frameQueue.front();
                frameQueue.pop();
                frameSet.erase(oldestPage);
            }

            // Add the current page to frames
            frameQueue.push(currentPage);
            frameSet.insert(currentPage);
        }
    }

    return pageFaults;
}

int main() {
    const int numFrames = 4;
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);

    int pageFaults = countPageFaults(pages, n, numFrames);

    cout << "Number of page faults using FIFO algorithm: " << pageFaults << endl;

    return 0;
}