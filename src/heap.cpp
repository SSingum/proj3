#include <vector>
#include "heap.h"
#include "record.h"

using namespace std;


// constructor
template <typename T>
Heap<T>::Heap() {}


// heapify functions
template <typename T>
void Heap<T>::heapifyDown(int currIndex) {
    int leftIndex, rightIndex, minIndex;
    int size = this->minHeap.size();
    bool swapped;

    // repeatedly compare with children until children are both smaller
    while (size - 1 > 0) {

        // set indices
        swapped = false;
        leftIndex = 2 * currIndex + 1;
        rightIndex = 2 * currIndex + 2;

        // compare parent to children (minHeap)
        if (leftIndex < size && this->minHeap[leftIndex] < this->minHeap[currIndex]) { // left child exists & left < current
            minIndex = leftIndex;
            swapped = true;
        }
        if (rightIndex < size && this->minHeap[rightIndex] < this->minHeap[currIndex]) { // right child exists & right < current
            // note: if right index exists, left must too -- don't need to check
            if (this->minHeap[rightIndex] < this->minHeap[leftIndex]) { // right < left, thus smallest element, so we swap with it
                minIndex = rightIndex;
                swapped = true;
            }
        }

        // if children weren't larger, we're done heapifying
        if (!swapped) break;
        // else, swap current with its larger child
        else swap(this->minHeap[currIndex], this->minHeap[minIndex]);

        // update current index to its new swapped position
        currIndex = minIndex;
    }
}

template <typename T>
void Heap<T>::heapifyUp(int currIndex) {
    int parentIndex;
    
    if (this->minHeap.size() < 1) // empty heap
        return;

    // repeatedly compare with parent until parent is smaller or we reach the root
    while (currIndex > 0) {

        // set parent index
        parentIndex = (currIndex - 1) / 2;

        // compare parent to child (minHeap)
        if (this->minHeap[parentIndex] > this->minHeap[currIndex]) // current is smaller, so swap
            swap(this->minHeap[parentIndex], this->minHeap[currIndex]);
        else // parent is smaller, so done heapifying
            break;

        // move current to swapped position
        currIndex = parentIndex;
    }
}


// basic operations
template <typename T>
void Heap<T>::insert(T newElement) {
    // insert new element at bottom of heap
    this->minHeap.push_back(newElement);

    // move it upwards until in correct position
    heapifyUp(this->minHeap, this->minHeap.size() - 1);
}

template <typename T>
T Heap<T>::peek() {
    if (this->size() > 0)
        return this->minHeap[0];
    else
        return T();
}

template <typename T>
T Heap<T>::extract() {
    if (this->minHeap.size() < 1) // if empty, return empty record
        return Record();

    // save the minimum and swap it with Last-In-Heap (LIH)
    T min = this->minHeap[0];
    swap(this->minHeap[0], this->minHeap[this->minHeap.size() - 1]);

    // remove the min and heapify LIH to put it in the right spot
    this->minHeap.pop_back();
    heapifyDown(this->minHeap, 0);

    return min;
}


// misc.
template <typename T>
int Heap<T>::size() { return this->minHeap.size(); }
