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
First Rules<t>::getFirst(){
    First f;
    for(auto h:rs)
        f.insert(f.end(),h.getFirst().begin(),h.getFirst().end());
    return f;
}
template<typename t>
template<typename... T>
Rule<t>& Rules<t>::add(isSomething<t> x,T... M){
    rs.push_back(Rule<t>{this});
    return rs[rs.size()-1].add(x,M...);
}

template<typename t>
Rule<t>& Rules<t>::add(isSomething<t> x){
    rs.push_back(Rule<t>{this});
    return rs[rs.size()-1].add(x);
}
template<typename t>
Rule<t>& Rules<t>::add(){
    rs.push_back(Rule<t>{this});
    return rs[rs.size()-1].add();
}

