#ifndef __RIGHTASSOCIATE_HPP__
#define __RIGHTASSOCIATE_HPP__

#ifndef __TYPES_HPP__
#include <types.hpp>
#endif // !__TYPES_HPP__

#ifndef __TERMINAL_HPP__
#include <terminal.hpp>
#endif // !__TERMINAL_HPP__

#ifndef _NONTERMINAL_HPP_
#include <nonterminal.hpp>
#endif // !_NONTERMINAL_HPP_

template <typename Stream>
Stream &operator<<(Stream &o, const RightAssociateType &a)
{
    switch (a)
    {
    case RightAssociateType::TERMINALOBJ:
        o << "RightAssociate::Terminal";
        break;
    case RightAssociateType::NONTERMINALOBJ:
        o << "RightAssociate::NonTerminal";
        break;
    }
    return o;
}

template <typename Stream>
Stream &operator<<(Stream &o, const RightAssociate &a)
{
    switch (a.first)
    {
    case RightAssociateType::TERMINALOBJ:
        o << get<TERMINAL>(a.second);
        break;
    case RightAssociateType::NONTERMINALOBJ:
        o << get<NONTERMINAL>(a.second);
        break;
    default:
        o << "Error some" << endl;
        break;
    }
    return o;
}

bool isNonTerminal(const RightAssociate &r)
{
    return r.first == RightAssociateType::NONTERMINALOBJ;
}

bool isTerminal(const RightAssociate &r)
{
    return r.first == RightAssociateType::TERMINALOBJ;
}

bool operator==(const RightAssociate &l, const TERMINAL &r)
{
    return isTerminal(l) && get<TERMINAL>(l.second) == r;
}

bool operator==(const RightAssociate &l, const NONTERMINAL &r)
{
    return isNonTerminal(l) && get<NONTERMINAL>(l.second) == r;
}

bool operator!=(const RightAssociate &l, isRightAssociate auto x)
{
    return !(l == x);
}
#endif // __RIGHTASSOCIATE_HPP__