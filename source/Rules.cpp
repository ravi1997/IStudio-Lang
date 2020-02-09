#ifndef _RULES_HPP_
#include<Rules.hpp>
#endif

#ifndef _RULE_HPP_
#include<rule.hpp>
#endif

Rules::Rules(NonTerminal* x):left{x}{}
First Rules::getFirst(){}
template<typename... T>
Rule& Rules::add(isSomething x,T... M){
    r.push_back(x);
    if(sizeof...(M)>0)
        return add(M...);
    else
        return *this;
}

Rule& Rules::add(isSomething x){
    r.push_back(x);
    return *this;
}
Rule& Rules::add(){
    Terminal epsilon{""};    
    r.push_back(epsilon);
    return *this;
}

