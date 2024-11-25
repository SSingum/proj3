#include <iostream>
#include <vector>
using namespace std;

class Record{
  private:
    int billMonth;
    int companyId;
    string companyName;
    string chargeType;
    string chargeComponent;
    int volume;
    float revenue;

  public:
    Record (){}
    Record(int month, int id, string name, string type, string component, int vol, float rev){
      billMonth = month;
      companyId = id;
      companyName = name;
      chargeType = type;
      chargeComponent = component;
      volume = volume;
      revenue = rev;
    }

    void monthSetter(int month);
    void idSetter(int id);
    void nameSetter(string name);
    void typeSetter(string type);
    void componentSetter(string component);
    void volumeSetter(int vol);
    void revenueSetter(float rev);



};