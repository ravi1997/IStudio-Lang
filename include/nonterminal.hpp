#ifndef _NON_TERMINAL_HPP_
#define _NON_TERMINAL_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif

template<typename t=void>
class NonTerminal{
    Rules<t>* rs=nullptr;
public:
    NonTerminal(){}
    ~NonTerminal(){
        if(rs!=nullptr)
            delete rs;
    }
    NonTerminal& operator=(const NonTerminal& n){
        if(rs!=nullptr)
            delete rs;
        rs=new Rules{*(n.rs)};
        return *this;
    }
    NonTerminal& operator=(const NonTerminal&& n){
        if(rs!=nullptr)
            delete rs;
        rs=n.rs;
        return *this;
    }
    NonTerminal(const NonTerminal& n){
        rs=new Rules{*(n.rs)};
    }
    NonTerminal(const NonTerminal&& n){
        rs=n.rs;
    }
    Rules<t>* operator->(){
        if(rs==nullptr)
            return rs;
        rs=new Rules<t>{this};
        return rs;
    }
    First<t> getFirst(){
        First<t> f;
        for(auto x:*rs)
            f.insert(f.end(),x.getFirst().begin(),x.getFirst().end());
        return f;
    }
    Rules<t>& getRules() const{
        return *rs;
    }
    Follow<t> getFollow(Grammar<t> g){
        return g.getFollow(*this);
    }
};

#endif
