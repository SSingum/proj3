#include "quickselect.h"

using namespace std;


template <typename T>
float findPivot(vector<T>& elements, int first, int last) {
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
int partition(vector<T>& elements, float pivot, int first, int last) {
    int i = first - 1; // just before first element
    int j = last + 1; // just after last element

    while (true) { // repeat until partitioned
        // find a value left of pivot that is greater
        do { i++; } while (elements[i] < pivot);
        // find a value right of pivot that is lesser
        do { j--; } while (elements[j] > pivot);
        // check if i & j have crossed, meaning they passed over the pivot (done partitioning)
        if (i > j) break;
        // swap the two incorrectly-placed elements into correct positions
        swap(elements[i], elements[j]);
    }

    // note: elements equal to the pivot are placed on the LEFT of the returned pivot index

    // upon breaking, j will be the last element that isn't greater than the pivot
    // logically, this element is the pivot itself
    // thus, we return j, the index of the pivot
    return j;
}

template <typename T>
vector<T> quickSelect(vector<T>& elements, int k) {
    int first = 0;
    int last = elements.size() - 1;
    float pivotVal = findPivot(elements, first, last);
    int pivot;

    if (k < 1)
        k = 1;

    while (true) {
        // partition the current segment of the vector
        pivot = partition(elements, pivotVal, first, last);

        // check if we've found the k largest elements
        if (k == (last - pivot) + 1) { // including pivot, k elements in right partition
            first = pivot;
            break;
        }
        else if (k == (last - pivot)) { // excluding pivot, k elements in right partition
            first = pivot + 1;
            break;
        }
        // otherwise, continue partitioning
        else if (k < (last - pivot)) // k < # elements to right, so partition left further
            last = pivot;
        else // k > # elements to right, so continue partitioning right
            first = pivot + 1;
    }

    // collect and sort the k largest elements
    vector<T> maxElements;
    for (int i = first; i < k; i++)
        maxElements.push_back(elements[i]);
    quickSort(maxElements);

    return maxElements;
}

template <typename T>
void quickSort(vector<T>& elements, int first = 0, int last = -1) {
    if (last < 0) // default
        last = elements.size() - 1;

    if (first < last) {
        // partition
        int pivotValue = findPivot(elements, first, last);
        int pivot = partition(elements, pivotValue, first, last);
        // recursion
        quickSort(elements, first, pivot - 1);
        quickSort(elements, pivot + 1, last);
    }
}
