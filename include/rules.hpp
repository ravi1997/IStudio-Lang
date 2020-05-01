#ifndef _RULES_HPP_
#define _RULES_HPP_ 1

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif // !_TYPES_HPP_

template<typename t>
class Rules{
    private:
        shared_ptr<vector<Rule<t>>> rs;
    public:
        Rules():rs{make_shared<vector<Rule<t>>>()}{}
        
        Rules(const Rules& r):rs{r.rs}{}
        Rules(Rules&& r):rs{move(r.rs)}{}

        Rules& operator=(const Rules& r){
            rs=r.rs;
            return *this;
        }
        
        Rules& operator=(Rules&& r){
            rs=move(r.rs);
            return *this;
        }

        auto begin(){
            return rs->begin();
        }

        auto end(){
            return rs->end();
        }



        auto begin()const{
            return rs->begin();
        }

        auto end()const{
            return rs->end();
        }


        Rules& operator|(const Rule<t> r){
            if(r.data->left==nullptr)
                r.data->left=(*rs)[0].data->left;
            rs->push_back(r);
            return *this;
        }


        void add(const Rule<t> r){
            rs->push_back(r);
        }

        friend class Rule<t>;
        friend class NonTerminal<t>;

        
};

#endif // !_RULES_HPP_