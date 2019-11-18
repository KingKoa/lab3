#include "Relations.h"

void Relation::setScheme(std::string newName, std::vector<std::string*> *newAttributes)
{
  myScheme.setName(newName);
  myScheme.setAttributes(newAttributes);
}

Relation* Relation::selct(std::vector<std::string*> *parmList)
{
  return new Relation();
}

Relation* Relation::selectMatching(std::vector<std::string*> *parmList)
{
  return new Relation();
}

Relation* Relation::project(std::vector<std::string*> *parmList)
{
  return new Relation();
}

Relation* Relation::rename(std::vector<std::string*> *parmList)
{
  return new Relation();
}
