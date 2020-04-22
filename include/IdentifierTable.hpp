#ifndef _IDENTIFIER_TABLE_HPP_
#define _IDENTIFIER_TABLE_HPP_ 1

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif

#ifndef _SYMBOL_TABLE_HPP_
#include<symbolTable.hpp>
#endif

class IdentifierTableEntry{
public:
  void setName(string s){
    name=s;
  }
  void setLineNumber(unsigned long int s){
    lineNumber=s;
  }
  void setFileName(string s){
    fileName=s;
  }
  void setKnown(bool b){
    known=b;
  }

  string getName()const{
    return name;
  }
  unsigned long int getLineNumber()const{
    return lineNumber;
  }
  string getFileName()const{
    return fileName;
  }
  bool getKnown()const{
    return known;
  }

private:
  string name="";
  unsigned long int lineNumber=1;
  string fileName="";
  bool known=false;
  Scope scope;
};

class IdentifierTable{
private:
  vector<IdentifierTableEntry> table;
};

#endif
