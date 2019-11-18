#ifndef RELATION_H
#define RELATION_H

#include <vector>
#include <string>
#include <set>
#include "Scheme.h"
#include "Tuple.h"
#include <iostream>

class Relation {
public:
    Relation() {}
    Scheme getScheme() { return myScheme; }
    std::string getName() { return myScheme.getName(); }
    void setScheme(std::string newName, std::vector<std::string*> *newAttributes);
    void setTuple(std::vector<std::string*> *tupData) { myTuples.insert(new Tuple(tupData)); }
    Relation* selct(std::vector<std::string*> *parmList);
    Relation* selectMatching(std::vector<std::string*> *parmList);
    Relation* project(std::vector<std::string*> *parmList);
    Relation* rename(std::vector<std::string*> *parmList);
    std::string toString()
    {
      std::string returnString = "Relation:\n";
      returnString += "  ";
      returnString += myScheme.toString();
      std::set<Tuple*>::iterator it;
      std::cout << "Before Loop\n";
      for( it = myTuples.begin(); it!=myTuples.end(); ++it)
      {
        std::cout << "In Loop\n";
        std::string blah = (*it)->toString();
        returnString += blah;
      }
      std::cout << "After Loop\n";

      return returnString;
    }
private:
    Scheme myScheme;
    std::set<Tuple*> myTuples;

};

#endif //RELATION_H
