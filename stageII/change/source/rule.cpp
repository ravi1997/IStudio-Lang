#ifndef __RULE_CPP__
#define __RULE_CPP__

#pragma once

#include <shared_ptr.hpp>
#include <rule.hpp>
#include <rules.hpp>

RULESTYPE &RULETYPE::operator|(const RULE &R) const
{
    if (data == nullptr)
        throw RuleNotSet{};
    R->data->left = data->left;
    getLeft().getRules().add(R);
    return getLeft().getRules();
}

#endif // __RULE_CPP__