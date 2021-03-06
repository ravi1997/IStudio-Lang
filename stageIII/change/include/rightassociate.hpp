#ifndef  _RIGHTASSCIATE_HPP_
#define  _RIGHTASSCIATE_HPP_  1

#ifndef _TERMINAL_HPP_
#include <terminal.hpp>
#endif // !_TERMINAL_HPP_

#ifndef _OPERATOR_HPP_
#include<operator.hpp>
#endif // !_OPERATOR_HPP_

#ifndef _NONTERMINAL_HPP_
#include<nonterminal.hpp>
#endif // !_NONTERMINAL_HPP_

#ifndef _LOGGER_HPP_
#include <logger.hpp>
#endif // !_LOGGER_HPP_

enum class RightAssociateType
{
    TERMINAL,
    NONTERMINAL,
    UNARYPOST,
    UNARYPRE,
    BINARY
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
    case RightAssociateType::UNARYPOST:
        o << "RightAssociateType::UNARYPOST";
        break;
    case RightAssociateType::UNARYPRE:
        o << "RightAssociateType::UNARYPRE";
        break;
    case RightAssociateType::BINARY:
        o << "RightAssociateType::BINARY";
        break;
    }
    return o;
}

Logger& operator<<(Logger &o, RightAssociateType a)
{
    switch (a)
    {
    case RightAssociateType::TERMINAL:
        o << "RightAssociate::Terminal";
        break;
    case RightAssociateType::NONTERMINAL:
        o << "RightAssociate::NonTerminal";
        break;
    case RightAssociateType::UNARYPOST:
        o << "RightAssociateType::UNARYPOST";
        break;
    case RightAssociateType::UNARYPRE:
        o << "RightAssociateType::UNARYPRE";
        break;
    case RightAssociateType::BINARY:
        o << "RightAssociateType::BINARY";
        break;
    }
    return o;
}

template <typename t>
using RightAssociate = pair<
                            RightAssociateType, 
                            variant<
                                    Terminal<t>, 
                                    NonTerminal<t>, 
                                    UnaryPre<t>,
                                    UnaryPost<t>,
                                    Binary<t>
                                >
                            >;

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
    case RightAssociateType::UNARYPOST:
        o << get<UnaryPost<t>>(r.second);
        break;
    case RightAssociateType::UNARYPRE:
        o << get<UnaryPre<t>>(r.second);
        break;
    case RightAssociateType::BINARY:
        o << get<Binary<t>>(r.second);
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
    case RightAssociateType::UNARYPOST:
        o << get<UnaryPost<t>>(r.second);
        break;
    case RightAssociateType::UNARYPRE:
        o << get<UnaryPre<t>>(r.second);
        break;
    case RightAssociateType::BINARY:
        o << get<Binary<t>>(r.second);
        break;
    }
    return o;
}

template <typename t>
Clouser<t> getClouser(RightAssociate<t>& r,Grammar<t>& g){
    switch (r.first)
    {
    case RightAssociateType::TERMINAL:
        return get<Terminal<t>>(r.second).getClouser(g);
    case RightAssociateType::NONTERMINAL:
        return get<NonTerminal<t>>(r.second).getClouser(g);
    case RightAssociateType::UNARYPOST:
        return get<UnaryPost<t>>(r.second).getClouser(g);
    case RightAssociateType::UNARYPRE:
        return get<UnaryPre<t>>(r.second).getClouser(g);
    case RightAssociateType::BINARY:
        return get<Binary<t>>(r.second).getClouser(g);
    }
    return {};
}

template<typename t>
bool operator==(RightAssociate<t> r,NonTerminal<t> n){
    if (r.first == RightAssociateType::NONTERMINAL){
        return get<NonTerminal<t>>(r.second)==n;
    }
    else{
        return false;
    }
}

template <typename t>
bool operator==(RightAssociate<t> r, Terminal<t> n)
{
    if (r.first == RightAssociateType::TERMINAL)
    {
        return get<Terminal<t>>(r.second) == n;
    }
    else
    {
        return false;
    }
}

template <typename t>
bool operator==(RightAssociate<t> r, UnaryPre<t> n)
{
    if (r.first == RightAssociateType::UNARYPRE)
    {
        return get<UnaryPre<t>>(r.second) == n;
    }
    else
    {
        return false;
    }
}

template <typename t>
bool operator==(RightAssociate<t> r, UnaryPost<t> n)
{
    if (r.first == RightAssociateType::UNARYPOST)
    {
        return get<UnaryPost<t>>(r.second) == n;
    }
    else
    {
        return false;
    }
}

template <typename t>
bool operator==(RightAssociate<t> r, Binary<t> n)
{
    if (r.first == RightAssociateType::BINARY)
    {
        return get<Binary<t>>(r.second) == n;
    }
    else
    {
        return false;
    }
}

#endif // ! _RIGHTASSCIATE_HPP_