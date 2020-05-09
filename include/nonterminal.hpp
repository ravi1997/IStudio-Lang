#ifndef _NONTERMINAL_HPP_
#define _NONTERMINAL_HPP_ 1


#ifndef _TYPES_HPP_
#include<types.hpp>
#endif // !_TYPES_HPP_

#ifndef _RULE_HPP_
#include<rule.hpp>
#endif // !_RULE_HPP_

#ifndef _RULES_HPP_
#include<rules.hpp>
#endif // !_RULES_HPP_


template<typename t>
class NonTerminal{
    private:
        shared_ptr<Rules<t>> data;
        shared_ptr<string> name;
    public:
        NonTerminal(string s="",bool con=false):data{make_shared<Rules<t>>()},name{make_shared<string>(s)}{
            if(con && s=="Dollar"){
                data->rs->push_back(Rule<t>{this});
                (*data->rs)[data->rs->size()-1].getThis()->add(Terminal<t>::DOLLAR);
            }
        }
        ~NonTerminal(){}

        NonTerminal(const NonTerminal& n):data{n.data},name{n.name}{}
        NonTerminal(NonTerminal&& n):data{move(n.data)},name{(n.name)}{}

        NonTerminal& operator=(const NonTerminal& n){
           if(name==nullptr || *name=="")
                data=n.data;
            
            data = n.data;
            
            return *this;
        }

        NonTerminal& operator=(NonTerminal&& n){
            if(name==nullptr || *name=="")
                data=move(n.data);
        
            data = move(n.data);
            
            return *this;
        }


        bool operator==(NonTerminal n) const {
            return data == n.data;
        }

        bool operator!=(NonTerminal n) const {
            return !(*this==n);
        }

        bool operator<(NonTerminal n)const{
            return *name<*n.name;
        }

        Rule<t>* operator->(){
            if(data==nullptr)
                data=make_shared<Rules<t>>();
            data->rs->push_back(Rule<t>{this});
            return (*data->rs)[data->rs->size()-1].getThis();
        }

        Rules<t>& getRules()const{
            return *data;
        }

        First<t> getFirst()const{
            if(data==nullptr)
                throw RulesNotFoundException{};
            
            First<t> f;
            
            for(auto r:getRules()){
                auto temp=r.getFirst();
                f.insert(f.end(),temp.begin(),temp.end());
            }

            return f;
        }
        friend ostream& operator<<(ostream& o,NonTerminal nn){
            if(nn.name!=nullptr)
                o<<*nn.name;
            return o;
        }
        friend Logger& operator<<(Logger& o,NonTerminal nn){
            if(nn.name!=nullptr)
                o<<*nn.name;
            return o;
        }

        bool isDollar()const{
            return *this==NonTerminal::Dollar;
        }

        Clouser<t> getClouser()const{
            Clouser<t> f;

            for(auto r: getRules()){
                f.push_back(r.getHandleRule());
                if (r.getHandleRule().getNextSymbol().first == RightAssociateType::NONTERMINAL){
                    auto y = get<NonTerminal<t>>(r.getHandleRule().getNextSymbol().second).getClouser();
                    f.insert(f.end(), y.begin(),y.end());
                }
            }
            return f;
        }


        const static NonTerminal Dollar;

        friend class Rule<t>;
        friend class Rules<t>;
};


#endif // !_NONTERMINAL_HPP_