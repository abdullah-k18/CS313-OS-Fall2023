#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

// Function to find the index of the farthest page in the future
int findFarthestPage(const vector<int>& pages, const unordered_map<int, int>& pageIndices, int start, int end) {
    int farthestIndex = -1;
    int farthestPage = -1;

    for (int i = start; i <= end; ++i) {
        int currentPage = pages[i];

        if (pageIndices.find(currentPage) == pageIndices.end())
            return i; // Return the index if the page won't occur in the future

        int currentIndex = pageIndices.at(currentPage);

        if (currentIndex > farthestIndex) {
            farthestIndex = currentIndex;
            farthestPage = currentPage;
        }
    }

    return farthestIndex;
}

// Function to find the number of page faults using the Optimal Page Replacement algorithm
int countPageFaults(const vector<int>& pages, int numFrames) {
    int pageFaults = 0;
    unordered_map<int, int> pageIndices;  // Map to store the indices of pages in the future

    vector<int> frames(numFrames, -1);  // -1 represents an empty frame

    for (int i = 0; i < pages.size(); ++i) {
        int currentPage = pages[i;

        // If the page is not in a frame, replace the page with the farthest page in the future
        if (find(frames.begin(), frames.end(), currentPage) == frames.end()) {
            ++pageFaults;

            int replaceIndex = findFarthestPage(pages, pageIndices, i + 1, pages.size() - 1);
            int replacePage = frames[replaceIndex % numFrames];

            pageIndices.erase(replacePage);
            pageIndices[currentPage] = i;
            frames[replaceIndex % numFrames] = currentPage;
        } else {
            // Update the index of the page in the future
            pageIndices[currentPage] = i;
        }
    }

    return pageFaults;
}

int main() {
    const int numFrames = 4;
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

    int pageFaults = countPageFaults(pages, numFrames);

    cout << "Number of page faults using Optimal Page Replacement algorithm: " << pageFaults << endl;

    return 0;
}
