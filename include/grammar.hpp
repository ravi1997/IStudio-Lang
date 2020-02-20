#ifndef _GRAMMAR_HPP_
#define _GRAMMAR_HPP_

#include<types.hpp>
#include<terminal.hpp>
#include<nonterminal.hpp>
#include<Rule.hpp>
#include<Rules.hpp>

class TokenMismatch{};


template<typename T>
class Grammar{
    vector<Terminal> t;
    vector<NonTerminal<T>> n;
    Rules<T> r;
    NonTerminal<T> start;
    int numberOfRules=0;
    Grammar(vector<Terminal> x,vector<NonTerminal<T>> y,NonTerminal<T> s):t{x},n{y},start{s}{
        int v=0;
        for(auto i:n){
            for(auto j:*i.getRules()){
                r|j;
                v++;
            }
        }
        numberOfRules=v;
    }
    Grammar(){}
    Grammar(const Grammar&g):t{g.t},n{g.n},r{g.r},start{g.start},numberOfRules{g.numberOfRules}{}
    Grammar(const Grammar&&g):t{g.t},n{g.n},r{g.r},start{g.start},numberOfRules{g.numberOfRules}{}
    Grammar& operator=(const Grammar& h){
        t=h.t;
        n=h.n;
        r=h.r;
        return *this;
    }
    Grammar& operator=(const Grammar&& h){
        t=h.t;
        n=h.n;
        r=h.r;
        return *this;
    }
    auto getNumberOfTerminal(){
        return t.size();
    }
    int& getNumberOfRules(){
        return numberOfRules;
    }
    Follow getFollowOf(NonTerminal<T> n){
            Follow fn;
            for(auto x:r){
                Follow temp=x.getFollow(*this,n);
                fn.insert(fn.end(),temp.begin(),temp.end());
            }
            if(n==start)
                fn.push_back(dollar);
            return fn;
    }
    pair<Terminal,string> getNextToken(string& gh){
        string s;
        Terminal sdf;
        for(string ccv;auto i:t){
            ccv=i.match(gh);
            if(s.length()==ccv.length())
                throw TokenMismatch{};
            else if(s.length()<ccv.length()){
                s=ccv;
                sdf=i;
            }
        }
        size_t pos = gh.find(s);
        if (pos != string::npos)
        {
            // If found then erase it from string
            gh.erase(pos, s.length());
        }
        return {sdf,s};
    }
};

#endif
