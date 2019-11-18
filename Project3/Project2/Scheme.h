#ifndef SCHEME_H
#define SCHEME_H

#include <vector>
#include <string>
#include "Predicate.h"

class Scheme {
public:
    Scheme() { schemeName = ""; schemeAttributes = NULL; }
    std::string getName() { return schemeName; }
    void setName(std::string newName) { schemeName = newName; }
    std::vector<std::string*> *getAttributes() { return schemeAttributes; }
    void setAttributes(std::vector<std::string*> *newAttributes) { schemeAttributes = newAttributes; }
    void addAttribute(std::string *newAttribute) { schemeAttributes->push_back(newAttribute); }
    std::string toString()
    {
      std::string returnString = schemeName;
      returnString += "( ";
      for (unsigned int i = 0; i < schemeAttributes->size(); i++)
      {
        returnString += *schemeAttributes->at(i);
        returnString += " ";
      }

      returnString += ")";
      return returnString;
    }

private:
    std::string schemeName;
    std::vector<std::string*> *schemeAttributes;

};

#endif //SCHEME_H
