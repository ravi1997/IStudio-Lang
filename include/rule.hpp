#ifndef _RULE_HPP_
#define _RULE_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif

template<typename T>
class Rule{
    union Data{
            NonTerminal<T> n;
            Terminal t;
            Data(){}
            Data(NonTerminal<T>);
            Data(Terminal);
            Data& operator=(NonTerminal<T>);
            Data& operator=(Terminal);
            ~Data(){}
    };
    enum class Type{
        TERMINAL,
        NONTERMINAL
    };
    vector<pair<Data,Type>> r;
    typedef T (*ActionType)(Parser<T>);
    ActionType action;
public:
    First getFirst();
    template<typename... v>
    Rule& add(isSomething<T> x,v... M);

    Rule& add(isSomething<T>);
    Rule& add();
};

template<typename t, typename... T>
Rule<t> add(isSomething<t> x,T... M);

template<typename t>
Rule<t> add(isSomething<t>);

template<typename t>
Rule<t> add();

#endif
