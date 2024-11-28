#include <iostream>
#include <vector>

using namespace std;


class Record {
    private:
        int billMonth;
        int companyID;
        string companyName;
        string chargeType;
        string chargeComponent;
        int volume;
        float revenue;

    public:
        // constructors
        Record ();
        Record(int month, int ID, const string& name, const string& type, const string& component, int vol, float rev);
        // setters
        void setMonth(int month);
        void setID(int ID);
        void setName(string name);
        void setType(string type);
        void setComponent(string component);
        void setVolume(int vol);
        void setRevenue(float rev);
        // getters
        int getMonth();
        int getID();
        string getName();
        string getType();
        string getComponent();
        int getVolume();
        float getRevenue();
        // overloaded operators
        bool operator==(Record& other);
        bool operator!=(Record& other);
        bool operator>(Record& other);
        bool operator<(Record& other);
        bool operator>=(Record& other);
        bool operator<=(Record& other);
};
