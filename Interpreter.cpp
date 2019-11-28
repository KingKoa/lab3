#include "Interpreter.h"
bool isConstant(std::string checkThis)
{
  if (checkThis.at(0) == '\'' && checkThis.at((checkThis.size() - 1)) == '\'')
  {
    return true;
  }

  return false;
}
std::string Interpreter::checkQueries(std::vector<Predicate*> myQueries)
{
  std::string returnString = "";

  for(unsigned int i = 0; i < myQueries.size(); i++)
  {
    Predicate curQuery = *(myQueries.at(i));

    for(unsigned int j = 0; j < myDataBase.getRelations().size(); j++)
    {
      std::string relName = myDataBase.getRelations().at(j)->getName();
      if(relName == curQuery.getName())
      {
        Relation thisRelation = *(myDataBase.getRelations().at(j));
        returnString += curQuery.toString();
        returnString += "? ";
        //Evaluate Query
          //Grab the realtion from DB *That's what curQuery is*
          std::vector<std::string*> curParams = *(curQuery.getParams());
          std::map<std::string, unsigned int> firstTimer;
          //std::map<std::string, unsigned int> dupVars;
          std::vector<std::string> dupVars;
          // Go through Params
          //Check each
          for(unsigned int k = 0; k < curParams.size(); ++k)
          {
            if(isConstant(*(curParams.at(k))))
            {
              //if const do a select
              //returnString += "it's a const \n";
              thisRelation = *(thisRelation.select(*(curParams.at(k)), *(thisRelation.getAttributesAt(k))));
              //thisRelation = *(thisRelation.select(*(curParams.at(k)), *(myDataBase.getRelations().at(j)->getAttributes()->at(k))));
            }

            else
            {
              if(firstTimer.insert(std::pair<std::string, unsigned int>(*(curParams.at(k)), k)).second)
              {
                firstTimer.insert(std::pair<std::string, unsigned int>(*(curParams.at(k)), k));
              }

              else
              {
                thisRelation = *(thisRelation.selectMatching(*(thisRelation.getAttributesAt(k)), *(thisRelation.getAttributesAt(firstTimer.find(*(curParams.at(k)))->second))));
              }
            }
          }
          //Do a project
          std::map<std::string, unsigned int>::iterator it = firstTimer.begin();
          std::vector<unsigned int> useThese;
          std::vector<std::string> renameThese;
          while(it != firstTimer.end())
          {
            renameThese.push_back(it->first);
            useThese.push_back(it->second);
            ++it;
          }

          thisRelation = *(thisRelation.project(useThese));

          //Do a rename
          thisRelation = *(thisRelation.rename(renameThese));
        //Check size of query answer aka num tuples ( retuned as relation )
        // if not put Yes(num Tuples)
        // then print the returned relation
        if (thisRelation.getTuple().size() != 0)
        {
          returnString += "Yes(";
          returnString += std::to_string(thisRelation.getTuple().size());
          returnString += ")\n";
          returnString += thisRelation.toString();
        }
        // if 0 out put No
        else
        {
          returnString += "No\n";
        }
      }
    }
  }

  return returnString;
}

/*
for (e = k + 1; e < curParams.size(); ++e)
{
  if(*(curParams.at(k)) == *(curParams.at(e)))
  {
    //if duplicate variables do a selectMatching
    //returnString += "it's a dup\n";
    thisRelation = *(thisRelation.selectMatching(*(thisRelation.getAttributesAt(k)), *(thisRelation.getAttributesAt(e))));
    isDup = true;
    dupVars.push_back(*(curParams.at(k)));
  }
}

if (!isDup)
{
  //returnString += "it's a non dup var \n";
  //Mark a variable as a column and an attribute you want to keep if it's the first time you've seen the variable
    //Use a map<string int> to represent the variable and the index you found it??
  if(k + 1 != curParams.size()) { firstTimer.insert(std::pair<std::string, unsigned int>(*(curParams.at(k)), k)); }
  else
  {
    isDup = false;

    for (e = 0; e < dupVars.size(); ++e)
    {
      if(dupVars.at(e) == *(curParams.at(k)))
      {
        isDup = true;
        break;
      }
    }

    if (!isDup) { firstTimer.insert(std::pair<std::string, unsigned int>(*(curParams.at(k)), k)); }
  }
  */
