#include "hashmap.h"
#include "record.h"

hashMap::hashMap(){
  map = vector<Record*>(1000001, nullptr);
}

void hashMap::update(Record updateRecord){
  if(map[updateRecord.getID()] == nullptr){
    map[updateRecord.getID()] == new Record(updateRecord.getID(), updateRecord.getName(), updateRecord.getRevenue());
  } else {
    map[updateRecord.getID()]->setRevenue(map[updateRecord.getID()]->getRevenue() + updateRecord.getRevenue()); 
  }
}

Record *hashMap::get(int key){
  return map[key];
}

vector<Record> hashMap::getAllRecords(){
  vector<Record> records;
  for (auto record : map){
    if (record != nullptr){
      records.push_back(*record);
    }
  }
  return records;
}

hashMap::~hashMap(){
  for (auto record : map) {
      delete record;
  }
}
