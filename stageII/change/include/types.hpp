#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#pragma once

#include <experimental/source_location>
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <variant>
#include <vector>
#include <fstream>
using namespace std;

template <typename t>
class NonTerminal;
template <typename t>
class Terminal;
template <typename t>
class Rule;
template <typename t>
class HandleRule;
template <typename t>
class Rules;
template <typename t>
class Grammar;
template <typename t>
class Parser;
class FlowControl;

enum class TerminalType
{
    NORMAL,
    DOLLAR,
    EPSILON,
    OPERATOR
};

///////////////////////////////////////////////////////////////////////////////////////
//                                EXCEPTIONS                                         //
///////////////////////////////////////////////////////////////////////////////////////
class Exception
{
private:
    unsigned int line = 0;
    string fileName = "";
    string description = "";

public:
    Exception(unsigned int l, string f, string des)
        : line{l}, fileName{f}, description{des} {}

    template <typename stream>
    friend stream &operator<<(stream &s, const Exception &e)
    {
        s << e.fileName << ":" << e.line << ":" << e.description;
        return s;
    }
};

class TerminalNotSet : public Exception
{
public:
    TerminalNotSet(const std::experimental::source_location &location =
                       std::experimental::source_location::current())
        : Exception(location.line(), location.file_name(), "TerminalNotSet") {}
};

class RulesNotSet : public Exception
{
public:
    RulesNotSet(const std::experimental::source_location &location =
                    std::experimental::source_location::current())
        : Exception(location.line(), location.file_name(), "RulesNotSet") {}
};

class FileNotFound : public Exception
{
public:
    FileNotFound(const std::experimental::source_location &location =
                     std::experimental::source_location::current())
        : Exception(location.line(), location.file_name(), "FileNotFound") {}
};

class RuleNotSet : public Exception
{
public:
    RuleNotSet(const std::experimental::source_location &location =
                   std::experimental::source_location::current())
        : Exception(location.line(), location.file_name(), "RuleNotSet") {}
};

class GrammarNotSet : public Exception
{
public:
    GrammarNotSet(const std::experimental::source_location &location =
                      std::experimental::source_location::current())
        : Exception(location.line(), location.file_name(), "GrammarNotSet") {}
};

class CompilerError : public Exception
{
public:
    CompilerError(const string s, const std::experimental::source_location &location =
                                      std::experimental::source_location::current())
        : Exception(location.line(), location.file_name(), string{"CompilerError : "} + s) {}
};

class NonTerminalNotSet : public Exception
{
public:
    NonTerminalNotSet(const std::experimental::source_location &location =
                          std::experimental::source_location::current())
        : Exception(location.line(), location.file_name(), "NonTerminalNotSet : ") {}
};

class BadAlloc : public Exception
{
public:
    BadAlloc(const std::experimental::source_location &location =
                 std::experimental::source_location::current())
        : Exception(location.line(), location.file_name(), "BadAlloc : ") {}
};

class RightAssociateNotSet : public Exception
{
public:
    RightAssociateNotSet(const std::experimental::source_location &location =
                             std::experimental::source_location::current())
        : Exception(location.line(), location.file_name(), "RightAssociateNotSet : ") {}
};

class RulesEmpty : public Exception
{
public:
    RulesEmpty(const std::experimental::source_location &location =
                   std::experimental::source_location::current())
        : Exception(location.line(), location.file_name(), "RulesEmpty : ") {}
};

class HandleRuleException : public Exception
{
public:
    HandleRuleException(const std::experimental::source_location &location =
                            std::experimental::source_location::current())
        : Exception(location.line(), location.file_name(), "HandleRuleException : ") {}
};

#define stringify(s) #s
#define PARSERTYPE FlowControl

#define NONTERMINALTYPE NonTerminal<PARSERTYPE>
#define TERMINALTYPE Terminal<PARSERTYPE>
#define RULESTYPE Rules<PARSERTYPE>
#define RULETYPE Rule<PARSERTYPE>
#define HANDLERULE HandleRule<PARSERTYPE>
#define GRAMMAR Grammar<PARSERTYPE>
#define PARSER Parser<PARSERTYPE>

enum class RightAssociateType
{
    TERMINALOBJ,
    NONTERMINALOBJ
};

using RightAssociate = pair<RightAssociateType, variant<shared_ptr<NONTERMINALTYPE>, shared_ptr<TERMINALTYPE>>>;


#include <shared_ptr.hpp>

#define NONTERMINAL shared_ptr<NONTERMINALTYPE>
#define TERMINAL shared_ptr<TERMINALTYPE>
#define RULES shared_ptr<RULESTYPE>
#define RULE shared_ptr<RULETYPE>
#define RIGHTASSOCIATE shared_ptr<RightAssociate>

#define N(name) \
    NONTERMINAL name { stringify(name) }
#define T(name, pat) \
    TERMINAL name { stringify(name), pat }

template <typename t>
concept isRightAssociate = is_same<t, NONTERMINAL>::value || is_same<t, TERMINAL>::value;

enum class TableEntry
{
    SHIFT,
    REDUCE,
    ERROR
};

using First = vector<TERMINAL>;
using Follow = vector<TERMINAL>;

using LookAheads = vector<TERMINAL>;

using StateRule = pair<HANDLERULE, LookAheads>;

using State = vector<StateRule>;

using Action = pair<TableEntry, unsigned int>;

using ActionTable = map<State, map<TERMINAL, Action>>;
using GotoTable = map<State, map<NONTERMINAL, unsigned int>>;
using ParseringTable = pair<ActionTable, GotoTable>;

#endif //__TYPES_HPP__