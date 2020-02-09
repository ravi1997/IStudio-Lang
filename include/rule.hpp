#ifndef _RULE_HPP_
#define _RULE_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif

class Rule{
    union Data{
            NonTerminal n;
            Terminal t;
            Data(){}
            Data(NonTerminal);
            Data(Terminal);
            Data& operator=(NonTerminal);
            Data& operator=(Terminal);
            ~Data(){}
    };
    enum class Type{
        TERMINAL,
        NONTERMINAL
    };
    vector<pair<Data,Type>> r;
public:
    First getFirst();
    template<typename... T>
    Rule& add(isSomething x,T... M);
    
    Rule& add(isSomething);
    Rule& add();
};

template<typename... T>
Rule add(isSomething x,T... M);

Rule add(isSomething);
Rule add();

#endif
