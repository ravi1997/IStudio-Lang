#ifndef _RULES_HPP_
#define _RULES_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif


template<typename t>
class Rules{
    NonTerminal<t>* left;
    vector<Rule<t>> rs;
public:
    Rules(NonTerminal<t>* x);
    auto begin(){
        return rs.begin();
    }
    auto end(){
        return rs.end();
    }

    template<typename... T>
    Rules<t>& add(isSomething<t> x,T... M);

    Rules<t>& add(isSomething<t>);
    Rules<t>& add();
    First getFirst();
};

#endif
