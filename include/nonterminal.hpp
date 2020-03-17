#ifndef _NON_TERMINAL_HPP_
#define _NON_TERMINAL_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif

template<typename t=void>
class NonTerminal{
    Rules<t>* rs=nullptr;
    int * x=nullptr;
public:
    NonTerminal(){}
    ~NonTerminal(){
  //    cout<<"destructor"<<endl;
      if(rs!=nullptr && x!=nullptr){
        (*x)--;
        if(*x==0){
          delete x;
          delete rs;
        }
      }
    }

    NonTerminal& operator=(const NonTerminal& n){
        if(rs!=nullptr && x!=nullptr){
          if(rs!=n.rs && x!=n.x){
            (*x)--;
            if(*x==0){
              delete x;
              delete rs;
            }
            if(n.x!=nullptr)
              ++(*n.x);
          }
        }
        rs=n.rs;
        x=n.x;
        return *this;
    }
    NonTerminal& operator=(const NonTerminal&& n){
      if(rs!=nullptr && x!=nullptr){
        (*x)--;
        if(*x==0){
          delete x;
          delete rs;
        }
      }
      rs=n.rs;
      x=n.x;
      n.rs=n.x=nullptr;
      return *this;
    }
    NonTerminal(const NonTerminal& n){
        rs=n.rs;
        x=n.x;
        if(x!=nullptr)
          (*x)++;
    }
    NonTerminal(const NonTerminal&& n){
        rs=n.rs;
        x=n.x;
        n.rs=n.x=nullptr;
    }
    Rules<t>* operator->(){
        if(rs!=nullptr)
            return rs;
        rs=new Rules<t>{this};
        x=new int(0);
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
