#ifndef _OPERATOR_HPP_
#define _OPERATOR_HPP_ 1

#ifndef _TERMINAL_HPP_
#include<terminal.hpp>
#endif



template<typename T>
class Operator:Terminal<T>{
  enum class Type {
    UNIARY,
    BINARY,
    TERNARY
  };
  enum class UniaryType {
    LEFTUNIARY,
    RIGHTUNIARY
  };
  string name;
};




#endif
