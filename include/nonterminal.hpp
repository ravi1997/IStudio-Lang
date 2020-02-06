#ifndef _NON_TERMINAL_HPP_
#define _NON_TERMINAL_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif


class NonTerminal{
    shared_ptr<Rules> r;
public:
    NonTerminal();
    ~NonTerminal();
    NonTerminal& operator=(const NonTerminal&);
    NonTerminal& operator=(const NonTerminal&&);
    NonTerminal(const NonTerminal&);
    NonTerminal(const NonTerminal&&);
    shared_ptr<Rules>& operator->();
    First getFirst();
};

#endif
