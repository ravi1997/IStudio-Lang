#ifndef _RULES_HPP_
#define _RULES_HPP_

#ifndef __TYPES_HPP__
#include <types.hpp>
#endif

#ifndef __RULE_HPP__
#include <rule.hpp>
#endif

template <>
class Rules<PARSERTYPE>
{
private:
    shared_ptr<vector<RULE>> data;

public:
    Rules() : data{make_shared<vector<RULE>>()} {}
    Rules(const Rules &ds) : data{ds.data} {}
    Rules(const Rules &&ds) : data{move(ds.data)} {}
    Rules &operator=(const Rules &rs)
    {
        data = rs.data;
        return *this;
    }
    Rules &operator=(Rules &&rs)
    {
        data = move(rs.data);
        return *this;
    }

    ~Rules()
    {
        data.reset();
    }

    void add(const RULE &r) const
    {
        if (data == nullptr)
            throw RulesNotSet{};
        data->emplace_back(r);
    }

    RULE &back() const
    {
        if (data == nullptr)
            throw RulesNotSet{};
        return data->back();
    }

    auto begin()
    {
        if (data == nullptr)
            throw RulesNotSet{};
        return data->begin();
    }
    auto end()
    {
        if (data == nullptr)
            throw RulesNotSet{};
        return data->end();
    }

    auto begin() const
    {
        if (data == nullptr)
            throw RulesNotSet{};
        return data->begin();
    }
    auto end() const
    {
        if (data == nullptr)
            throw RulesNotSet{};
        return data->end();
    }

    auto size() const
    {
        if (data == nullptr)
            throw RulesNotSet{};
        return data->size();
    }

    auto &operator[](size_t i) const
    {
        if (data == nullptr)
            throw RulesNotSet{};
        if (size() == 0)
            throw RulesEmpty{};
        return (*data)[i];
    }

    void add(const Rules &rs) const
    {
        if (data == nullptr)
            throw RulesNotSet{};
        for (auto r : rs)
            data->push_back(r);
    }

    void remove(const RULE &r) const
    {
        if (data == nullptr)
            throw RulesNotSet{};
        auto b = begin();
        auto e = end();

        auto i = find(b, e, r);
        if (i != e)
            data->erase(i);
        else if (size() != 0)
            throw 1;
    }

    template <typename Stream>
    friend Stream &operator<<(Stream &o, Rules rs)
    {
        for (RULE &r : rs)
            o << r << endl;
        return o;
    }

    void removeAll()
    {
        if (data == nullptr)
            throw RulesNotSet{};
        data.reset();
    }

    Rules &operator|(const RULE &r);

    Rules returnReduceInner(const RULE &r) const
    {
        Rules rs;
        if (size() > 0)
        {
            for (auto i : *this)
            {
                if (i.countOccurrence(r.getLeft()) > 0)
                {
                    for (size_t j = i.countOccurrence(r.getLeft()); j > 0; j--)
                    {
                        rs.add(i.removeFromOccurrence(r.getLeft(), j));
                    }
                }
            }
            if (rs.size() > 0)
                rs.add(rs.returnReduceInner(r));
        }
        return rs;
    }

    Rules returnReduce(const RULE &r) const
    {
        Rules rs;

        for (auto r1 : *this)
            rs.add(r1);

        Rules temp = returnReduceInner(r);

        for (auto r1 : temp)
            rs.add(r1);

        return rs;
    }

    bool operator==(const Rules &rs) const
    {
        if (size() != rs.size())
            return false;

        for (size_t i = 0, j = size(); i < j; i++)
            if ((*this)[i] != rs[i])
                return false;

        return true;
    }

    Rules removeAllOccurrence(const NONTERMINAL &n) const;
    Rules replaceAllOccurrence(const RULE &n) const;

    vector<RIGHTASSOCIATE> getCommonRightAssociates() const
    {
        //cout << "Debug : inside getCommonRightAssociates" << endl;

        vector<RIGHTASSOCIATE> result;

        for (auto r : *this)
        {
            //cout << "For " << r << endl;
            vector<RIGHTASSOCIATE> v = r.getRight();

            auto min = [](auto i, auto j) requires is_same_v<decltype(i), decltype(j)>
            {
                return (i < j) ? i : j;
            };

            for (auto r1 : *this)
            {
                // cout << "against " << r1 << endl;
                if (r1 == r)
                    continue;
                if (r1.getRight()[0] == v[0])
                {
                    //cout << "found equivalence " << endl;
                    auto rs = r1.getRight();
                    long unsigned int i = 0, j = min(rs.size(), v.size());
                    //cout << "i : " << i << "j : " << j << endl;
                    for (; i < j; i++)
                    {
                        if (rs[i] != v[i])
                            break;
                    }

                    if (i != j)
                    {
                        auto e = v.size();
                        while (i != e)
                        {
                            v.pop_back();
                            i++;
                        }
                    }
                }
            }
            //cout << "v.size : " << v.size() << " result.size : " << result.size() << endl;
            if (result.size() == 0 || v.size() < result.size())
                result = move(v);
        }

        return result;
    }
    friend class GRAMMAR;
};

#endif // _RULES_HPP_