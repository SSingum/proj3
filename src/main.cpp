#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
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
    while (true) {
        // ANSI escape codes used for design from: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
        string input;
        int k = 0;
        string year;

        // design from: https://www.asciiart.eu/art-and-design/borders
        cout << "             ______________________________________________" << endl;
        cout << "            |  __________________________________________  |" << endl;
        cout << "            | |\033[42m                                          \033[0m| |" << endl;
        cout << "            | |\033[1;37;42m    Welcome to Financial Trend Analyzer   \033[0;22;24m| |" << endl;
        cout << "            | |\033[1;37;42m           by Gator Gas Company           \033[0;22;24m| |" << endl;
        cout << "            | |\033[42m__________________________________________\033[0m| |" << endl;
        cout << "            |______________________________________________|\n" << endl;

        // validate user input
        while (true) {
            cout << "                   " << "\033[3;4m" << "Select year 2022 (a) or 2023 (b):" << "\033[23;24m ";
            cin >> year;

            if (year == "a" || year == "b")
                break;
        }

        // design from: https://www.asciiart.eu/miscellaneous/hourglass
        cout << "\n                                 " << "+====+" << endl;
        cout << "                                 " << "|(::)|" << endl;
        cout << "                                 " << "| )( |" << endl;
        cout << "                                 " << "|(..)|" << endl;
        cout << "                                 " << "+====+" << endl;

        // validate user input
        while (true) {
            cout << "          " << "\033[3;4m" << "Enter input for quick select (q) or heap select (h):" << "\033[23;24m ";
            cin >> input;

            if (input == "h" || input == "q")
                break;
        }

        cout << "\n                                 " << "+====+" << endl;
        cout << "                                 " << "|(::)|" << endl;
        cout << "                                 " << "| )( |" << endl;
        cout << "                                 " << "|(..)|" << endl;
        cout << "                                 " << "+====+" << endl;

        // validate user input
        while(true){
            cout << "\n                 " << "\033[3;4m" << "Enter input for top k elements (>0): " << "\033[23;24m ";
            cin >> k;

            // if enter anything other than an int, clear it and continue
            // functionality from: https://www.geeksforgeeks.org/how-to-use-cin-fail-method-in-cpp/
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if(k >= 1){
                break;
            }
        }

        cout << "\n                                 " << "+====+" << endl;
        cout << "                                 " << "|(::)|" << endl;
        cout << "                                 " << "| )( |" << endl;
        cout << "                                 " << "|(..)|" << endl;
        cout << "                                 " << "+====+" << endl;


        ifstream data;

        // open data
        if (year == "a")
            data.open("data/SalesData2022.csv");
        else if (year == "b")
            data.open("data/SalesData2023.csv");
        else {
            cout << "Invalid data selection!";
            continue;
        }

        if (!data.is_open()) {
            // failsafe, adjusts depending on where parent directory is
            if (year == "a")
                data.open("../data/SalesData2022.csv");
            else if (year == "b")
                data.open("../data/SalesData2023.csv");
            else {
                cout << "Sales data is not open!" << endl;
                break;
            }
        }

        // clear template lines of the CSV
        string line; 
        getline(data, line);
        
        // initialize variables for loop
        string token; 
        string final;
        hashMap map;
        vector<Record> totalRev;
        vector<Record> heapSelectResult;
        vector<Record> quickSelectResult;

        int counter = 0;

        // loop through every line of data
        while (getline(data, line)) {
            Record newRecord;
            istringstream stream(line);

            // loop through each piece of data in each CSV entry
            for (int i = 0; i < 22; i++) {
                // get value
                getline(stream, token,',');
                string remainder = " ";
                // switch through possible data entries to assign it
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
                    case 17: { // assigns revenue component 
                        newRecord.setComponent(token);
                        break;
                    }
                    case 19: { // assigns volume of product bought 
                        newRecord.setVolume(stoi(token));
                        break;
                    }
                    case 21: { // assigns revenue amount
                        newRecord.setRevenue(stof(token));
                        break;
                    }
                    default: {
                        continue;
                    }
                }
            }

            map.update(newRecord);
        }

        data.close();

        // calculate a vector to unify data points under the same company names
        totalRev = map.getAllRecords();

        // print out to the user the results 
        cout << "\n                     _______________________________" << endl;
        cout << "                    |  ___________________________  |" << endl;
        cout << "                    | |\033[42m                           \033[0m| |" << endl;
        cout << "                    | |\033[1;37;42m    Companies Revenue:     \033[0;22;24m| |" << endl;
        cout << "                    | |\033[42m___________________________\033[0m| |" << endl;
        cout << "                    |_______________________________|\n" << endl;

        // call selection algorithms
        if (input == "q") { // quickSelect
            quickSelectResult = quickSelect(totalRev, k);
            int counter = 0;
            for (int i = 0; i < quickSelectResult.size(); i++) {
                counter += 1;
                cout << "\033[3m" << counter << ") Company Name: " << quickSelectResult[i].getName() << " Revenue: " << "$" << fixed << setprecision(2) << quickSelectResult[i].getRevenue() << "\033[23m" << endl;
            }
        }
        else if (input == "h") { // heapSelect
            heapSelectResult = heapSelect(totalRev, k);
            int counter = 0;
            for (int i = 0; i < heapSelectResult.size(); i++) {
                counter += 1;
                cout << "\033[3m" << counter << ") Company Name: " << heapSelectResult[i].getName() << " Revenue: " << "$" << fixed << setprecision(2) << heapSelectResult[i].getRevenue() << "\033[23m" << endl;
            }
        }

        char exit;

        // check if user wants to exit program
        cout << "\n            " << "\033[3;4m" << "Enter (y) if you wish to repeat the program:" << "\033[23;24m ";
        cin >> exit;

        if (exit == 'y')
            continue;
        else
            break;
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

    cout << "\n            " << "\033[3;4m" << "Thank you for using the financial trend analyzer!" << "\033[23;24m ";
    cout << endl << endl;

    return 0;
}
