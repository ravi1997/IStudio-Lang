#ifndef _SYMBOL_TABLE_HPP_
#define _SYMBOL_TABLE_HPP_

#ifndef _TYPES_HPP_
#include <types.hpp>
#endif

class Scope{
public:
  enum class ScopeType{
    FUNCTIONSCOPE,
    LOCALSCOPE,
    GLOBALSCOPE,
    CLASSSCOPE,
    NAMESPACESCOPE,
    FILESCOPE
  };


  void setName       (string s){
    name=s;
  }
  void setOutterScope(Scope* s){
    outterScope=s;
  }

  string getName()       const{
    return name;
  }
  Scope& getOutterScope()const{
    return *outterScope;
  }

  bool operator==(const Scope s)const{
    if (name==s.getName()){
      if(outterScope!=nullptr && s.outterScope!=nullptr)
        return getOutterScope()==s.getOutterScope();
      else if(outterScope==nullptr && s.outterScope==nullptr)
        return true;
      else
        return false;
    }
    return false;
  }
  bool operator!=(const Scope s)const{
    return !(*this==s);
  }
private:
  string name="";
  Scope* outterScope=nullptr;
};


class SymbolTableEntry{
public:
  enum class Type{
        DEFAULT,
        CLASS,
        FUNCTION,
        VARIABLE,
        UNION,
        METACLASS,
        SCOPE
    };
  void setName      (const string s){
    name=s;
  }
  void setScope     (const Scope s){
    scope=s;
  }
  void setFileName  (const string s){
    fileName=s;
  }
  void setLineNumber(const unsigned long int s){
    lineNumber=s;
  }
  void setType      (const Type t){
    type=t;
  }


  string            getName()const{
    return name;
  }
  Scope             getScope()const{
    return scope;
  }
  string            getFileName()const{
    return fileName;
  }
  unsigned long int getLineNumber()const{
    return lineNumber;
  }
  Type              getType()const{
    return type;
  }



  bool operator==(const SymbolTableEntry ste)const{
    return ((name==ste.getName()) &&
            (scope==ste.getScope()) &&
            (fileName==ste.getFileName()) &&
            (lineNumber==ste.getLineNumber()) &&
            (type==ste.getType())
           );
  }
  bool operator!=(const SymbolTableEntry ste)const{
    return !(*this==ste);
  }


private:
  string name="";
  Scope scope;
  string fileName="";
  unsigned long int lineNumber=1;
  Type type=Type::DEFAULT;
};

class Variable:public SymbolTableEntry{

  void setScope        (const Scope vs){
    scope=vs;
  }
  void setDataType     (const string s){
    dataType=s;
  }
  void setConstant     (const bool b){
    constant=b;
  }
  void setStatic       (const bool b){
    Static=b;
  }
  void setMutable      (const bool b){
    Mutable=b;
  }
  void setVolatile     (const bool b){
    Volatile=b;
  }


  Scope         getScope()        const{
    return scope;
  }
  string        getDataType()     const{
    return dataType;
  }
  bool          getConstant()     const{
    return constant;
  }
  bool          getStatic()       const{
    return Static;
  }
  bool          getMutable()      const{
    return Mutable;
  }
  bool          getVolatile()     const{
    return Volatile;
  }


  bool operator==(const Variable v)const{
    return ((dataType     == v.getDataType())      &&
            (scope        == v.getScope())         &&
            (constant     == v.getConstant())      &&
            (Static       == v.getStatic())        &&
            (Mutable      == v.getMutable())       &&
            (Volatile     == v.getVolatile())
           );
  }
  bool operator!=(const Variable v)const{
    return !(*this==v);
  }

  private:
    string dataType="";
    Scope scope;
    bool constant=false;
    bool Static=false;
    bool Mutable=false;
    bool Volatile=false;
    unsigned long int lastUpdated=0;
    string lastUpdatedFile="";
};

class DataMembers{};



class SymbolTable{
    vector<SymbolTableEntry> table;
    void insert();
};


#endif
