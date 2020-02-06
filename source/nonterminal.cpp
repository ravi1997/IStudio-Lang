#ifndef _TERMINAL_HPP_
#include <terminal.hpp>
#endif

#ifndef _NON_TERMINAL_HPP_
#include<nonterminal.hpp>
#endif

#ifndef _RULE_HPP_
#include<rule.hpp>
#endif


#ifndef _RULES_HPP_
#include<Rules.hpp>
#endif



NonTerminal::NonTerminal():r{new Rules{this}}{}
NonTerminal::~NonTerminal(){}
NonTerminal& NonTerminal::operator=(const NonTerminal& x){
    r=x.r;
    return *this;
}
NonTerminal& NonTerminal::operator=(const NonTerminal&&x){
    r=x.r;
    return *this;
}
NonTerminal::NonTerminal(const NonTerminal&x):r{x.r}{}
NonTerminal::NonTerminal(const NonTerminal&&x):r{x.r}{}
shared_ptr<Rules>& NonTerminal::operator->(){
    return r;
}
First NonTerminal::getFirst(){
    First f;
    for(auto x:*r)
        f.insert(f.end(),x.getFirst().begin(),x.getFirst().end());

    return f;
}
