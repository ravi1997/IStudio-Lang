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
#include <climits>
#include <iomanip> // put_time
#include <string>
#include <type_traits>
#include <variant>
#include <vector>
#include<cassert> 
using namespace std;

// forward declarations

template<typename t>class Terminal;
template<typename t>class NonTerminal;
template<typename t>class Parser;
template<typename t>class Rule;
template<typename t>class Rules;
template <typename t>class HandleRule;
class Logger;
class FlowControlNode;


    // Utilities
template <typename t>
using First = vector<Terminal<t>>;

template<typename t>
using Follow=vector<Terminal<t>>;

template <typename t>
using Clouser = vector<HandleRule<t>>;

template <typename t, typename x>
concept isRightAssociate = is_same<t, NonTerminal<x>>::value || is_same<t, Terminal<x>>::value;

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
class ShiftReduce{};
class ReduceReduce{};
class Empty
{
};
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
class FileNotFound{
        string file="";
    public:
        FileNotFound() = default;
        ~FileNotFound() = default;
        FileNotFound& operator=(const FileNotFound&) = default;

        FileNotFound(const FileNotFound&)=default;

        FileNotFound(string s):file{s}{}


        friend ostream& operator<<(ostream& e,FileNotFound f){
            e<<f.file;
            return e;
        }
};

#ifndef _LOGGER_HPP_
#include"logger.hpp"
#endif // !_LOGGER_HPP_

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

        friend Logger &operator<<(Logger &o, SyntaxError s)
        {
            o <<s.fileName<<" "<<s.lineNumber<<" : "<< s.error;
            return o;
        }
};

template<typename t>
using LookAheads=vector<Terminal<t>>;

template <typename t>
using State = vector<pair<HandleRule<t>, LookAheads<t>>>;


enum class SR{
    SHIFT,
    REDUCE,
    EMPTY
};

template<typename t>
using Action=map<int,map<int,pair<SR,size_t>>>;

template<typename t>
using Goto=map<int,map<int,size_t>>;

template <typename t>
using ParserTable = pair<Action<t>,Goto<t>>;

template <typename t>
using Token = pair<Terminal<t>, string>;

class Successfull{};

#endif // !_TYPES_HPP_