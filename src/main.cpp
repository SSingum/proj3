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
    string remainder;
    string final;

    // loop through every data point
    for (int i = 0; i < 3000; i++) {
        getline(data22, line);
        Record newRecord;
        istringstream stream(line);

        // loop through each piece of data in each CSV entry
        for (int i = 0; i < 22; i++) {
            getline(stream, token,',');
//          cout << token << endl;
            switch (i) {
                case 0: // COMMENT HERE WHAT DOES THIS DO
                    newRecord.setMonth(stoi(token));
                    break;
                case 1: // COMMENT HERE WHAT DOES THIS DO
                    newRecord.setID(stoi(token));
                    break;
                case 2:
                    if (token[0] == '"') { // COMMENT HERE WHAT DOES THIS MEAN
                        if (token.back() != '"') {
                            while (getline(stream, remainder, ',')) {
                                token += ',' + remainder;
                                if (remainder.back() == '"')
                                    break;
                            }
                        }
                        // COMMENT HERE
                        token = token.substr(1, token.size()-2);
                        newRecord.setName(token);
                    }
                    else // COMMENT HERE WHAT DOES THIS MEAN
                        newRecord.setName(token);
                    break;
                case 16: // COMMENT HERE 
                    newRecord.setType(token);
                    break;
                case 17: // COMMENT HERE 
                    newRecord.setComponent(token);
                    break;
                case 19: // COMMENT HERE
                    newRecord.setVolume(stoi(token));
                    break;
                case 21: // COMMENT HERE 
                    for (char x : token){ // COMMENT what does this loop do
                        if(isdigit(x) || x == '.' || x == '-')
                            final += x;
                    newRecord.setRevenue(stof(final));
                    break;
                default:
                    continue;
                }
            }
        }

        records2022.push_back(newRecord);
    }

    data22.close();
    return 0;
}
