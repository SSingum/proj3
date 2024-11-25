#include "Record.h"

void Record::monthSetter(int month){
    billMonth = month;
    cout << " month: " << billMonth << endl;
  }

  void Record::idSetter(int id){
    companyId = id;
    cout << " id: " << companyId << endl;

  }

  void Record::nameSetter(string name){
    companyName = name;
    cout << " name: " << companyName << endl;

  }

  void Record::typeSetter(string type){
    chargeType = type;
    cout << " type: " << chargeType << endl;

  }

  void Record::componentSetter(string component){
    chargeComponent = component;
    cout << " component: " << chargeComponent << endl;

  }

  void Record::volumeSetter(int vol){
    volume = vol;
    cout << " volume: " << volume << endl;

  }

  void Record::revenueSetter(float rev){
    revenue = rev;
        cout << " revenue: " << revenue << endl;

  }
