#ifndef _HANDLE_RULE_HPP_
#define _HANDLE_RULE_HPP_ 1

#ifndef _RULE_HPP_
#include<rule.hpp>
#endif // !_RULE_HPP_

template<typename t>
class HandleRule{
    struct Data{
        vector<RightAssociate<t>> beforeHandle,AfterHandle;
        //vector<function<t(const Parser<t> &)>> action;
        NonTerminal<t> *left = nullptr;
        Data()=default;
        Data(NonTerminal<t> * l,vector<RightAssociate<t>> b, vector<RightAssociate<t>> a) : 
                        beforeHandle{b},
                        AfterHandle{a},
                        left{l}
                        {}
        
        Data(const Data& d):
                        left{d.left}
                        {
                            for (auto x : d.beforeHandle)
                                beforeHandle.emplace_back(x);
                            for (auto x : d.AfterHandle)
                                AfterHandle.push_back(x);
                        }
        Data(const Data&& d):
                        beforeHandle{move(d.beforeHandle)},
                        AfterHandle{move(d.AfterHandle)},
                        left{move(d.left)}
                        {}
        Data& operator=(const Data& d){
            
            for (auto x : d.beforeHandle)
                beforeHandle.emplace_back(x);
            for (auto x : d.AfterHandle)
                AfterHandle.push_back(x);
        }
        ~Data()=default;        
    };
    shared_ptr<Data> data;
    public:
        HandleRule()=default;
        HandleRule(NonTerminal<t> *l,vector<RightAssociate<t>> b, vector<RightAssociate<t>> a) : data{make_shared<Data>(l,b,a)} {}
        vector<Terminal<t>> calculateLookAhead()const{
            if(data==nullptr)
                return {};
            if (data->AfterHandle.size()==0)
                return {};
            if (data->AfterHandle[0].first == RightAssociateType::NONTERMINAL)
                return get<NonTerminal<t>>(getNextSymbol().second).getFirst();
            else
                return get<Terminal<t>>(getNextSymbol().second).getFirst();
        }
        RightAssociate<t>& getNextSymbol()const{
            return data->AfterHandle[0];
        }
 };

#endif // !_HANDLE_RULE_HPP_