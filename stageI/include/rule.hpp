#ifndef __RULE_HPP__
#define __RULE_HPP__

#pragma once

#ifndef __TYPES_HPP__
#include <types.hpp>
#endif

#include <rightassociate.hpp>

template <>
class Rule<PARSERTYPE>
{
private:
    // using actionType = function<t(Parser<t>&)>;
    struct Data
    {
        NONTERMINAL left;
        vector<RIGHTASSOCIATE> right;
        // actionType action;

        Data() {}
        Data(const NONTERMINAL &s) : left{s} {}
        Data(const Data &d) : left{d.left}
        {
            for (auto r : d.right)
                right.push_back(r);
        }

        Data(Data &&d) : left{move(d.left)}, right{move(d.right)} {}

        template <typename Stream>
        friend Stream &operator<<(Stream &o, const Data &d)
        {

            if (d.left != nullptr)
                o << d.left << " -> add(";

            // o << "here" << endl;

            if (d.right.size() != 0)
                for (auto r : d.right)
                {
                    // o << "here" << endl;
                    o << r << ",";
                }
            o << ");";
            return o;
        }

        bool operator==(const Data &d) const
        {
            if (left != d.left || right.size() != d.right.size())
                return false;

            for (size_t i = 0, j = right.size(); i < j; i++)
                if (right[i] != d.right[i])
                    return false;

            return true;
        }

        bool operator!=(const Data &d) const
        {
            if (left != d.left || right.size() != d.right.size())
                return true;
            return !(*this == d);
        }
    };

    shared_ptr<Data> data;

    template <typename t>
    constexpr auto getType(t) const requires(is_same_v<t, TERMINAL>)
    {
        return RightAssociateType::TERMINALOBJ;
    }

    template <typename t>
    constexpr auto getType(t) const requires(is_same_v<t, NONTERMINAL>)
    {
        return RightAssociateType::NONTERMINALOBJ;
    }

public:
    Rule() : data{make_shared<Data>()} {}
    Rule(const NONTERMINAL &n) : data{make_shared<Data>(n)} {}
    Rule(const Rule &r) : data{r.data} {}
    Rule(Rule &&r) : data{move(r.data)} {}

    void setLeft(const NONTERMINAL &N)
    {
        data->left = N;
    }

    vector<RIGHTASSOCIATE> &getRightAssociates() const
    {
        if (data == nullptr)
            throw RuleNotSet{};

        return data->right;
    }

    NONTERMINAL &getLeft() const
    {
        if (data == nullptr)
            throw RuleNotSet{};
        return data->left;
    }

    template <typename Stream>
    friend Stream &operator<<(Stream &o, const Rule &r)
    {
        if (r.data != nullptr)
            o << *r.data;
        return o;
    }

    bool operator==(const Rule &r) const
    {
        return data != nullptr &&
               r.data != nullptr &&
               *data == *r.data;
    }

    bool operator!=(const Rule &r) const
    {
        return data != nullptr &&
               r.data != nullptr &&
               *data != *r.data;
    }

    Rule &add()
    {
        if (data == nullptr)
            throw RuleNotSet{};
        try
        {
            if (getRightAssociates().size() != 0)
                throw 1;
        }
        catch (...)
        {
            throw 1;
        }
        data->right.push_back(RIGHTASSOCIATE{RightAssociateType::TERMINALOBJ, TERMINAL::EPSILON});
        return *this;
    }

    Rule &add(auto temp) requires(isRightAssociate<decltype(temp)>)
    {
        if (data == nullptr)
            throw RuleNotSet{};
        data->right.push_back(RIGHTASSOCIATE{getType(temp), temp});
        return *this;
    }

    template <typename... Vars>
    Rule &add(auto temp, Vars... v) requires(isRightAssociate<decltype(temp)>)
    {
        if (data == nullptr)
            throw RuleNotSet{};

        data->right.push_back(RIGHTASSOCIATE{getType(temp), temp});
        return add(v...);
    }

    Rule &add(const RIGHTASSOCIATE &r)
    {
        if (data == nullptr)
            throw RuleNotSet{};
        if (r == TERMINAL::EPSILON && getRightAssociates().size() != 0)
            throw 1;
        data->right.push_back(r);
        return *this;
    }
    Rule &add(const vector<RIGHTASSOCIATE> &r)
    {
        if (data == nullptr)
            throw RuleNotSet{};

        for (auto i : r)
            data->right.push_back(i);
        return *this;
    }

    RULESTYPE &operator|(const RULE &R) const;

    bool isNull() const
    {
        return getRightAssociates().size() == 1 && getRightAssociates()[0] == TERMINAL::EPSILON;
    }

    bool isUnitProduction() const
    {
        return getRightAssociates().size() == 1 && getLeft().getRules().size() == 1;
    }

    friend class RULESTYPE;
    friend class RULE;
};

template <typename... VV>
RULE add(auto x, VV... M) requires(isRightAssociate<decltype(x)>)
{
    RULE R;
    R->add(x, M...);
    return R;
}

RULE add(auto x) requires(isRightAssociate<decltype(x)>)
{
    RULE R;
    R->add(x);
    return R;
}

RULE add()
{
    RULE R;
    R->add();
    return R;
}

#endif // __RULE_HPP__