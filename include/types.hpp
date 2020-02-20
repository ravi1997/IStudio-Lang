#ifndef _TYPES_HPP_
#define _TYPES_HPP_

#include<string>
#include<regex>
#include<fstream>
#include<vector>
#include<string>
#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <sstream>
#include <iomanip> // put_time
#include<regex>
#include<variant>
using namespace std;

class Options;
class Terminal;
template<typename t>
class NonTerminal;
template<typename t>
class Rule;
template<typename t>
class Rules;
template<typename t>
class Grammar;
template<typename t>
class Parser;


using First = vector<Terminal>;
using Follow = vector<Terminal>;
using Token = pair<Terminal,string>;

template<typename t,typename x>
concept isSomething=is_same<t,NonTerminal<x>>::value || is_same<t,Terminal>::value;

#endif
