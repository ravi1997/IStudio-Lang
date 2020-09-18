#ifndef _NONTERMINAL_HPP_
#define _NONTERMINAL_HPP_

#ifndef __TYPES_HPP__
#include <types.hpp>
#endif

#ifndef _RULES_HPP_
#include <rules.hpp>
#endif

template <>
class NonTerminal<PARSERTYPE>
{
private:
    struct Data
    {
        string name = "";
        RULESTYPE rules;

        Data(string s) : name{s} {}
        ~Data()
        {
            rules.removeAll();
        }

        Data &operator=(const Data &d)
        {
            name = d.name;
            rules = d.rules;
            return *this;
        }

        Data &operator=(const Data &&d)
        {
            name = move(d.name);
            rules = move(d.rules);
            return *this;
        }

        bool operator==(const Data &d) const
        {
            return name == d.name;
        }

        bool operator!=(const Data &d) const
        {
            return name != d.name;
        }
    };

    shared_ptr<Data> data;

public:
    NonTerminal(string s) : data{make_shared<Data>(s)} {}
    NonTerminal(const NonTerminal &n) : data{n.data} {}
    NonTerminal(NonTerminal &&n) : data{move(n.data)} {}

    void add(const RULE &r) const
    {
        if (data != nullptr)
            data->rules.add(r);
    }

    bool operator==(const NonTerminal &n) const
    {
        return data != nullptr && n.data != nullptr && *data == *n.data;
    }

    bool operator!=(const NonTerminal &n) const
    {
        return data != nullptr && n.data != nullptr && *data != *n.data;
    }

    RULE &operator->() const
    {
        return data->rules.back();
    }

    RULESTYPE &getRules() const
    {
        if (data == nullptr)
            throw NonTerminalNotSet{};
        return data->rules;
    }

    string &getName() const
    {
        if (data == nullptr)
            throw NonTerminalNotSet{};
        return data->name;
    }

    template <typename stream>
    friend stream &operator<<(stream &s, NonTerminal &n)
    {
        if (n.data != nullptr)
            if (n.data->name != "")
                s << n.getName();
        return s;
    }
};

#endif // _NONTERMINAL_HPP_