#include <vector>

using namespace std;


// finds a pivot of the given data using the median-of-three strategy
// returns the value of the pivot
template <typename T>
float pivot(vector<T>& elements, int first, int last);

// partitions the vector based on input pivot
// returns index of where the pivot was placed after partitioning
template <typename T>
int partition(vector<T>& elements, float pivot, int first, int last);

// quickSelect algorithm to find k largest elements
// returns vector of k largest elements, sorted in descending order
template <typename T>
vector<T> quickSelect(vector<T>& elements, int k);

// quickSort algorithm to sort the k largest elements once found
// returns nothing, but sorts the input vector
template <typename T>
void quickSort(vector<T>& elements, int first = 0, int last = -1);
