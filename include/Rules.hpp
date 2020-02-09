#ifndef _RULES_HPP_
#define _RULES_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif



class Rules{
    NonTerminal* left;
    vector<Rule> rs;
public:
    Rules(NonTerminal* x);
    auto begin(){
        return rs.begin();
    }
    auto end(){
        return rs.end();
    }

    template<typename... T>
    Rule& add(isSomething x,T... M);

    Rule add(isSomething);
    Rule add();
};

#endif
