#include "quickselect.h"

using namespace std;


float findPivot(vector<Record>& records, int first, int last) {
    // find three values to take the median of
    int middle = first + (last - first) / 2;
    float firstVal = records[first].getRevenue();
    float middleVal = records[middle].getRevenue();
    float lastVal = records[last].getRevenue();

    // sort the values, so that middleVal is the median of the three
    if (firstVal > middleVal)
        swap(firstVal, middleVal);
    if (firstVal > lastVal)
        swap(firstVal, lastVal);
    if(middleVal > lastVal)
        swap(middleVal, lastVal);

    return middleVal;
}

int partition(vector<Record>& records, float pivot, int first, int last) {
    int i = first - 1; // just before first element
    int j = last + 1; // just after last element

    while (true) { // repeat until partitioned
        // find a value left of pivot that is greater
        do { i++; } while (records[i].getRevenue() < pivot);
        // find a value right of pivot that is lesser
        do { j--; } while (records[j].getRevenue() > pivot);
        // check if i & j have crossed, meaning they passed over the pivot (done partitioning)
        if (i > j) break;
        // swap the two incorrectly-placed elements into correct positions
        swap(records[i], records[j]);
    }

    // note: elements equal to the pivot are placed on the LEFT of the returned pivot index

    // upon breaking, j will be the last element that isn't greater than the pivot
    // logically, this element is the pivot itself
    // thus, we return j, the index of the pivot
    return j;
}

vector<Record> quickSelect(vector<Record>& records, int k) {
    int first = 0;
    int last = records.size() - 1;
    float pivotVal = findPivot(records, first, last);
    int pivot;

    if (k < 1)
        k = 1;

    while (true) {
        // partition the current segment of the vector
        pivot = partition(records, pivotVal, first, last);

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

    // collect and sort the k largest records
    vector<Record> largestRecords;
    for (int i = first; i < k; i++)
        largestRecords.push_back(records[i]);
    quickSort(largestRecords);

    return largestRecords;
}

void quickSort(vector<Record>& records, int first = 0, int last = -1) {
    if (last < 0) // default
        last = records.size() - 1;

    if (first < last) {
        // partition
        int pivotValue = findPivot(records, first, last);
        int pivot = partition(records, pivotValue, first, last);
        // recursion
        quickSort(records, first, pivot - 1);
        quickSort(records, pivot + 1, last);
    }
}
