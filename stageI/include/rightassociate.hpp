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

ostream &operator<<(ostream &o, RightAssociateType& a)
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
ostream &operator<<(ostream &o, RightAssociate<t>& r)
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
Logger &operator<<(Logger &o, RightAssociate<t>& r)
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
bool isNonTerminal(const RightAssociate<t> &r) {
    return r.first==RightAssociateType::NONTERMINAL;
}

template <typename t>
bool isTerminal(const RightAssociate<t> &r)
{
    return r.first == RightAssociateType::TERMINAL;
}

template <typename t>
bool operator==(const RightAssociate<t>& r, const NonTerminal<t>& n)
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
bool operator==(const RightAssociate<t>& r, const Terminal<t>& n)
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

template <typename t>
bool operator==(RightAssociate<t>& r, RightAssociate<t>& n)
{
    //cout<<r.first<<" == "<<n.first<<endl;
    if (r.first == n.first)
    {
        switch(n.first){
        case RightAssociateType::TERMINAL:
            return get<Terminal<t>>(r.second) == get<Terminal<t>>(n.second);
        case RightAssociateType::NONTERMINAL:
            return get<NonTerminal<t>>(r.second) == get<NonTerminal<t>>(n.second);
        }
        return false;
    }
    else
    {
        return false;
    }
}

template <typename t>
bool operator!=(RightAssociate<t>& r, RightAssociate<t>& n)
{
    //cout<<r<<endl;
    //cout<<r.first<<endl;
    return !(r==n);
}

template <typename t>
bool operator!=(RightAssociate<t>& r, Terminal<t>& n)
{
    return !(r == n);
}

template <typename t>
bool operator!=(RightAssociate<t>& r, NonTerminal<t>& n)
{
    return !(r == n);
}

template <typename t>
First<t> getFirst(RightAssociate<t>& r)
{
    switch (r.first)
    {
    case RightAssociateType::TERMINAL:
        return get<Terminal<t>>(r.second).getFirst();
        
    case RightAssociateType::NONTERMINAL:
        return get<NonTerminal<t>>(r.second).getFirst();
    }
    return First<t>{};
}

template <typename t>
ostream &operator<<(ostream &o, State<t>& s)
{
    for (auto h : s)
    {
            o << h.first << " ";
            for (auto l1 : h.second)
                o << l1 << " ";
            o << endl;
    }
    return o;
}

template <typename t>
Logger &operator<<(Logger &o, State<t> &s)
{
    for (auto h : s)
    {
        o << h.first << " ";
        for (auto l1 : h.second)
            o << l1 << " ";
        o << Logger::endl;
    }
    return o;
}


Logger& operator<<(Logger& l,SR s){
    switch(s){
        case SR::SHIFT:l<<"SHIFT";break;
        case SR::REDUCE:l<<"REDUCE";break;
        case SR::EMPTY:l<<"REDUCE";break;
    }
    return l;
}

ostream &operator<<(ostream &l, SR s)
{
    switch (s)
    {
    case SR::SHIFT:
        l << "SHIFT";
        break;
    case SR::REDUCE:
        l << "REDUCE";
        break;
    case SR::EMPTY:
        l<<"EMPTY";
        break;
    }
    return l;
}

#endif // !_RIGHT_ASSOCIATE_HPP_
