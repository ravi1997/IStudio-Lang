#ifndef _GRAMMAR_HPP_
#define _GRAMMAR_HPP_ 1

#pragma once

#include <types.hpp>
#include <shared_ptr.hpp>
#include <rule.hpp>
#include <rules.hpp>

template <>
class Grammar<PARSERTYPE>
{
    struct Data
    {
        vector<TERMINAL> terminals;
        vector<NONTERMINAL> nonterminals;
        NONTERMINAL start;
        RULESTYPE rules;

        Data(vector<TERMINAL> ts, vector<NONTERMINAL> ns, NONTERMINAL s, bool val = true) : terminals{move(ts)}, nonterminals{move(ns)}, start{move(s)}
        {
            if (val)
            {
                for (auto nss : nonterminals)
                    for (auto r : nss.getRules())
                        rules.add(r);
            }
        }
        Data(const Data &d) : terminals{d.terminals}, nonterminals{d.nonterminals}, start{d.start}, rules{d.rules} {}
        Data(Data &&d) : terminals{move(d.terminals)}, nonterminals{move(d.nonterminals)}, start{move(d.start)}, rules{move(d.rules)} {}
        Data &operator=(const Data &d)
        {
            terminals = d.terminals;
            nonterminals = d.nonterminals;
            start = d.start;
            rules = d.rules;
            return *this;
        }

        Data &operator=(Data &&d)
        {
            terminals = move(d.terminals);
            nonterminals = move(d.nonterminals);
            start = move(d.start);
            rules = move(d.rules);
            return *this;
        }
    };

    shared_ptr<Data> data;

public:
    Grammar(vector<NONTERMINAL> ns, vector<TERMINAL> ts, NONTERMINAL s, bool val = true) : data{make_shared<Data>(ts, ns, s, val)} {}

    Grammar(const Grammar &g) : data{g.data} {}
    Grammar(Grammar &&g) : data{move(g.data)} {}

    Grammar &operator=(const Grammar &g)
    {
        data = g.data;
        return *this;
    }

    Grammar &operator=(Grammar &&g)
    {
        data = move(g.data);
        return *this;
    }

    ~Grammar() {}

    vector<TERMINAL> &getTerminals() const
    {
        return data->terminals;
    }

    vector<NONTERMINAL> &getNonTerminals() const
    {
        return data->nonterminals;
    }

    NONTERMINAL &getStart() const
    {
        return data->start;
    }
    RULESTYPE &getRules() const
    {
        return data->rules;
    }
    void setRules(RULESTYPE &r)
    {
        data->rules = r;
    }

    void remove(const RULE &r) const
    {
        getRules().remove(r);
        r.getLeft().getRules().remove(r);
    }

    bool hasNull() const
    {
        for (auto r : getRules())
        {
            if (r.isNull())
                return true;
        }
        return false;
    }

    bool hasUnitProduction() const
    {
        for (auto r : getRules())
        {
            if (r.isUnitProduction())
                return true;
        }
        return false;
    }

    bool hasLeftFactoring() const
    {
        for (auto n : getNonTerminals())
            if (n.hasLeftFactoring())
                return true;
        return false;
    }

    RULESTYPE getNullProductions() const
    {
        RULESTYPE result;
        for (auto r : getRules())
            if (r.isNull())
                result.add(r);

        return result;
    }

    RULESTYPE getUnitProductions() const
    {
        RULESTYPE result;
        for (auto r : getRules())
            if (r.isUnitProduction())
                result.add(r);

        return result;
    }

    Grammar reduceNull(const RULE &r) const
    {
#ifdef DEBUG
        cout << "Debug : Reduce Null for : " << r << endl;
        cout << "Debug : NonTerminal rules : " << r.getLeft().getRules().size() << endl;
#endif
        if (r.getLeft().getRules().size() != 1)
        {
#ifdef DEBUG
            cout << "Debug : inside rules greater than 1" << endl
                 << endl;
#endif
            remove(r); //remove works fine

            RULESTYPE rr = getRules().returnReduce(r);
            Grammar g{getNonTerminals(), getTerminals(), getStart(), false};
            g.setRules(rr);
#ifdef DEBUG
            cout << "Debug : " << endl;
            cout << g << endl
                 << endl;
#endif // DEBUG
            return g;
        }
        else
        {
#ifdef DEBUG
            cout << "Debug : inside rules equals to 1" << endl;
#endif
            if (r.getLeft() == getStart())
                return reduce(false);
            auto ns = getNonTerminals();
            if (auto it = find(ns.begin(), ns.end(), r.getLeft()); it != ns.end())
                ns.erase(it);
            else
                return *this;

            Grammar g{ns, getTerminals(), getStart(), true};

            RULESTYPE rs = g.getRules().removeAllOccurrence(r.getLeft());

            g.setRules(rs);

#ifdef DEBUG
            cout << "Debug : " << endl;
            cout << g << endl
                 << endl;
#endif // DEBUG

            return g;
        }
    }

    Grammar removeNull() const
    {
        if (hasNull())
        {
            RULESTYPE rs = getNullProductions();
            RULE r = rs[0]; //get the first production
#ifdef DEBUG
            cout << "Debug : Reducing from removeNull : " << endl
                 << r << endl;
#endif
            return reduceNull(r).removeNull();
        }
        else
            return *this;
    }

    Grammar reduceUnit(const RULE &r) const
    {
        if (r.getLeft() == getStart())
            return reduce(false);
        auto ns = getNonTerminals();
        if (auto it = find(ns.begin(), ns.end(), r.getLeft()); it != ns.end())
            ns.erase(it);
        else
            return *this;

        Grammar g{ns, getTerminals(), getStart(), true};

        RULESTYPE rs = g.getRules().replaceAllOccurrence(r);

        g.setRules(rs);
        return g;
    }

    Grammar reduceleftFactoring(RULESTYPE &rs) const
    {
        static unsigned int count = 0;
        auto v = rs.getCommonRightAssociates();
        for (auto r : rs)
            remove(r);

        NONTERMINAL tdash{rs[0].getLeft().getName() + to_string(count++)};

        RULE r{rs[0].getLeft()};
        r->add(v);
        r->add(tdash);

        r.getLeft().add(r); // will create rule

        for (auto r1 : rs)
        {
            auto v1 = r1.getRightFrom(v.size() + 1); //returns EPSILON if doesn't find anything

            RULE r11{tdash};
            bool flag = true;

            if (v1.size() != 0)
            {
                r11->add(v1);

                for (auto r2 : tdash.getRules())
                    if (r2 == r11)
                    {
                        flag = false;
                        break;
                    }

                if (flag)
                    tdash->add(v1);
            }
            else
            {
                r11->add();

                for (auto r2 : tdash.getRules())
                    if (r2 == r11)
                    {
                        flag = false;
                        break;
                    }

                if (flag)
                    tdash->add();
            }
        }

        vector<NONTERMINAL> ns = getNonTerminals();
        ns.push_back(tdash);

        return Grammar{ns, getTerminals(), getStart(), true};
    }

    Grammar removeUnitProduction() const
    {
        if (hasUnitProduction())
        {
            RULESTYPE rs = getUnitProductions();
            RULE r = rs[0]; //get the first production
            //cout << r << endl;
            return reduceUnit(r).removeUnitProduction();
        }
        else
            return *this;
    }

    Grammar removeLeftFactoring() const
    {
        //cout << *this << endl;
        if (hasLeftFactoring())
        {
            RULESTYPE rs;
            for (auto n : getNonTerminals())
            {
                if (n.hasLeftFactoring())
                    rs = n.getleftFactoring();
            }
            return reduceleftFactoring(rs).removeLeftFactoring();
        }
        else
            return *this;
    }

    Grammar reduce(bool flag = true) const
    {
#ifdef DEBUG
        cout << "Debug : Inside Reduce" << endl;
#endif // DEBUG

        if (flag && hasNull())
            return removeNull().reduce(flag);
        else if (hasUnitProduction())
            return removeUnitProduction().reduce(flag);
        else if (hasLeftFactoring())
            return removeLeftFactoring().reduce(false);
        else
            return *this;
    }

    template <typename Stream>
    friend Stream &operator<<(Stream &o, Grammar g)
    {
        o << "NonTerminals : ";
        for (auto n : g.getNonTerminals())
            o << n << " ";
        o << endl;
        o << "Terminals : ";
        for (auto n : g.getTerminals())
            o << n << " ";
        o << endl;

        o << "Start Symbol : " << g.getStart() << endl;

        o << "Rules :" << endl;
        o << g.getRules();
        return o;
    }
};

#endif // !_GRAMMAR_HPP_