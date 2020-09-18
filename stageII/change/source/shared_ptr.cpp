#ifndef __SHARED_PTR_CPP__
#define __SHARED_PTR_CPP__

#pragma once

#ifndef __SHARED_PTR_HPP__
#include <shared_ptr.hpp>
#endif

#ifndef _NONTERMINAL_HPP_
#include <nonterminal.hpp>
#endif

#ifndef _TERMINAL_HPP_
#include <terminal.hpp>
#endif

#include <rule.hpp>

namespace std
{
    RULESTYPE NONTERMINAL::getleftFactoring() const
    {
        //cout << *this << endl;
        //cout << getRules() << endl;
        //cout << getRules().getCommonRightAssociates().size() << endl;
        RULESTYPE result;
        RIGHTASSOCIATE rs = getRules().getCommonRightAssociates()[0];
        for (auto r : getRules())
        {
            if (r.getRight()[0] == rs)
                result.add(r);
        }

        return result;
    }

    NONTERMINAL::shared_ptr(string s)
        : data{new NONTERMINALTYPE(s)},
          count{new unsigned long int(1)}
    {
    }

    NONTERMINAL::~shared_ptr()
    {
        if (data != nullptr)
        {
            if (count != nullptr && *count == 1)
            {
                delete data;
                delete count;
            }
            else if (count != nullptr)
            {
                *count -= 1;
            }
        }
    }

    NONTERMINAL &NONTERMINAL::operator=(
        const NONTERMINAL &s)
    {
        if (data != nullptr)
        {
            if (count != nullptr && *count == 1)
            {
                delete data;
                delete count;
            }
            else if (count != nullptr)
            {
                *count -= 1;
            }
        }

        data = s.data;
        count = s.count;

        if (count != nullptr)
            *count += 1;

        return *this;
    }

    NONTERMINAL &NONTERMINAL::operator=(
        NONTERMINAL &&s)
    {
        if (data != nullptr)
        {
            if (count != nullptr && *count == 1)
            {
                delete data;
                delete count;
            }
            else if (count != nullptr)
            {
                *count -= 1;
            }
        }

        data = move(s.data);
        count = move(s.count);

        s.data = nullptr;
        s.count = nullptr;
        return *this;
    }

    NONTERMINALTYPE &NONTERMINAL::operator->() const
    {
        RULE r{*this};
        if (r == nullptr)
            throw BadAlloc{};
        data->add(r);
        return *data;
    }

    RULESTYPE &NONTERMINAL::getRules() const
    {
        return data->getRules();
    }

    string &NONTERMINAL::getName() const
    {
        return data->getName();
    }

    void NONTERMINAL::add(const RULE &r) const
    {
        data->add(r);
    }

    bool NONTERMINAL::operator==(const NONTERMINAL &x) const
    {
        if (data == nullptr || x.data == nullptr)
            return false;

        return *data == *x.data;
    }

    bool NONTERMINAL::operator<(const NONTERMINAL &x) const
    {
        if (data == nullptr || x.data == nullptr)
            return false;

        return *data < *x.data;
    }

    bool NONTERMINAL::hasLeftFactoring() const
    {
        for (auto r1 : getRules())
        {
            for (auto r2 : getRules())
            {
                if (r1 != r2)
                {
                    if (r1.getRight()[0] == r2.getRight()[0])
                        return true;
                }
            }
        }
        return false;
    }

    First NONTERMINAL::getFirst() const
    {
        First result;
        for (auto r : getRules())
            for (auto f : r.getFirst())
                result.push_back(f);

        return result;
    }

    TERMINAL::shared_ptr(string s, string p)
        : data{new TERMINALTYPE(s, p)}, count{new unsigned long int(1)} {}

    TERMINAL::shared_ptr(string s, TerminalType ty, string p)
        : data{new TERMINALTYPE(s, ty, p)}, count{new unsigned long int(1)} {}

    TERMINAL::~shared_ptr()
    {
        if (data != nullptr)
        {
            if (count != nullptr && *count == 1)
            {
                delete data;
                delete count;
            }
            else if (count != nullptr)
            {
                *count -= 1;
            }
        }
    }

    TERMINAL &TERMINAL::operator=(
        const TERMINAL &s)
    {
        if (data != nullptr)
        {
            if (count != nullptr && *count == 1)
            {
                delete data;
                delete count;
            }
            else if (count != nullptr)
            {
                *count -= 1;
            }
        }

        data = s.data;
        count = s.count;

        if (count != nullptr)
            *count += 1;

        return *this;
    }

    TERMINAL &TERMINAL::operator=(
        TERMINAL &&s)
    {
        if (data != nullptr)
        {
            if (count != nullptr && *count == 1)
            {
                delete data;
                delete count;
            }
            else if (count != nullptr)
            {
                *count -= 1;
            }
        }

        data = move(s.data);
        count = move(s.count);

        s.data = nullptr;
        s.count = nullptr;
        return *this;
    }

    bool TERMINAL::operator==(const TERMINAL &x) const
    {
        return *data == *x.data;
    }

    string &TERMINAL::getName() const
    {
        return data->getName();
    }

    const TERMINAL &TERMINAL::EPSILON = TERMINAL{"EPSILON", TerminalType::EPSILON, ""};
    const TERMINAL &TERMINAL::DOLLAR = TERMINAL{"DOLLAR", TerminalType::DOLLAR, ""};

    RULES::shared_ptr() : data{new RULESTYPE{}}, count{new unsigned long int(1)} {}
    RULES::~shared_ptr()
    {
        if (data != nullptr)
        {
            if (count != nullptr && *count == 1)
            {
                delete data;
                delete count;
            }
            else if (count != nullptr)
            {
                *count -= 1;
            }
        }
    }

    RULES &RULES::operator=(
        const RULES &s)
    {
        if (data != nullptr)
        {
            if (count != nullptr && *count == 1)
            {
                delete data;
                delete count;
            }
            else if (count != nullptr)
            {
                *count -= 1;
            }
        }

        data = s.data;
        count = s.count;

        if (count != nullptr)
            *count += 1;

        return *this;
    }

    RULES &RULES::operator=(
        RULES &&s)
    {
        if (data != nullptr)
        {
            if (count != nullptr && *count == 1)
            {
                delete data;
                delete count;
            }
            else if (count != nullptr)
            {
                *count -= 1;
            }
        }

        data = move(s.data);
        count = move(s.count);

        s.data = nullptr;
        s.count = nullptr;

        return *this;
    }

    bool RULES::operator==(const RULES &x) const
    {
        return *data == *x.data;
    }

    RULE::shared_ptr() : data{new RULETYPE{}}, count{new unsigned long int(1)} {}
    RULE::shared_ptr(const NONTERMINAL &n) : data{new RULETYPE{n}}, count{new unsigned long int(1)} {}
    RULE::~shared_ptr()
    {
        if (data != nullptr)
        {
            if (count != nullptr && *count == 1)
            {
                delete data;
                delete count;
            }
            else if (count != nullptr)
            {
                *count -= 1;
            }
        }
    }

    RULE &RULE::operator=(
        const RULE &s)
    {
        if (data != nullptr)
        {
            if (count != nullptr && *count == 1)
            {
                delete data;
                delete count;
            }
            else if (count != nullptr)
            {
                *count -= 1;
            }
        }

        data = s.data;
        count = s.count;

        if (count != nullptr)
            *count += 1;

        return *this;
    }

    RULE &RULE::operator=(
        RULE &&s)
    {
        if (data != nullptr)
        {
            if (count != nullptr && *count == 1)
            {
                delete data;
                delete count;
            }
            else if (count != nullptr)
            {
                *count -= 1;
            }
        }

        data = move(s.data);
        count = move(s.count);

        s.data = nullptr;
        s.count = nullptr;

        return *this;
    }

    bool RULE::isNull() const
    {
        if (data == nullptr)
            throw RuleNotSet{};
        return data->isNull();
    }

    bool RULE::isUnitProduction() const
    {
        if (data == nullptr)
            throw RuleNotSet{};
        return data->isUnitProduction();
    }

    NONTERMINAL &RULE::getLeft() const
    {
        if (data == nullptr)
            throw RuleNotSet{};
        return data->getLeft();
    }

    First RULE::getFirst() const
    {
        First result;

        for (auto r : getRight())
        {
            bool flag = false;
            auto f = r.getFirst();
            for (auto temp : f)
            {
                if (temp == TERMINAL::EPSILON)
                {
                    flag = true;
                }
                else
                    result.push_back(temp);
            }
            if (!flag)
                break;
        }

        if (auto t = getRight().back().getFirst(); find(t.begin(), t.end(), TERMINAL::EPSILON) != t.end())
            result.push_back(TERMINAL::EPSILON);

        return result;
    }

    bool RULE::operator<(const RULE &x) const
    {

        if (data == nullptr || x.data == nullptr)
            return false;
        if (getLeft() < x.getLeft())
            return true;
        if (getRight().size() < x.getRight().size())
            return true;

        auto r1 = getRight(), r2 = x.getRight();
        for (unsigned int i = 0; i < r1.size(); i++)
            if (r1[i] < r2[i])
                return true;
        return false;
    }

    vector<RIGHTASSOCIATE> &RULE::getRight() const
    {
        if (data == nullptr)
            throw RuleNotSet{};
        return data->getRightAssociates();
    }

    HANDLERULE RULE::getHandleRule() const
    {
        return HANDLERULE{*this};
    }

    vector<RIGHTASSOCIATE> RULE::getRightFrom(long unsigned int j) const
    {
        if (data == nullptr)
            throw RuleNotSet{};
        vector<RIGHTASSOCIATE> v;
        long unsigned int i = 0;

        for (auto r : getRight())
        {
            if (i < j)
            {
                i++;
                continue;
            }
            v.push_back(r);
        }

        return v;
    }

    size_t RULE::countOccurrence(const NONTERMINAL &p) const
    {
        if (data == nullptr)
            throw RuleNotSet{};
        size_t c = 0;
        for (auto r : getRight())
            if (r == p)
                c++;
        return c;
    }

    RULE RULE::removeFromOccurrence(const shared_ptr<NONTERMINALTYPE> &p, size_t j) const
    {
        RULE r{getLeft()};
        for (auto t : getRight())
            if (t != p)
                r->add(t);
            else if (j != 1)
            {
                r->add(t);
                j--;
            }

        for (auto t : p.getRules())
            if (t == r)
                return t;

        r->getLeft().data->add(r);

        return r;
    }

    bool RULE::operator==(const RULE &x) const
    {
        if (data == nullptr || x.data == nullptr)
            return false;
        return *data == *x.data;
    }

    RIGHTASSOCIATE::shared_ptr(RightAssociateType R, variant<NONTERMINAL, TERMINAL> V) : data{new RightAssociate{R, V}},
                                                                                         count{new unsigned long int(1)}
    {
    }

    RIGHTASSOCIATE::~shared_ptr()
    {
        if (data != nullptr)
        {
            if (count != nullptr && *count == 1)
            {
                delete data;
                delete count;
            }
            else if (count != nullptr)
            {
                *count -= 1;
            }
        }
    }

    RIGHTASSOCIATE &RIGHTASSOCIATE::operator=(
        const RIGHTASSOCIATE &s)
    {
        if (data != nullptr)
        {
            if (count != nullptr && *count == 1)
            {
                delete data;
                delete count;
            }
            else if (count != nullptr)
            {
                *count -= 1;
            }
        }

        data = s.data;
        count = s.count;

        if (count != nullptr)
            *count += 1;

        return *this;
    }

    RIGHTASSOCIATE &RIGHTASSOCIATE::operator=(
        RIGHTASSOCIATE &&s)
    {
        if (data != nullptr)
        {
            if (count != nullptr && *count == 1)
            {
                delete data;
                delete count;
            }
            else if (count != nullptr)
            {
                *count -= 1;
            }
        }

        data = move(s.data);
        count = move(s.count);

        s.data = nullptr;
        s.count = nullptr;

        return *this;
    }

    bool RIGHTASSOCIATE::operator==(const shared_ptr &x) const
    {
        if (isTerminal() && x.isTerminal())
        {
            return *this == x.getTerminal();
        }
        else if (isNonterminal() && x.isNonterminal())
        {
            return *this == x.getNonterminal();
        }
        else
            return false;
    }

    bool RIGHTASSOCIATE::operator!=(const shared_ptr &x) const
    {
        return !(*this == x);
    }

    bool RIGHTASSOCIATE::operator<(const shared_ptr &x) const
    {
        if (isTerminal())
        {
            if (x.isTerminal())
                return getTerminal().getName() < x.getTerminal().getName();
            else
                return getTerminal().getName() < x.getNonterminal().getName();
        }
        else
        {
            if (x.isTerminal())
                return getNonterminal().getName() < x.getTerminal().getName();
            else
                return getNonterminal().getName() < x.getNonterminal().getName();
        }
    }

    const NONTERMINAL &RIGHTASSOCIATE::getNonterminal() const
    {
        return ::getNonterminal(*data);
    }
    const TERMINAL &RIGHTASSOCIATE::getTerminal() const
    {
        return ::getTerminal(*data);
    }

    bool RIGHTASSOCIATE::operator==(const TERMINAL &x) const
    {
        return *data == x;
    }

    bool RIGHTASSOCIATE::operator!=(const TERMINAL &x) const
    {
        return *data != x;
    }

    bool RIGHTASSOCIATE::operator==(const NONTERMINAL &x) const
    {
        return *data == x;
    }

    bool RIGHTASSOCIATE::operator!=(const NONTERMINAL &x) const
    {
        return *data != x;
    }

    bool RIGHTASSOCIATE::isNonterminal() const
    {
        return isNonTerminal(*data);
    }
    bool RIGHTASSOCIATE::isTerminal() const
    {
        return ::isTerminal(*data);
    }

    First RIGHTASSOCIATE::getFirst() const
    {
        if (isTerminal())
            return getTerminal().getFirst();
        else
            return getNonterminal().getFirst();
    }

} // namespace std

#endif // __SHARED_PTR_CPP__