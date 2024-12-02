#include "heapselect.h"
#include "heap.h"

using namespace std;


template <typename T>
vector<T> heapSelect(vector<T>& elements, int k) {
    // create minHeap of size k to hold the maximum elements
    Heap<T> elementsHeap;

    // iterate through every element
    for (int i = 0; i < elements.size(); i++) {

        // if heap isn't full yet, add to heap
        if (elementsHeap.size() < k)
            elementsHeap.insert(elements[i]);

        // else if current > smallest maxElement, then we replace it
        else if (elements[i] > elementsHeap.peek()) {
            elementsHeap.extract(); // remove smallest element
            elementsHeap.insert(elements[i]); // replace it
        }
    }

    // extract k largest elements from the minHeap
    vector<T> maxElements;
    for (int i = 0; i < elementsHeap.size(); i++)
        maxElements.push_back(elementsHeap.extract());
    maxElements.reverse(); // reverse minHeap into descending order

    return maxElements;
}
