#include "DataBase.h"

void DataBase::addSchemes(std::vector<Predicate*> mySchemes)
{
    for(unsigned int i = 0; i < mySchemes.size(); i++)
    {
      Relation* newRelation = new Relation();

      Predicate curScheme = *(mySchemes.at(i));

      newRelation->setScheme(curScheme.getName(), curScheme.getParams());
      myRelations.push_back(newRelation);
    }
}

void DataBase::addFacts(std::vector<Predicate*> myFacts)
{
    for(unsigned int i = 0; i < myFacts.size(); i++)
    {
      Predicate* curFact = myFacts.at(i);

      for(unsigned int j = 0; j < myRelations.size(); j++)
      {
        std::string relName = myRelations.at(j)->getName();
        if(relName == curFact->getName())
        {
          myRelations.at(j)->setTuple(curFact->getParams());
          break;
        }
      }
    }
}

std::string DataBase::checkQueries(std::vector<Predicate*> myQueries)
{
  std::string returnString = "";

  for(unsigned int i = 0; i < myQueries.size(); i++)
  {
    Predicate curQuery = *(myQueries.at(i));

    for(unsigned int j = 0; j < myRelations.size(); j++)
    {
      std::string relName = myRelations.at(j)->getName();
      if(relName == curQuery.getName())
      {
        returnString += curQuery.toString();
        //Evaluate Query
      }
    }
  }

  return returnString;
}

std::string DataBase::printDB()
{
  std::string returnString = "";
  for(unsigned int i = 0; i < myRelations.size(); ++i)
  {
      returnString += myRelations.at(i)->toString();
      returnString += "\n";
  }

  return returnString;
}
