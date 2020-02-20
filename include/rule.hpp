#ifndef _RULE_HPP_
#define _RULE_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif

class ActionNotSet{};

template<typename T>
class Rule{
    enum class Type{
        TERMINAL,
        NONTERMINAL
    };
    vector<pair<variant<NonTerminal<T>,Terminal>,Type>> r;
    typedef T (*ActionType)(Parser<T>);
    ActionType action=nullptr;
    Type getType([[maybe_unused]]NonTerminal<T>)const{
        return Type::NONTERMINAL;
    }
    Type getType([[maybe_unused]]Terminal)const{
        return Type::TERMINAL;
    }
    Rules<T>* rs=nullptr;
public:
    Rule(){};
    ~Rule(){};
    Rule(Rules<T>* sr):rs{sr}{}
    Rule(const Rule& f):r{f.r},action{f.action},rs{f.rs}{}
    Rule(const Rule&& f):r{f.r},action{f.action},rs{f.rs}{}
    Rule& operator=(const Rule& f){
        r.clear();
        for(auto i:f.r)
            r.push_back(i);
        rs=f.rs;
        action=f.action;
        return *this;
    }
    Rule& operator=(const Rule&&f){
        r.clear();
        for(auto i:f.r)
            r.push_back(i);
        rs=f.rs;
        action=f.action;
        return *this;
    }
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
    Follow getFollowOf(Grammar<T>,NonTerminal<T> n);
    Rules<T>& operator|(Rule r){
        return (*rs)|r;
    }

    friend class Rules<T>;
};

template<typename t, typename... T>
Rule<t> add(isSomething<t> x,T... M);

template<typename t>
Rule<t> add(isSomething<t>);

template<typename t>
Rule<t> add();

#endif
