#ifndef __PARSER_H__
#define __PARSER_H__

#include <grammar.hpp>
#include <handlerule.hpp>
template <>
class Parser<PARSERTYPE>
{
private:
    GRAMMAR grammar;
    vector<State> states;
    ParseringTable table;

public:
    Parser(const GRAMMAR &g) : grammar{g} {}

    State getClosure(const State &s) const
    {
        State result;

        for (auto temp : s)
            result.push_back(temp);

        for (auto [r, l] : s)
        {
            if (auto n = r.getNextSymbol(); n.isNonterminal())
            {
                auto y = n.getNonterminal();
                for (auto nr : y.getRules())
                    if (StateRule rs = StateRule{nr.getHandleRule(), r.getLookAheads(l)}; find(result.begin(), result.end(), rs) != result.end())
                        result.push_back(rs);
            }
        }
        if (result == s)
            return result;
        else
            return getClosure(result);
    }

    State Goto(State I, RIGHTASSOCIATE x) const
    {
        State j;
        for (auto [r, l] : I)
        {
            if (r.getNextSymbol() == x)
                j.push_back({r.shiftedRule(), l});
        }
        return getClosure(j);
    }

    void init()
    {
    }
};

#endif // __PARSER_H__