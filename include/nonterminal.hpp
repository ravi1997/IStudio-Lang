#ifndef _NON_TERMINAL_HPP_
#define _NON_TERMINAL_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif

template<typename t>
class NonTerminal{
    shared_ptr<Rules<t>> r;
public:
    NonTerminal();
    ~NonTerminal();
    NonTerminal& operator=(const NonTerminal&);
    NonTerminal& operator=(const NonTerminal&&);
    NonTerminal(const NonTerminal&);
    NonTerminal(const NonTerminal&&);
    shared_ptr<Rules<t>>& operator->();
    First getFirst();
    shared_ptr<Rules<t>>& getRules(){
        return r;
    }
    Follow getFollow(Grammar<t>);
};

#endif
