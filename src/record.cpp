#include "record.h"

// constructors
Record::Record() {}
Record::Record(int month, int ID, const string& name, const string& type, const string& component, int vol, float rev) 
: billMonth(month), companyID(ID), companyName(name), chargeType(type), chargeComponent(component), volume(vol), revenue(rev) {}

// setters
void Record::setMonth(int month) { billMonth = month; }
void Record::setID(int ID) { companyID = ID; }
void Record::setName(string name) { companyName = name; }
void Record::setType(string type) { chargeType = type; }
void Record::setComponent(string component) { chargeComponent = component; }
void Record::setVolume(int vol) { volume = vol; }
void Record::setRevenue(float rev) { revenue = rev; }

// getters
int Record::getMonth() { return this->billMonth; }
int Record::getID() { return this->companyID; }
string Record::getName() { return this->companyName; }
string Record::getType() { return this->chargeType; }
string Record::getComponent() { return this->chargeComponent; }
int Record::getVolume() { return this->volume; }
float Record::getRevenue() { return this->revenue; }

// operators
bool Record::operator==(Record& other) { return (this->revenue == other.revenue); }
bool Record::operator!=(Record& other) { return !(*this == other); }
bool Record::operator>(Record& other) { return (this->revenue > other.revenue); }
bool Record::operator<(Record& other) { return (this->revenue < other.revenue); }
bool Record::operator>=(Record& other) { return (*this > other || *this == other); }
bool Record::operator<=(Record& other) { return (*this < other || *this == other); }
Record::operator float() const { return revenue; } 
