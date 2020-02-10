#ifndef _TERMINAL_HPP_
#include<terminal.hpp>
#endif

#ifndef _RULES_HPP_
#include<Rules.hpp>
#endif

#ifndef _RULE_HPP_
#include<rule.hpp>
#endif

template<typename t>
Rules<t>::Rules(NonTerminal<t>* x):left{x}{}
template<typename t>
First Rules<t>::getFirst(){}
template<typename t>
template<typename... T>
Rules<t>& Rules<t>::add(isSomething<t> x,T... M){
    rs.push_back(Rule<t>{});
    rs[rs.size()-1].add(x,M...);
    return *this;
}

template<typename t>
Rules<t>& Rules<t>::add(isSomething<t> x){
    rs.push_back(Rule<t>{});
    rs[rs.size()-1].add(x);
    return *this;
}
template<typename t>
Rules<t>& Rules<t>::add(){
    rs.push_back(Rule<t>{});
    rs[rs.size()-1].add();
    return *this;
}
