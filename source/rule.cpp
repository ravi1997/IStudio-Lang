#ifndef _TERMINAL_HPP_
#include <terminal.hpp>
#endif


#ifndef _RULE_HPP_
#include<rule.hpp>
#endif

template<typename t>
First Rule<t>::getFirst(){
    return First{};
}



    template<typename T>
    Rule<T>::Data::Data(NonTerminal<T> x):n{x}{}
    template<typename T>
    Rule<T>::Data::Data(Terminal x):t{x}{}
    template<typename T>
    Rule<T>::Data& Rule<T>::Data::operator=(NonTerminal<T> x){
        n=x;
        return *this;
    }
    template<typename T>
    Rule<T>::Data& Rule<T>::Data::operator=(Terminal x){
        t=x;
        return *this;
    }
    
    template<typename T>
    template<typename... v>
    Rule<T>& Rule<T>::add(isSomething<T> x,v... M){
        r.push_back(pair{x,getType(x)});
        return add(M...);
    }

    template<typename T>
    Rule<T>& Rule<T>::add(isSomething<T> x){
        r.push_back(pair{x,getType(x)});
        return *this;
    }
    template<typename T>
    Rule<T>& Rule<T>::add(){
        Terminal epsilon;
        r.push_back(pair{epsilon,getType(epsilon)});
        return *this;
    }


template<typename t, typename... T>
Rule<t> add(isSomething<t> x,T... M){
    return Rule<t>{}.add(x,M...);
}

template<typename t>
Rule<t> add(isSomething<t> x){
    return Rule<t>{}.add(x);
}

template<typename t>
Rule<t> add(){
    return Rule<t>{}.add();
}
