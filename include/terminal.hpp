#ifndef _TERMINAL_HPP_
#define _TERMINAL_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif

class Terminal{
regex r;
string pattern;
public:
    Terminal(string s):r{(s!=string{""})?string{"^"}+s:s},pattern{s}{}
    string getMatch(string s){
        smatch m; 
        regex_search(s, m, r);
        for(auto x:m)
            return x;
    }
    bool operator==(const Terminal t)const{
        return pattern==t.pattern;
    }
    bool operator!=(const Terminal t)const{
        return !(*this==t);
    }
    
};

#endif