#ifndef _TYPES_HPP_
#define _TYPES_HPP_ 1

#include <chrono>  // chrono::system_clock
#include <concepts>
#include <ctime>   // localtime
#include <functional>
#include <fstream>
#include <iostream>
#include <memory>
#include <regex>
//#include <sstream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>
#include <iomanip> // put_time


using namespace std;


// forward declarations

template<typename t>class Terminal;
template<typename t>class NonTerminal;
template<typename t>class Parser;
template<typename t>class Rule;
template<typename t>class Rules;
class Logger;


// Utilities

template<typename t>
using First=vector<Terminal<t>>;

template<typename t>
using Follow=vector<Terminal<t>>;

template<typename t,typename x>
concept isRightAssociate=is_same<t,NonTerminal<x>>::value || is_same<t,Terminal<x>>::value;

// Exceptions List
class ActionNotSet{};
class GrammarNotFoundException{};
class RulesNotFoundException{};
class InvalidGrammarException{};
class TerminalNotSetException{};
class InfiniteGrammarFoundException{};
class GrammarContainNullException{};
class GrammarContainLeftRecursionException{};
class GrammarContainUnitProductionException{};
class RuleRightNotFoundException{};
class InvalidOption{
    string s;
public:
    InvalidOption(string x):s{x}{}
    friend ostream& operator<<(ostream& o,InvalidOption i){
        o<<i.s;
        return o;
    }
};

class HelpOption{};
class FewOptions{};
class FileNotFound{};

class SyntaxError{
        string error;
        unsigned int lineNumber;
        string fileName;
        string description;
    public:
        SyntaxError()=default;
        ~SyntaxError()=default;
        SyntaxError(const SyntaxError&)=default;
        SyntaxError(SyntaxError&&)=default;
        SyntaxError& operator=(const SyntaxError&)=default;
        SyntaxError& operator=(SyntaxError&&)=default;

        SyntaxError(string s,unsigned int x,string f,string des=""):error{s},lineNumber{x},fileName{f},description{des}{}

        friend ostream& operator<<(ostream& o,SyntaxError s){
            o<<s.error;
            return o;
        }
        
};

#ifndef _LOGGER_HPP_
#include<logger.hpp>
#endif // !_LOGGER_HPP_

#endif // !_TYPES_HPP_