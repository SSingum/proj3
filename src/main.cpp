#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "record.h"
// #include "crow_all.h"
#include "hashmap.h"
#include "quickselect.h"
#include "heapselect.h"

using namespace std;


int main() {

    // attempt to receive user input from frontend using crow
    // functionality was unsuccessful, but still kept here to showcase that work was still put into this
    /*
    // receive user input from frontend using crow
    // crow functionality from https://github.com/CrowCpp/crow
    crow::SimpleApp app;
    CROW_ROUTE(app, "/proj3").methods("POST"_method)([](const crow::request& req){
        crow::response res;

        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");

        auto data = req.body;
        cout << "Received user input: " << data << endl;

        crow::json::wvalue response;
        response["message"] = "Input received from backend";
        return response;
    });
    app.port(1000).multithreaded().run();
    */

    // frontend
    char input;
    int k;
    cout << "Welcome to Financial Trend Analyzer" << endl;
    cout << "Enter input for quick (q) or heap (h)" << endl;
    cin >> input;
    cout << "Enter input for top k elements (1-10)" << endl;
    cin >> k;

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
    hashMap map;
    vector<Record> totalRev;
    vector<Record> heapSelectResult;
    vector<Record> quickSelectResult;

    // loop through every data point
    for (int j = 0; j < 3000; j++) {
        getline(data22, line);
        Record newRecord;
        istringstream stream(line);

        // loop through each piece of data in each CSV entry
        for (int i = 0; i < 22; i++) {
            getline(stream, token,',');
            // cout << token << endl;
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

        // returns company and total revenue
        totalRev = map.getAllRecords();

        // call functions for heapselect and quickselect 
        // print out to the user the results 
        if (input == 'q'){
            // quickSelectResult = quickSelect(totalRev, k);
            // int counter = 0;
            // for (auto item : quickSelectResult){
            //     counter += 1;
            //     cout << counter << "Company Name:" << item.getName() << " Revenue: " << item.getRevenue() << endl;
            // }
            cout << "quick" << endl;
        } else if (input == 'h'){
            // heapSelectResult = heapSelect(totalRev, k);
            // int counter = 0;
            // for (auto item : heapSelectResult){
            //     counter += 1;
            //     cout << counter << "Company Name:" << item.getName() << " Revenue: " << item.getRevenue() << endl;
            // }
            cout << "heap" << endl;
        }

        return 0;

    }
