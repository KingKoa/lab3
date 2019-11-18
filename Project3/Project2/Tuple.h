#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>
#include "Predicate.h"

class Tuple {
public:
    Tuple() { tupData = NULL; }
    Tuple(std::vector<std::string*> *newData) { tupData = newData; }
    void addTuple(std::vector<std::string*> *newData) { tupData = newData; }
    std::string toString()
    {
      std::string returnString = "( ";

      for(unsigned int i = 0; i < tupData->size(); i++)
      {
        returnString += *tupData->at(i);
        returnString += " ";
      }

      returnString += ")";

      return returnString;
    }

private:
  std::vector<std::string*> *tupData;

};

#endif //TUPLE_H
