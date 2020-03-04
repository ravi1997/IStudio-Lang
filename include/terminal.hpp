#ifndef _TERMINAL_HPP_
#define _TERMINAL_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif

template<typename t>
class Terminal{
    string pattern;
    enum class Type{
        NORMAL,
        EPSILON,
        END
    };
    Type type;
    using actionType=void (*)(Parser<t>&);
    actionType action;
public:
    Terminal(string s="",bool end=false):pattern{s},type{(end)?Type::END:(s=="")?Type::EPSILON:Type::NORMAL}{}
    ~Terminal(){}
    Terminal(const Terminal& x):pattern{x.pattern},type{x.type},action{x.action}{}
    Terminal(const Terminal&& x):pattern{x.pattern},type{x.type},action{x.action}{}
    Terminal& operator=(const Terminal& x){
        pattern=x.pattern;
        type=x.type;
        action=x.action;
        return *this;
    }
    Terminal& operator=(const Terminal&& x){
        pattern=x.pattern;
        type=x.type;
        action=x.action;
        return *this;
    }
    
    string getMatch(string s){
        smatch m;
        regex_search(s, m, regex{(pattern!=string{""})?string{"^"}+pattern:pattern});
        for(auto x:m)
            return x;
    }
    bool operator==(const Terminal x)const{
        return (pattern==x.pattern)&&(type==x.type);
    }
    bool operator!=(const Terminal x)const{
        return !(*this==x);
    }
    const static Terminal<t> epsilon;
    const static Terminal<t> dollar;
};


#endif
