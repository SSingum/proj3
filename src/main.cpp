#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
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
    // design from: https://www.asciiart.eu/miscellaneous/money
    cout << "\n\033[42m||====================================================================||\033[0m" << endl;
    cout << "\033[42m||//$\\\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\//$\\\\||\033[0m" << endl;
    cout << "\033[42m||(100)==================| FEDERAL RESERVE NOTE |================(100)||\033[0m" << endl;
    cout << "\033[42m||\\\\$//        ~         '------========--------'                \\\\$//||\033[0m" << endl;
    cout << "\033[42m||<< /        /$\\              // ____ \\\\                         \\ >>||\033[0m" << endl;
    cout << "\033[42m||>>|  12    //L\\\\            // ///..) \\\\         L38036133B   12 |<<||\033[0m" << endl;
    cout << "\033[42m||<<|        \\\\ //           || <||  >\\  ||                        |>>||\033[0m" << endl;
    cout << "\033[42m||>>|         \\$/            ||  $$ --/  ||        One Hundred     |<<||\033[0m" << endl;
    cout << "\033[42m||<<|      L38036133B        *\\\\  |\\_/  //* series                 |>>||\033[0m" << endl;
    cout << "\033[42m||>>|  12                     *\\\\/___\\_//*   1989                  |<<||\033[0m" << endl;
    cout << "\033[42m||<<\\      Treasurer     ______/Franklin\\________     Secretary 12 />>||\033[0m" << endl;
    cout << "\033[42m||//$\\\\                 ~|UNITED STATES OF AMERICA|~             //$\\\\||\033[0m" << endl;
    cout << "\033[42m||(100)===================  ONE HUNDRED DOLLARS =================(100)||\033[0m" << endl;
    cout << "\033[42m||\\\\$//\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\///$\\\\||\033[0m" << endl;
    cout << "\033[42m||====================================================================||\033[0m" << endl;

    // loop through program till user exits
    while(true){
        // ANSI escape codes used for design from: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
        char input;
        int k = 0;
        char year;

        // design from: https://www.asciiart.eu/art-and-design/borders
        cout << "             ______________________________________________" << endl;
        cout << "            |  __________________________________________  |" << endl;
        cout << "            | |\033[42m                                          \033[0m| |" << endl;
        cout << "            | |\033[1;37;42m    Welcome to Financial Trend Analyzer   \033[0;22;24m| |" << endl;
        cout << "            | |\033[1;37;42m           by Gator Gas Company           \033[0;22;24m| |" << endl;
        cout << "            | |\033[42m__________________________________________\033[0m| |" << endl;
        cout << "            ı|______________________________________________|\n" << endl;

        // validate user input
        while(true){
            cout << "                   " << "\033[3;4m" << "Select year 2022 (a) or 2023 (b):" << "\033[23;24m ";
            cin >> year;

            if(year == 'a' || year == 'b'){
                break;
            }
        }

        // design from: https://www.asciiart.eu/miscellaneous/hourglass
        cout << "\n                                 " << "+====+" << endl;
        cout << "                                 " << "|(::)|" << endl;
        cout << "                                 " << "| )( |" << endl;
        cout << "                                 " << "|(..)|" << endl;
        cout << "                                 " << "+====+" << endl;

        // validate user input
        while(true){
            cout << "          " << "\033[3;4m" << "Enter input for quick select (q) or heap select (h):" << "\033[23;24m ";
            cin >> input;

            if(input == 'h' || input == 'q'){
                break;
            }
        }

        cout << "\n                                 " << "+====+" << endl;
        cout << "                                 " << "|(::)|" << endl;
        cout << "                                 " << "| )( |" << endl;
        cout << "                                 " << "|(..)|" << endl;
        cout << "                                 " << "+====+" << endl;

        // validate user input
        while(true){
            cout << "\n                 " << "\033[3;4m" << "Enter input for top k elements (1-10): " << "\033[23;24m ";
            cin >> k;

            // if enter anything other than an int, clear it and continue
            // functionality from: https://www.geeksforgeeks.org/how-to-use-cin-fail-method-in-cpp/
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if(k >= 1 && k <= 10){
                break;
            }
        }

        cout << "\n                                 " << "+====+" << endl;
        cout << "                                 " << "|(::)|" << endl;
        cout << "                                 " << "| )( |" << endl;
        cout << "                                 " << "|(..)|" << endl;
        cout << "                                 " << "+====+" << endl;

        if(year == 'a'){
            // open CSV file
            ifstream data22("src/SalesData2022.csv");
            vector<Record> records2022;

            if (!data22.is_open()){
                cout << "Sales data is not open!" << endl;
            }

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
                    map.update(newRecord);
                }

            data22.close();

            // returns company and total revenue
            totalRev = map.getAllRecords();
            // totalRev = records2022;

            // call functions for heapselect and quickselect 
            // print out to the user the results 
            cout << "\n                     _______________________________" << endl;
            cout << "                    |  ___________________________  |" << endl;
            cout << "                    | |\033[42m                           \033[0m| |" << endl;
            cout << "                    | |\033[1;37;42m    Companies Revenue:     \033[0;22;24m| |" << endl;
            cout << "                    | |\033[42m___________________________\033[0m| |" << endl;
            cout << "                    |_______________________________|\n" << endl;

            if (input == 'q'){
                quickSelectResult = quickSelect(totalRev, k);
                int counter = 0;
                for (auto item : quickSelectResult){
                    counter += 1;
                    cout << "\033[3m" << counter << ") Company Name: " << item.getName() << " Revenue: " << "$" << fixed << setprecision(2) << item.getRevenue() << "\033[23m" << endl;
                }
            } else if (input == 'h'){
                heapSelectResult = heapSelect(totalRev, k);
                int counter = 0;
                for (auto item : heapSelectResult){
                    counter += 1;
                    cout << "\033[3m" << counter << ") Company Name: " << item.getName() << " Revenue: " << "$" << fixed << setprecision(2) << item.getRevenue() << "\033[23m" << endl;
                }
            }
        }
        else{
            // open CSV file
            ifstream data23("src/SalesData2023.csv");
            vector<Record> records2023;

            if (!data23.is_open()){
                cout << "Sales data is not open!" << endl;
            }

            // clear template lines of the CSV
            string line; 
            getline(data23, line);
            
            // initialize variables for loop
            string token; 
            string final;
            hashMap map;
            vector<Record> totalRev;
            vector<Record> heapSelectResult;
            vector<Record> quickSelectResult;

            // loop through every data point
            for (int j = 0; j < 100000; j++) {
                getline(data23, line);
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

                records2023.push_back(newRecord);
                map.update(newRecord);
            }

            data23.close();

            // returns company and total revenue
            totalRev = map.getAllRecords();
            // totalRev = records2022;

            // call functions for heapselect and quickselect 
            // print out to the user the results 
            cout << "\n                     _______________________________" << endl;
            cout << "                    |  ___________________________  |" << endl;
            cout << "                    | |\033[42m                           \033[0m| |" << endl;
            cout << "                    | |\033[1;37;42m    Companies Revenue:     \033[0;22;24m| |" << endl;
            cout << "                    | |\033[42m___________________________\033[0m| |" << endl;
            cout << "                    |_______________________________|\n" << endl;

            if (input == 'q'){
                quickSelectResult = quickSelect(totalRev, k);
                int counter = 0;
                for (auto item : quickSelectResult){
                    counter += 1;
                    cout << "\033[3m" << counter << ") Company Name: " << item.getName() << " Revenue: " << "$" << fixed << setprecision(2) << item.getRevenue() << "\033[23m" << endl;
                }
            } else if (input == 'h'){
                heapSelectResult = heapSelect(totalRev, k);
                int counter = 0;
                for (auto item : heapSelectResult){
                    counter += 1;
                    cout << "\033[3m" << counter << ") Company Name: " << item.getName() << " Revenue: " << "$" << fixed << setprecision(2) << item.getRevenue() << "\033[23m" << endl;
                }
            }
        }

        char exit;

        // check is user wants to exit program
        cout << "\n            " << "\033[3;4m" << "Enter yes (y) if you wish to exit the program:" << "\033[23;24m ";
        cin >> exit;

        if(exit == 'y'){
            break;
        }

    }

    // design from: https://www.asciiart.eu/miscellaneous/money
    cout << "\n   \033[42m||====================================================================||\033[0m" << endl;
    cout << "   \033[42m||//$\\\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\//\\///$\\\\||\033[0m" << endl;
    cout << "   \033[42m||(100)==================| FEDERAL RESERVE NOTE |================(100)||\033[0m" << endl;
    cout << "   \033[42m||\\\\$//        ~         '------========--------'                \\\\$//||\033[0m" << endl;
    cout << "   \033[42m||<< /        /$\\              // ____ \\\\                         \\ >>||\033[0m" << endl;
    cout << "   \033[42m||>>|  12    //L\\\\            // ///..) \\\\         L38036133B   12 |<<||\033[0m" << endl;
    cout << "   \033[42m||<<|        \\\\ //           || <||  >\\  ||                        |>>||\033[0m" << endl;
    cout << "   \033[42m||>>|         \\$/            ||  $$ --/  ||        One Hundred     |<<||\033[0m" << endl;
    cout << "\033[42m||====================================================================||>||\033[0m" << endl;
    cout << "\033[42m||//$\\\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\//$\\\\||<||\033[0m" << endl;
    cout << "\033[42m||(100)==================| FEDERAL RESERVE NOTE |================(100)||>||\033[0m" << endl;
    cout << "\033[42m||\\\\$//        ~         '------========--------'                \\\\$//||\\||\033[0m" << endl;
    cout << "\033[42m||<< /        /$\\              // ____ \\\\                         \\ >>||)||\033[0m" << endl;
    cout << "\033[42m||>>|  12    //L\\\\            // ///..) \\\\         L38036133B   12 |<<||/||\033[0m" << endl;
    cout << "\033[42m||<<|        \\\\ //           || <||  >\\  ||                        |>>||=||\033[0m" << endl;
    cout << "\033[42m||>>|         \\$/            ||  $$ --/  ||        One Hundred     |<<||\033[0m" << endl;
    cout << "\033[42m||<<|      L38036133B        *\\\\  |\\_/  //* series                 |>>||\033[0m" << endl;
    cout << "\033[42m||>>|  12                     *\\\\/___\\_//*   1989                  |<<||\033[0m" << endl;
    cout << "\033[42m||<<\\      Treasurer     ______/Franklin\\________     Secretary 12 />>||\033[0m" << endl;
    cout << "\033[42m||//$\\                 ~|UNITED STATES OF AMERICA|~               /$\\\\||\033[0m" << endl;
    cout << "\033[42m||(100)===================  ONE HUNDRED DOLLARS =================(100)||\033[0m" << endl;
    cout << "\033[42m||\\\\$//\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\///$\\\\||\033[0m" << endl;
    cout << "\033[42m||====================================================================||\033[0m\n" << endl;

    return 0;

}
