#include "quickselect.h"
#include "record.h"

using namespace std;


template <typename T>
float findPivot(vector<T>& elements, int first, int last) {
    // if < 3 elements, just use first element
    if (last - first + 1 < 3)
        return elements[first];
    
    // find three values to take the median of
    int middle = first + (last - first) / 2;
    float firstVal = elements[first];
    float middleVal = elements[middle];
    float lastVal = elements[last];

    // sort the values, so that middleVal is the median of the three
    if (firstVal > middleVal)
        swap(firstVal, middleVal);
    if (firstVal > lastVal)
        swap(firstVal, lastVal);
    if(middleVal > lastVal)
        swap(middleVal, lastVal);

    return middleVal;
}

template <typename T>
int partition(vector<T>& elements, int first, int last) {
    float pivot = findPivot(elements, first, last);
    int i = first - 1; // just before first element
    int j = last + 1; // just after last element

    while (true) { // repeat until partitioned
        // find a value left of pivot that is greater
        do { i++; } while (elements[i] < pivot);
        // find a value right of pivot that is lesser
        do { j--; } while (elements[j] > pivot);
        // check if i & j have crossed, meaning they passed over the pivot (done partitioning -- j rests just before the pivot)
        if (i >= j) return j;
        // swap the two incorrectly-placed elements into correct positions
        swap(elements[i], elements[j]);
    }

}

template <typename T>
vector<T> quickSelect(vector<T>& elements, int k) {
    int first = 0;
    int last = elements.size() - 1;
    int pivot, rightPartition;

    // empty input
    if (elements.empty())
        return vector<T>();

    // clamp k between 1 and elements.size()
    if (k > elements.size())
        k = elements.size();
    if (k < 1)
        k = 1;

    while (k < elements.size()) {
        // partition the current segment of the vector
        pivot = partition(elements, first, last);

        // count elements to the right of pivot
        rightPartition = elements.size() - pivot - 1;

        // check if we've found the k largest elements
        if (k == rightPartition) { // excluding pivot, k elements in right partition
            first = pivot + 1;
            break;
        }
        // otherwise, continue partitioning
        else if (k > rightPartition) // k > # elements to right, so partition left further
            last = pivot;
        else // k > # elements to right, so continue partitioning right
            first = pivot + 1;
    }

    // collect and sort the k largest elements
    vector<T> maxElements;
    for (int i = elements.size() - k; i < elements.size(); i++) // collect
        maxElements.push_back(elements[i]);
    quickSort(maxElements, 0, maxElements.size() - 1); // sort
    for (int i = 0; i < maxElements.size() / 2; i++) // reverse for descending
        swap(maxElements[i], maxElements[maxElements.size() - i - 1]);

    return maxElements;
}

template <typename T>
void quickSort(vector<T>& elements, int first, int last) {
    if (first < last) {
        // partition
        int pivot = partition(elements, first, last);
        // recursion
        quickSort(elements, first, pivot);
        quickSort(elements, pivot + 1, last);
    }
}


// template instantiation
template float findPivot(vector<Record>& elements, int first, int last);
template int partition(vector<Record>& elements, int first, int last);
template vector<Record> quickSelect(vector<Record>& elements, int k);
template void quickSort(vector<Record>& elements, int first, int last);
template void quickSort(vector<int>& elements, int first, int last);