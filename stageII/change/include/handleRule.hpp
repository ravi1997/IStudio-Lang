#ifndef __HANDLERULE_H__
#define __HANDLERULE_H__

#pragma once
#include <types.hpp>

template <>
class HandleRule<FlowControl>
{
    struct Data
    {
        NONTERMINAL left;
        vector<RIGHTASSOCIATE> before, after;

        Data(NONTERMINAL l, vector<RIGHTASSOCIATE> b, vector<RIGHTASSOCIATE> a) : left{l}
        {
            for (auto r : b)
                before.push_back(r);

            for (auto r : a)
                before.push_back(r);
        }

        Data(const Data &x) : left{x.left}
        {
            for (auto r : x.before)
                before.push_back(r);

            for (auto r : x.after)
                before.push_back(r);
        }
        Data(Data &&x) : left{move(x.left)}, before{move(x.before)}, after{x.after} {}
        ~Data() = default;
    };
    shared_ptr<Data> data = nullptr;

public:
    HandleRule() = default;
    HandleRule(const RULE &r) : data{make_shared<Data>(r.getLeft(), vector<RIGHTASSOCIATE>{}, r.getRight())} {}
    HandleRule(NONTERMINAL l, vector<RIGHTASSOCIATE> b, vector<RIGHTASSOCIATE> a) : data{make_shared<Data>(l, b, a)} {}
    HandleRule(const HandleRule &x) : data{x.data} {}
    HandleRule(HandleRule &&x) : data{move(x.data)} {}
    HandleRule &operator=(const HandleRule &h)
    {
        data = h.data;
        return *this;
    }
    HandleRule &operator=(HandleRule &&h)
    {
        data = move(h.data);
        return *this;
    }
    ~HandleRule() = default;

    RIGHTASSOCIATE getNextSymbol() const
    {
        if (data != nullptr)
        {
            if (data->after.size() != 0)
                return data->after[0];
            else
                return RIGHTASSOCIATE{RightAssociateType::TERMINALOBJ, TERMINAL::EPSILON};
        }
        else
            throw HandleRuleException{};
    }

    LookAheads getLookAheads(const LookAheads &l) const
    {
        if (data != nullptr)
        {
            if (data->after.size() > 1)
            {
                bool flag = true;
                LookAheads result;
                for (auto r : data->after)
                {
                    if (flag)
                    {
                        flag = false;
                        continue;
                    }
                    auto r1 = r.getFirst();
                    for (auto temp : r1)
                        result.push_back(temp);
                }
                return result;
            }
            else
                return l;
        }
        else
            throw HandleRuleException{};
    }

    HandleRule shiftedRule() const
    {
        auto b = data->before;
        b.push_back(getNextSymbol());

        auto a = data->after;
        a.erase(a.begin());

        return HandleRule{data->left, b, a};
    }

    bool operator==(const HandleRule &h) const
    {
        if (data == nullptr || h.data == nullptr)
            return false;
        return data->left == h.data->left && data->before == h.data->before && data->after == h.data->after;
    }
};

#endif // __HANDLERULE_H__