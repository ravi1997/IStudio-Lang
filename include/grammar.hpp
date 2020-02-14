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
    int numberOfRules=0;
    Grammar(vector<Terminal> x,vector<NonTerminal<int>> y):t{x},n{y}{
        int v=0;
        for(auto i:n){
            for(auto j:*i.getRules()){
                r|j;
                v++;
            }
        }
        numberOfRules=v;
    }
    Grammar(){}
    Grammar& operator=(const Grammar& h){
        t=h.t;
        n=h.t;
        r=h.r;
        return *this;
    }
    Grammar& operator=(const Grammar&& h){
        t=h.t;
        n=h.t;
        r=h.r;
        return *this;
    }
    auto getNumberOfTerminal(){
        return t.size();
    }
    int& getNumberOfRules(){
        return numberOfRules;
    }
};

#endif