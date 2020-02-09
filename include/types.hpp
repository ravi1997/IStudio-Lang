#ifndef _TYPES_HPP_
#define _TYPES_HPP_

#include<string>
#include<regex>
#include<fstream>
#include<vector>
#include<string>
#include<regex>
using namespace std;

class Terminal;
class NonTerminal;
class Rule;
class Rules;
class Grammar;
class Parser;

typedef vector<Terminal> First;
template<typename t>
concept isSomething=is_same<t,NonTerminal>::value || is_same<t,Terminal>::value;

#endif
