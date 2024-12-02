#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "record.h"

using namespace std;


class hashMap {
    private:
        // stores total revenue for each company
        vector<Record*> map;
    public:
        // constructor
        hashMap();
        // updates revenue value
        void update(Record updateRecord);
        // misc.
        Record* get(int key);
        // returns total revenue for each company
        vector<Record> getAllRecords();
        // destructor
        ~hashMap();
};
