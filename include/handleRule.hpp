#ifndef _HANDLE_RULE_HPP_
#define _HANDLE_RULE_HPP_ 1

#ifndef _RULE_HPP_
#include <rule.hpp>
#endif // !_RULE_HPP_

template <typename t>
class HandleRule
{
    struct Data
    {
        vector<RightAssociate<t>> beforeHandle, AfterHandle;
        //vector<function<t(const Parser<t> &)>> action;
        NonTerminal<t> *left = nullptr;
        Data() = default;
        Data(NonTerminal<t> *l, vector<RightAssociate<t>> b, vector<RightAssociate<t>> a) : beforeHandle{b},
                                                                                            AfterHandle{a},
                                                                                            left{l}
        {
        }

        Data(const Data &d) : left{d.left}
        {
            for (auto x : d.beforeHandle)
                beforeHandle.emplace_back(x);
            for (auto x : d.AfterHandle)
                AfterHandle.push_back(x);
        }
        Data(const Data &&d) : beforeHandle{move(d.beforeHandle)},
                               AfterHandle{move(d.AfterHandle)},
                               left{move(d.left)}
        {
        }
        Data &operator=(const Data &d)
        {

            for (auto x : d.beforeHandle)
                beforeHandle.emplace_back(x);
            for (auto x : d.AfterHandle)
                AfterHandle.push_back(x);
        }
        ~Data() = default;
        bool operator==(const Data d) const
        {
            if (left != d.left || beforeHandle.size() != d.beforeHandle.size() || AfterHandle.size() != d.AfterHandle.size())
                return false;

            for (int j = 0, i = beforeHandle.size(); j < i; j++)
                if (beforeHandle[j] != d.beforeHandle[j])
                    return false;

            for (int j = 0, i = AfterHandle.size(); j < i; j++)
                if (AfterHandle[j] != d.AfterHandle[j])
                    return false;

            return true;
        }

        bool operator!=(const Data d) const
        {
            return !(*this == d);
        }
    };
    shared_ptr<Data> data;

public:
    HandleRule() = default;
    HandleRule(NonTerminal<t> *l, vector<RightAssociate<t>> b, vector<RightAssociate<t>> a) : data{make_shared<Data>(l, b, a)} {}
    vector<Terminal<t>> calculateLookAhead() const
    {
        if (data == nullptr)
            return {};
        if (data->AfterHandle.size() == 0)
            return {};
        if (data->AfterHandle[0].first == RightAssociateType::NONTERMINAL)
            return get<NonTerminal<t>>(getNextSymbol().second).getFirst();
        else
            return get<Terminal<t>>(getNextSymbol().second).getFirst();
    }
    RightAssociate<t> &getNextSymbol() const
    {
        if (data == nullptr)
            throw RulesNotFoundException{};
        if (data->AfterHandle.size() == 0)
            throw Empty{};
        return data->AfterHandle[0];
    }

    bool isGoto() const
    {
        try
        {
            bool h = (getNextSymbol().first == RightAssociateType::NONTERMINAL);
            return h;
        }
        catch (...)
        {
            return false;
        }
    }

    bool isAction() const
    {
        return !isGoto();
    }

    State<t> getState(Grammar<t> g, LookAheads<t> ts)
    {
        State<t> I;
        I.push_back(pair{*this, ts});

        if (data->AfterHandle.size() > 0)
        {
            auto [x, y] = data->AfterHandle[0];
            if (x == RightAssociateType::NONTERMINAL)
            {
                for (auto r : get<NonTerminal<t>>(y).getRules())
                    if (find(I.begin(), I.end(), pair{r.getHandleRule(), getLookheads()}) == I.end())
                    {
                        LookAheads<t> ls = getLookheads();
                        if (find(ls.begin(), ls.end(), Terminal<t>::EPSILON) != ls.end())
                        {
                            ls.erase(find(ls.begin(), ls.end(), Terminal<t>::EPSILON));
                            ls.insert(ls.end(), ts.begin(), ts.end());
                        }
                        I.push_back(pair{r.getHandleRule(), ls});
                        I.insert(I.end(), r.getHandleRule().getState(g, getLookheads()).begin(), r.getHandleRule().getState(g, getLookheads()).end());
                    }
            }
        }
        return I;
    }

    LookAheads<t> getLookheads() const
    {
        LookAheads<t> ls;

        if (data->AfterHandle.size() > 1)
        {
            size_t i = 1;
            do
            {

                ls.insert(ls.end(), getFirst(data->AfterHandle[i]).begin(), getFirst(data->AfterHandle[i]).end());

                if (find(ls.begin(), ls.end(), Terminal<t>::EPSILON) == ls.end())
                    break;
                else
                    ls.erase(find(ls.begin(), ls.end(), Terminal<t>::EPSILON));
            } while (i < ls.size());
        }

        return (ls.size() > 0) ? ls : LookAheads<t>{Terminal<t>::DOLLAR};
    }

    HandleRule getShiftedHandleRule() const
    {
        vector<RightAssociate<t>> x = data->beforeHandle;
        vector<RightAssociate<t>> y = data->AfterHandle;
        x.push_back(y[0]);
        y.erase(y.begin());
        return HandleRule{data->left, x, y};
    }

    bool operator==(const HandleRule h) const
    {
        return data != nullptr &&
               h.data != nullptr &&
               *data == *h.data;
    }
    bool operator!=(const HandleRule h) const
    {
        return data != nullptr &&
               h.data != nullptr &&
               !(*this == h);
    }
};

template <typename t>
vector<NonTerminal<t>> getGoto(State<t> I)
{
    vector<NonTerminal<t>> f;
    for (auto x : I)
    {
        if (x.first.isGoto())
        {
            try
            {
                f.push_back(get<NonTerminal<t>>(x.first.getNextSymbol().second));
            }
            catch (...)
            {
            }
        }
    }
    return f;
}

template <typename t>
vector<Terminal<t>> getAction(State<t> I)
{
    vector<Terminal<t>> f;
    for (auto x : I)
    {
        if (x.first.isAction())
        {
            try
            {
                f.push_back(get<Terminal<t>>(x.first.getNextSymbol().second));
            }
            catch (...)
            {
            }
        }
    }
    return f;
}

template <typename t>
State<t> getNextState(Grammar<t> g, State<t> I, NonTerminal<t> n)
{
    State<t> f;
    for (auto x : I)
    {
        try
        {
            if (x.first.getNextSymbol() == n)
            {
                f.push_back(x);
                auto h = x.first.getShiftedHandleRule();
                State<t> temp = h.getState(g, x.first.getLookheads());
                f.insert(f.end(), temp.begin(), temp.end());
            }
        }
        catch (...)
        {
        }
    }
    return f;
}

template <typename t>
State<t> getNextState(Grammar<t> g, State<t> I, Terminal<t> n)
{
    State<t> f;
    for (auto x : I)
    {
        if (x.first.getNextSymbol() == n)
        {
            f.push_back(x);
            auto h = x.first.getShiftedHandleRule();
            State<t> temp = h.getState(g, x.first.getLookheads());
            f.insert(f.end(), temp.begin(), temp.end());
        }
    }
    return f;
}

template <typename t>
SR getSR(State<t> I)
{
    bool s = false, r = false;

    for (auto z : I)
    {
        try
        {
            z.first.getNextSymbol();
            s = true;
        }
        catch (...)
        {
            r = true;
        }
    }
    if (s && r)
        throw ShiftReduce{};
    else if (s)
        return SR::SHIFT;
    else
        return SR::REDUCE;
}

template<typename t>
bool operator<(const State<t> a,const State<t> b){
    if(a.size()!=b.size())
        return false;
    for(size_t i=0,j=b.size();i<j;i++)
        if(a[i].first!=b[i].first)
            return true;
    
    return false;
}

#endif // !_HANDLE_RULE_HPP_