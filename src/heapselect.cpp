#include "heapselect.h"
#include "heap.h"
#include "record.h"

using namespace std;


template <typename T>
vector<T> heapSelect(vector<T>& elements, int k) {
    // empty input
    if (elements.empty())
        return vector<T>();

    // clamp k between 1 and elements.size()
    if (k > elements.size())
        k = elements.size();
    if (k < 1)
        k = 1;

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
    for (int i = 0; i < k; i++)
        maxElements.push_back(elementsHeap.extract());
    // reverse minHeap into descending order
    for (int i = 0; i < maxElements.size() / 2; i++)
        swap(maxElements[i], maxElements[maxElements.size() - i - 1]);

    return maxElements;
}


// template instantiation
template vector<Record> heapSelect<Record>(vector<Record>&, int);
