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
};

#endif