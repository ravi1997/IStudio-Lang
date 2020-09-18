#ifndef _RULES_CPP_
#define _RULES_CPP_

#include <rule.hpp>
#include <rules.hpp>

RULESTYPE &RULESTYPE::operator|(const RULE &r)
{
    if (data == nullptr)
        throw RulesNotSet{};

    r->setLeft((*data)[0].getLeft());

    data->push_back(r);
    return *this;
}

RULESTYPE RULESTYPE::removeAllOccurrence(const NONTERMINAL &n) const
{
    Rules result;

    for (auto r : *this)
    {
        RULE t{r.getLeft()};
        for (auto rs : r.getRight())
            if (rs != n)
                t->add(rs);
        result.add(t);
    }

    for (auto r : *this)
        r.getLeft().getRules().remove(r);

    for (auto r : result)
        r.getLeft().add(r);

    return result;
}

RULESTYPE RULESTYPE::replaceAllOccurrence(const RULE &n) const
{
    Rules result;

    for (auto r : *this)
    {
        RULE t{r.getLeft()};
        for (auto rs : r.getRight())
            if (rs != n.getLeft())
                t->add(rs);
            else
            {
                if (n.getRight()[0] != TERMINAL::EPSILON)
                    t->add(n.getRight()[0]);
            }
        result.add(t);
    }

    for (auto r : *this)
        r.getLeft().getRules().remove(r);

    for (auto r : result)
        r.getLeft().add(r);

    return result;
}
#endif // _RULES_CPP_