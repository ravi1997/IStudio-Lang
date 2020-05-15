#ifndef _RULES_HPP_
#define _RULES_HPP_ 1

#ifndef _RULE_HPP_
#include<rule.hpp>
#endif // !_RULE_HPP_

template<typename t>
class Rules{
    private:
        shared_ptr<vector<Rule<t>>> rules;
    public:
        Rules()=default;
        auto begin(){
            if(rules==nullptr)
                throw RulesNotFoundException{};
            return rules->begin();
        }
        auto end(){
            if (rules == nullptr)
                throw RulesNotFoundException{};
            return rules->end();
        }

        void add(Rule<t> r){
            if(rules==nullptr)
                rules=make_shared<vector<Rule<t>>>();
            rules->push_back(r);
        }

        auto size()const{
            if (rules == nullptr)
                throw RulesNotFoundException{};
            return rules->size();
        }
        Rule<t> &operator[](int i){
            return (*rules)[i];
        }

        Rules<t>& operator|(Rule<t> r){
            if(r.data->left==nullptr)
                r.data->left =(*rules)[0].data->left;
            add(r);
            return *this;
        } 
};

#endif // !_RULES_HPP_