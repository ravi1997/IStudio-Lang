#ifndef _RIGHT_ASSOCIATE_HPP_
#define _RIGHT_ASSOCIATE_HPP_ 1

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif // !_TYPES_HPP_

#ifndef _TERMINAL_HPP_
#include <terminal.hpp>
#endif // !_TERMINAL_HPP_

#ifndef _NON_TERMINAL_HPP_
#include <nonterminal.hpp>
#endif // !_NON_TERMINAL_HPP_

enum class RightAssociateType
{
    TERMINAL,
    NONTERMINAL
};

ostream &operator<<(ostream &o, RightAssociateType a)
{
    switch (a)
    {
    case RightAssociateType::TERMINAL:
        o << "RightAssociate::Terminal";
        break;
    case RightAssociateType::NONTERMINAL:
        o << "RightAssociate::NonTerminal";
        break;
    }
    return o;
}

template <typename t>
using RightAssociate = pair<RightAssociateType, variant<Terminal<t>, NonTerminal<t>>>;

template <typename t>
ostream &operator<<(ostream &o, RightAssociate<t> r)
{
    switch (r.first)
    {
    case RightAssociateType::TERMINAL:
        o << get<Terminal<t>>(r.second);
        break;
    case RightAssociateType::NONTERMINAL:
        o << get<NonTerminal<t>>(r.second);
        break;
    }
    return o;
}

template <typename t>
Logger &operator<<(Logger &o, RightAssociate<t> r)
{
    switch (r.first)
    {
    case RightAssociateType::TERMINAL:
        o << get<Terminal<t>>(r.second);
        break;
    case RightAssociateType::NONTERMINAL:
        o << get<NonTerminal<t>>(r.second);
        break;
    }
    return o;
}

template <typename t>
bool operator==(RightAssociate<t> r, NonTerminal<t> n)
{
    if (r.first == RightAssociateType::NONTERMINAL)
    {
        return get<NonTerminal<t>>(r.second) == n;
    }
    else
    {
        return false;
    }
}

template <typename t>
bool operator==(RightAssociate<t> r, Terminal<t> n)
{
    if (r.first == RightAssociateType::TERMINAL)
    {
        return get<Terminal<t>>(r.second)==n;
    }
    else
    {
        return false;
    }
}

template<typename t>
First<t> getFirst(RightAssociate<t> r){
    switch (r.first)
    {
    case RightAssociateType::TERMINAL:
        return get<Terminal<t>>(r.second).getFirst();
        
    case RightAssociateType::NONTERMINAL:
        return get<NonTerminal<t>>(r.second).getFirst();
    }
    return First<t>{};
}

#endif // !_RIGHT_ASSOCIATE_HPP_
