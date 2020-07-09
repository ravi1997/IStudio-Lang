#ifndef _NTTYPE_HPP_
#define _NTTYPE_HPP_ 1


#define PARSERTYPE FlowControlNode
#define TERMINAL Terminal<PARSERTYPE>
#define NONTERMINAL NonTerminal<PARSERTYPE>

#define T(name, pattern) TERMINAL name{pattern};

#define stringy(n) #n

#define N(name) NONTERMINAL name{stringy(name) };

#endif

