#ifndef _RULES_HPP_
#define _RULES_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif
class InvalidRuleMisMatch{};

template<typename t>
class Rules{
    NonTerminal<t>* left=nullptr;
    vector<Rule<t>> rs;
public:
    Rules(NonTerminal<t>* x):left{x},rs{}{}
    Rules():rs{}{}
    Rules(const Rules& r){
      left=r.left;
      for(auto u:r.rs)
        rs.push_back(u);
    }
    Rules(const Rules&& r):left{r.left},rs{r.rs}{}
    Rules& operator=(const Rules& h){
        left=h.left;
        rs=h.rs;
        return *this;
    }
    Rules& operator=(const Rules&& h){
        left=h.left;
        rs=h.rs;
        return *this;
    }
    auto begin(){
        return rs.begin();
    }
    auto end(){
        return rs.end();
    }

    template<typename... T>
    Rule<t>& add(isSomething<t> x,T... M){
        Rule<t> myRule{this};
    //    cout<<rs.size()<<endl;

        rs.push_back(myRule);
    //    cout<<rs.size()-1<<endl;

        return rs[rs.size()-1].add(x,M...);
    }


    Rule<t>& add(isSomething<t> x){
        rs.push_back(Rule<t>{this});
        return rs[rs.size()-1].add(x);
    }

    Rule<t>& add(){
        rs.push_back(Rule<t>{this});
        return rs[rs.size()-1].add();
    }

    First<t> getFirst(){
        First<t> f;
        for(auto h:rs)
            f.insert(f.end(),h.getFirst().begin(),h.getFirst().end());
        return f;
    }

    Rules& operator|(const Rules r){
        if((r.left!=nullptr) &&(left!=nullptr) && (left!=r.left))
            throw InvalidRuleMisMatch{};
        for(auto i:r)
            rs.push_back(i);
        return *this;
    }
    Rules& operator|(const Rule<t> r){
        rs.push_back(r);
        return *this;
    }
    Rule<t>& operator[](int x){
        return rs[x];
    }
    friend class Rule<t>;
};

#endif
