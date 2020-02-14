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
            Data(const Data&){}
            Data(const Data&&){}
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
    Type getType([[maybe_unused]]NonTerminal<T>)const{
        return Type::NONTERMINAL;
    }
    Type getType([[maybe_unused]]Terminal)const{
        return Type::TERMINAL;
    }

public:
    Rule(){};
    ~Rule(){};
    Rule(const Rule&){};
    Rule(const Rule&&){};
    Rule& operator=(const Rule&){};
    Rule& operator=(const Rule&&){};
    First getFirst();
    template<typename... v>
    Rule& add(isSomething<T> x,v... M);

    Rule& add(isSomething<T>);
    Rule& add();

    Rule& operator()(ActionType a){
        action=a;
        return *this;
    }
    T operator()(Parser<T> x);
};

template<typename t, typename... T>
Rule<t> add(isSomething<t> x,T... M);

template<typename t>
Rule<t> add(isSomething<t>);

template<typename t>
Rule<t> add();

#endif
