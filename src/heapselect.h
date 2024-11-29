#include <vector>

using namespace std;


// iterates through the input and stores the maximum k elements in a minHeap as it goes
// returns a vector of the k maximum elements in ascending order
template <typename T>
vector<T> heapSelect(vector<T>& elements, int k);
