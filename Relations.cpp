#include "Relations.h"
/*
Relation::Relation(const Relation &copyCat)
{
  this->addScheme(copyCat.getScheme());
  std::set<Tuple> otherTups = copyCat.getTuple();

  std::set<Tuple>::iterator it = otherTups.begin();

  while (it != otherTups.end())
  {
    this->addTuple(*it);
    it++;
  }

}
*/
void Relation::setScheme(std::string newName, std::vector<std::string*> *newAttributes)
{
  myScheme.setName(newName);
  myScheme.setAttributes(newAttributes);
}

void Relation::setTuple(std::vector<std::string*> *tupData)
{
  Tuple newTup;
  for (unsigned int i = 0; i < tupData->size(); ++i)
  {
    newTup.push_back(*(tupData->at(i)));
  }

  if(myTuples.insert(newTup).second)
  {
    myTuples.insert(newTup);
  }
}

void Relation::addTuple(Tuple newTuple)
{
  if(myTuples.insert(newTuple).second)
  {
    myTuples.insert(newTuple);
  }
}


Relation* Relation::select(std::string selectThis, std::string thisCol)
{
  unsigned int i;
  Relation* newRelation = new Relation();
  newRelation->setScheme(myScheme);

  for (i = 0; i < myScheme.getAttributes()->size(); ++i)
  {
    if (thisCol == *(myScheme.getAttributes()->at(i))) { break; }
  }

  std::set<Tuple>::iterator it = myTuples.begin();

  while (it != myTuples.end())
  {
    if (selectThis == (*it).at(i))
    {
      newRelation->addTuple(*it);
    }

    it++;
  }

  return newRelation;
}

Relation* Relation::selectMatching(std::string opOne, std::string opTwo)
{
  unsigned int i;
  unsigned int j;
  Relation* newRelation = new Relation();
  newRelation->setScheme(myScheme);

  for (i = 0; i < myScheme.getAttributes()->size(); ++i)
  {
    if (opOne == *(myScheme.getAttributes()->at(i))) { break; }
  }

  for (j = 0; j < myScheme.getAttributes()->size(); ++j)
  {
    if (opTwo == *(myScheme.getAttributes()->at(j))) { break; }
  }

  std::set<Tuple>::iterator it = myTuples.begin();

  while (it != myTuples.end())
  {
    if ((*it).at(j) == (*it).at(i))
    {
      newRelation->addTuple(*it);
    }

    it++;
  }

  return newRelation;
}

Relation* Relation::project(std::vector<unsigned int> parmList)
{
  unsigned int i = 0;
  unsigned int j;
  Relation* newRelation = new Relation();

  for (j = myScheme.getAttributes()->size(); j > 0; --j)
  {
    for(i = parmList.size(); i > 0; --i)
    {
      if(j-1 == parmList.at(i-1))
      {
        newRelation->addAttribute(myScheme.getAttributesAt(j-1));
      }
    }
  }

  std::set<Tuple>::iterator it = myTuples.begin();
  while (it != myTuples.end())
  {
    Tuple myTuple;

    for (i = parmList.size(); i > 0; --i)
    {
      myTuple.push_back(it->at(parmList.at(i-1)));
    }

    newRelation->addTuple(myTuple);
    it++;
  }

  return newRelation;
}

Relation* Relation::rename(std::vector<std::string> parmList)
{
  unsigned int i;
  Relation* newRelation = new Relation();

  for(i = parmList.size(); i > 0; --i)
  {
    newRelation->addAttribute(new std::string(parmList.at(i - 1)));
  }

  std::set<Tuple>::iterator it = myTuples.begin();
  while (it != myTuples.end())
  {
    newRelation->addTuple(*it);
    it++;
  }

  return newRelation;
}

std::string Relation::toString()
{
    std::string returnString = "";
//  returnString += "Relation:\n";
//  returnString += "  ";
//  returnString += myScheme.toString();
//  returnString += "\n";

  std::set<Tuple>::iterator it = myTuples.begin();

  while (it != myTuples.end())
  {
    if(myScheme.getAttributes()->size() != 0) { returnString += "  "; }

    for (unsigned int i = 0; i < myScheme.getAttributes()->size(); ++i)
    {
      returnString += *(myScheme.getAttributesAt(i));
      returnString += "=";
      returnString += (*it).at(i);

      if (i+1 != myScheme.getAttributes()->size())
      {
        returnString += ", ";
      }
    }

    it++;
    if(myScheme.getAttributes()->size() != 0) { returnString += "\n"; }
    //if (it != myTuples.end()) { returnString += "\n"; }
  }

  //returnString += "\n";
  return returnString;
}

/*
std::vector<std::string*> *myAttributes = myScheme.getAttributes();
for (unsigned int i = 0; i < parmList->size(); ++i)
{
  for (unsigned int j = 0; j < myAttributes->size(); ++j)
  {
    if (*(parmList->at(i)) == *(myAttributes->at(j))) break;
  }
}

int searching;

if ((i - 1) < 0) { searching = 1; }
else { searching = 0; }
*/
