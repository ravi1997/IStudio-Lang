#ifndef _RULE_HPP_
#define _RULE_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif

class ActionNotSet{};

template<typename T>
class Rule{
    class rightAssociate{
    private:
        enum class Type{
            TERMINAL,
            NONTERMINAL,
            FAULTY
        };
        Type getType([[maybe_unused]]NonTerminal<T>)const{
            return Type::NONTERMINAL;
        }
        Type getType([[maybe_unused]]Terminal)const{
            return Type::TERMINAL;
        }
        union Data{
            NonTerminal<T> n;
            Terminal<T> t;
            char x;
        };
        Type type;
        Data data;
    public:
        rightAssociate(NonTerminal<T> x):type{Type::NONTERMINAL},data.n{x}{}
        rightAssociate(Terminal<T> x):type{Type::TERMINAL},data.t{x}{}
        rightAssociate():type{Type::FAULTY},data.x{}{}
    };
    
    vector<rightAssociate> r;
    typedef T (*ActionType)(Parser<T>);
    ActionType action=nullptr;
    
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
