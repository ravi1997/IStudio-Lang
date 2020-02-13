#ifndef _GRAMMMAR_HPP_
#define _GRAMMAR_HPP_

#include<types.hpp>
#include<terminal.hpp>
#include<nonterminal.hpp>
#include<Rule.hpp>
#include<Rules.hpp>

template<typename T>
class Grammar{
    vector<Terminal> t;
    vector<NonTerminal<int>> n;
    Rules<T> r;
    Grammar(vector<Terminal> x,vector<NonTerminal<int>> y):t{x},n{y}{
        for(auto i:n){
            for(auto j:*i.getRules())
                r|j;
        }
    }
    
};

#endif