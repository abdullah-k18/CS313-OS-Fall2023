#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

// Function to find the number of page faults using the LRU page replacement algorithm
int countPageFaults(const vector<int>& pages, int numFrames) {
    int pageFaults = 0;
    unordered_map<int, list<int>::iterator> pageMap;  // Map to store the indices of pages in the list
    list<int> pageList;  // List to maintain the order of recently used pages

    for (int i = 0; i < pages.size(); ++i) {
        int currentPage = pages[i];

        // If the page is not in a frame, replace the least recently used page
        if (pageMap.find(currentPage) == pageMap.end()) {
            ++pageFaults;

            if (pageList.size() == numFrames) {
                int leastRecentlyUsedPage = pageList.back();
                pageList.pop_back();
                pageMap.erase(leastRecentlyUsedPage);
            }

            pageList.push_front(currentPage);
            pageMap[currentPage] = pageList.begin();
        } else {
            // Move the current page to the front of the list
            pageList.erase(pageMap[currentPage]);
            pageList.push_front(currentPage);
            pageMap[currentPage] = pageList.begin();
        }
    }

    return pageFaults;
}

int main() {
    const int numFrames = 4;
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

    int pageFaults = countPageFaults(pages, numFrames);

    cout << "Number of page faults using Least Recently Used algorithm: " << pageFaults << endl;

    return 0;
}
