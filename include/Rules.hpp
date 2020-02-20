#ifndef _RULES_HPP_
#define _RULES_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif
class InvalidRuleMisMatch{};

template<typename t>
class Rules{
    NonTerminal<t>* left=nullptr;
    vector<Rule<t>> rs;
public:
    Rules(NonTerminal<t>* x);
    Rules(){}
    Rules(const Rules& r):left{r.left},rs{r.rs}{}
    Rules(const Rules&& r):left{r.left},rs{r.rs}{}
    Rules& operator=(const Rules& h){
        left=h.left;
        rs=h.rs;
        return *this;
    }
    Rules& operator=(const Rules&& h){
        left=h.left;
        rs=h.rs;
        return *this;
    }
    auto begin(){
        return rs.begin();
    }
    auto end(){
        return rs.end();
    }

    template<typename... T>
    Rule<t>& add(isSomething<t> x,T... M);

    Rule<t>& add(isSomething<t>);
    Rule<t>& add();
    First getFirst();

    Rules& operator|(const Rules r){
        if((r.left!=nullptr) &&(left!=nullptr) && (left!=r.left))
            throw InvalidRuleMisMatch{};
        for(auto i:r)
            rs.push_back(i);
        return *this;
    }
    Rules& operator|(const Rule<t> r){
        rs.push_back(r);
        return *this;
    }
    Rule<t>& operator[](int x){
        return rs[x];
    }
    friend class Rule<t>;
};

#endif
