#ifndef _SYMBOL_TABLE_HPP_
#define _SYMBOL_TABLE_HPP_

#ifndef _TYPES_HPP_
#include <types.hpp>
#endif

class Class;
class Variable{
private:
  class Type{
    enum class TypeType{
      DEFAULT,
      USERDEFINED
    };
    enum class UserDefined{
      CLASS,
      STRUCTURE,

    };
    TypeType type;
    string name;
    bool arrayType;
    vector<int> arraySize{1,1};
    bool constant;
    bool pointer;
    Type* pointerType;
  public:
    TypeType getType() const{
      return type;
    }

    string getName()const{
      return name;
    }

    bool isArrayType()const{
      return arrayType;
    }

    vector<int> getArraySize()const{
      return arraySize;
    }

    bool isConstant()const{
      return constant;
    }


  };

  class Scope{
    string name;
    Scope* OutterScope;
  };

  Type t;
  string name;
  Scope scope;
  int lineNo;
  string fileName;

public:
  static vector<Variable> table;
};
class Function;
class SymbolOperator;


class SymbolTable{
    enum class Type{
        CLASS,
        FUNCTION,
        VARIABLE,
        UNION,
        INTERFACE
    };
    vector<pair<Type,string>> table;
    void insert();
};


#endif
