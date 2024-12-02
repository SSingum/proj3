#include <vector>
#include "record.h"

using namespace std;


template <typename T>
class Heap {
    private:
        vector<T> minHeap;
    public:
        // constructor
        Heap();
        // heapify functions
        void heapifyDown(int currIndex);
        void heapifyUp(int currIndex);
        // basic operations
        void insert(T newElement);
        T peek();
        T extract();
        // misc.
        int size();
};
