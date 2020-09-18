#ifndef __TERMINAL_HPP__
#define __TERMINAL_HPP__

#pragma once

#ifndef __TYPES_HPP__
#include <types.hpp>
#endif

template <>
class Terminal<PARSERTYPE>
{
private:
    struct Data
    {
        string name;
        TerminalType type;
        string pattern;

        Data(string n, TerminalType ty, string pat) : name{n}, type{ty}, pattern{pat}
        {
        }

        Data(const Data &d) : name{d.name},
                              type{d.type},
                              pattern{d.pattern}
        {
        }

        Data(Data &&d) : name{move(d.name)},
                         type{move(d.type)},
                         pattern{move(d.pattern)}
        {
        }

        bool operator==(const Data &d) const
        {

            return name == d.name && type == d.type && pattern == d.pattern;
        }
        bool operator!=(const Data &d) const
        {
            return !(*this == d);
        }
    };

    shared_ptr<Data> data;

public:
    Terminal(string name, TerminalType ty, string pattern) : data{make_shared<Data>(name, ty, pattern)} {}
    Terminal(string name, string pattern) : Terminal(name, TerminalType::NORMAL, pattern) {}

    virtual ~Terminal() = default;

    virtual bool isOperator(void) const final
    {
        return data != nullptr && data->type == TerminalType::OPERATOR;
    }

    virtual bool isEpsilon(void) const final
    {
        return data != nullptr && data->type == TerminalType::EPSILON;
    }

    virtual bool isDollar(void) const final
    {
        return data != nullptr && data->type == TerminalType::DOLLAR;
    }

    TerminalType getType() const
    {
        if (data == nullptr)
            throw TerminalNotSet{};
        return data->type;
    }

    string &getName() const
    {
        if (data == nullptr)
            throw TerminalNotSet{};
        return data->name;
    }

    bool operator==(const Terminal &b) const
    {
        return *data == *b.data;
    }

    bool operator!=(const Terminal &b) const
    {
        return *data != *b.data;
    }

    template <typename Stream>
    friend Stream &operator<<(Stream &s, Terminal &b)
    {
        if (b.getName() != "")
            s << b.getName();
        return s;
    }
};

#endif // __TERMINAL_HPP__