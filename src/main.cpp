#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "record.h"

using namespace std;


int main() {

    // open CSV file
    ifstream data22("../data/SalesData2022.csv");
    vector<Record> records2022;

    if (!data22.is_open())
        cout << "Sales data is not open!" << endl;

    // clear template lines of the CSV
    string line; 
    getline(data22, line);
    getline(data22, line);
    
    // initialize variables for loop
    string token; 
    string final;

    // loop through every data point
    for (int j = 0; j < 3000; j++) {
        getline(data22, line);
        Record newRecord;
        istringstream stream(line);

        // loop through each piece of data in each CSV entry
        for (int i = 0; i < 22; i++) {
            getline(stream, token,',');
//          cout << token << endl;
            string remainder = " ";
            switch (i) {
                case 0: { // assigns billing month to new record
                    newRecord.setMonth(stoi(token));
                    break;
                }
                case 1: { // assigns company id
                    newRecord.setID(stoi(token));
                    break;
                }
                case 2: {
                    if (token[0] == '"') { // includes commas in company name
                        if (token.back() != '"') {
                            while (getline(stream, remainder, ',')) {
                                token += ',' + remainder;
                                if (remainder.back() == '"')
                                    break;
                            }
                        }
                        // assigns company name 
                        token = token.substr(1, token.size()-2);
                        newRecord.setName(token);
                    }
                    else // assigns company name immediately if no commas
                        newRecord.setName(token);
                    break;
                }
                case 16: { // assigns revenue type
                    newRecord.setType(token);
                    break;
                }
                case 17: {// assigns revenue component 
                    newRecord.setComponent(token);
                    break;
                }
                case 19: { // assigns volume of product bought 
                    newRecord.setVolume(stoi(token));
                    break;
                }
                case 21: {// assigns revenue amount
                    newRecord.setRevenue(stof(token));
                    break;
                }
                default: {
                    continue;
                }
                }
            }

            records2022.push_back(newRecord);
        }

        data22.close();
        return 0;

    }

