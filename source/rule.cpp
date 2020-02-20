#ifndef _TERMINAL_HPP_
#include <terminal.hpp>
#endif

#ifndef _NON_TERMINAL_HPP_
#include <nonterminal.hpp>
#endif


#ifndef _RULE_HPP_
#include<rule.hpp>
#endif

template<typename t>
First Rule<t>::getFirst(){
    for(auto i:r)
        if(i.second==Type::TERMINAL)
            return First{i.first};
        else{
            bool flag=false;
            for(auto x:i.first.getFirst())
                if(x==epsilon){
                    flag=true;
                    break;
                }
            if(flag==true)
                continue;
            return i.first.getFirst();
        }
}

template<typename T>
T Rule<T>::operator()(Parser<T> x){
    if(action==nullptr)
        throw ActionNotSet{};
    return action(x);
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
        r.push_back(pair{epsilon,getType(epsilon)});
        return *this;
    }

template<typename T>
Follow Rule<T>::getFollowOf(Grammar<T> g,NonTerminal<T> n){
    bool flag=false;
    Follow f;
    for(auto i:r){
        if(flag){
            flag=false;
            if(i.second==Type::TERMINAL)
                f.push_back(i.first.t);
            else{
                First f2;
                if (get<NonTerminal>(i.first)==*(rs->left))
                {

                }
                else{
                    f2=i.first.getFirst();
                    for (auto i = f2.begin(); i != f2.end(); ++i) {
                        if(*i==epsilon){
                            flag=true;
                            f2.erase(i);
                        }
                    }
                    f.insert(f.end(),f2.begin(),f2.end());
                }
            }
            if(flag)
                continue;
        }
        if((i.second==Type::NONTERMINAL)&&(i.first.n==n))
            flag=true;
    }
    if(flag){
        Follow ghg=g.getFollowOf(*(rs->left));
        f.insert(f.end(),ghg.begin(),ghg.end());
    }
    return f;
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
