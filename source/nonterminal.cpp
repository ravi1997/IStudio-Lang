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

#ifndef _GRAMMAR_HPP_
#include<grammar.hpp>
#endif


template<typename t>
NonTerminal<t>::NonTerminal():r{new Rules{this}}{}
template<typename t>
NonTerminal<t>::~NonTerminal(){}
template<typename t>
NonTerminal<t>& NonTerminal<t>::operator=(const NonTerminal<t>& x){
    r=x.r;
    return *this;
}
template<typename t>
NonTerminal<t>& NonTerminal<t>::operator=(const NonTerminal<t>&&x){
    r=x.r;
    return *this;
}
template<typename t>
NonTerminal<t>::NonTerminal(const NonTerminal<t>&x):r{x.r}{}
template<typename t>
NonTerminal<t>::NonTerminal(const NonTerminal<t>&&x):r{x.r}{}
template<typename t>
shared_ptr<Rules<t>>& NonTerminal<t>::operator->(){
    return r;
}
template<typename t>
First NonTerminal<t>::getFirst(){
    First f;
    for(auto x:*r)
        f.insert(f.end(),x.getFirst().begin(),x.getFirst().end());

    return f;
}

template<typename t>
Follow NonTerminal<t>::getFollow(Grammar<t> g){
    return g.getFollow(*this);
}

