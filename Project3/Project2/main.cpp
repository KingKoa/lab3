#include "Scanner.h"
#include "DatalogProgram.h"
#include "Parser.h"
#include "Token.h"
#include "DataBase.h"

void sortDomain(std::vector<std::string*> *myDomain)
{
  unsigned int i, j;
  unsigned int size = myDomain->size();
  std::string t;
  std::vector<unsigned int> deleteThese;

  for(i=1; i<size; i++)
  {
    for(j=1; j<size; j++)
    {
      if(*myDomain->at(j-1) >= *myDomain->at(j))
      {
        t = *myDomain->at(j-1);
        *myDomain->at(j-1) = *myDomain->at(j);
        *myDomain->at(j) = t;
      }
    }
  }

  for (i = 1; i < size; ++i)
  {
    if(*myDomain->at(i-1) == *myDomain->at(i))
    {
      deleteThese.push_back(i);
    }
  }
  for (int k = (deleteThese.size() - 1); k >= 0; k--)
  {
    delete myDomain->at(deleteThese[k]);
    myDomain->erase(myDomain->begin() + deleteThese[k]);
  }
}


int main(int argc, char* argv[]) {
    std::string fileName = argv[1];
    std::vector<Token*> *myTokens;
    std::vector<Token*> *parseTokens = new std::vector<Token*>;

    Scanner myScanner(fileName);

    myTokens = myScanner.tokenize();

    for (unsigned int i = 0; i < myTokens->size(); i++)
    {
        if (myTokens->at(i) != nullptr && myTokens->at(i)->getTokenType() != COMMENT)
        {
            parseTokens->push_back(myTokens->at(i));
        }
    }

    Parser myParser(parseTokens);
    DatalogProgram* myProgram = myParser.getProg();
    sortDomain(myParser.getDomain());

    //print DP
    std::cout << myProgram->toStringFacts() << std::endl;


    //Create Database
    DataBase myDataBase;
    //
    // Input mySchemes
    std::cout << "Adding Schemes \n";
    myDataBase.addSchemes(myProgram->getSchemes());
    //Test relations
    std::cout << myDataBase.printDB() << std::endl;
    //Add Rules :X
    // Input myFacts
    std::cout << "Adding Facts \n";
    myDataBase.addFacts(myProgram->getFacts());
    //Test relations
    std::cout << "Testing Facts \n";
    std::cout << myDataBase.printDB() << std::endl;
    //Answer QUERIES
    std::cout << myDataBase.checkQueries(myProgram->getQueries());

    delete myProgram;

    for (unsigned int i = 0; i < myTokens->size(); i++)
    {
        delete myTokens->at(i);
    }

    delete myTokens;
    delete parseTokens;

    return 0;
}
