#include <vector>
#include "record.h"

using namespace std;


// finds a pivot of the given data using the median-of-three strategy
// returns the value of the pivot
float pivot(vector<Record>& records, int first, int last);

// partitions the vector based on input pivot
// returns index of where the pivot was placed after partitioning
int partition(vector<Record>& records, float pivot, int first, int last);

// quickSelect algorithm to find k largest records
// returns vector of k largest records, sorted in descending order
vector<Record> quickSelect(vector<Record>& records, int k);

// quickSort algorithm to sort the k largest records once found
// returns nothing, but sorts the input vector
void quickSort(vector<Record>& records, int first = 0, int last = -1);
