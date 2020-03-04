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
template<typename t>
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


template<typename t>
using First = vector<Terminal<t>>;
template<typename t>
using Follow = vector<Terminal<t>>;
template<typename t>
using Token = pair<Terminal<t>,string>;

template<typename t,typename x>
concept isSomething=is_same<t,NonTerminal<x>>::value || is_same<t,Terminal<x>>::value;

#endif
