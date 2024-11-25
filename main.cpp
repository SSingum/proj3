#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Record.h"
using namespace std;

int main(){

  ifstream data22("SalesData2022.csv");
  vector<Record> myRecords22;

  if(!data22.is_open()){
    cout << "sales data is not open!" << endl;
  }

  string line; 
  getline(data22, line);
  getline(data22, line);


  for(int i=0; i < 3000; i++){
    getline(data22, line);
    Record myRecord;
    istringstream stream(line);
    string token; 
    for(int i=0; i < 22; i++){
      getline(stream, token,',');
      cout << token << endl;
      if(i == 0){
        myRecord.monthSetter(stoi(token));
      } else if(i == 1){
        myRecord.idSetter(stoi(token));
      } else if(i == 2){
        if (token[0] == '"'){
          string remainder;
          if (token.back() != '"'){
            while(getline(stream, remainder, ',')){
                token += ',' + remainder;
                if(remainder.back() == '"'){
                  break;
                }
            }
          }

          token = token.substr(1, token.size()-2);
          myRecord.nameSetter(token);
        } else{
          myRecord.nameSetter(token);
        }
      } else if(i == 16){
        myRecord.typeSetter(token);
      } else if (i == 17){
        myRecord.componentSetter(token);
      } else if(i == 19){
        myRecord.volumeSetter(stoi(token));
      } else if(i == 21){
        string final;
        for (char x : token){
          if(isdigit(x) || x == '.' || x == '-'){
            final += x;
          }
        }

        myRecord.revenueSetter(stof(final));
      }
    }

    myRecords22.push_back(myRecord);
  }
  
  



  data22.close();
  return 0;
}