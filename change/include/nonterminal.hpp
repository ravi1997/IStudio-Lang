#ifndef _NONTERMINAL_HPP_
#define _NONTERMINAL_HPP_ 1

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif // !_TYPES_HPP_



template<typename t>
class NonTerminal{
    private:
        
        shared_ptr<string> name;
        shared_ptr<Rules<t>> rules;
        
    public:
        NonTerminal(string name):
                        name{make_shared<string>(name)},
                        rules{make_shared<Rules<t>>()}
                        {}

        NonTerminal(const NonTerminal & n):
                        name{n.name},
                        rules{n.rules}
                        {}

        NonTerminal(const NonTerminal && n):
                        name{move(n.name)},
                        rules{move(n.rules)}
                        {}
        
        NonTerminal& operator=(const NonTerminal& n){
            name=n.name;
            rules=n.rules;
            return *this;
        }
        
        NonTerminal& operator=(const NonTerminal&& n)
        {
            name = move(n.name);
            rules = move(n.rules);
            return *this;
        }

        bool operator==(const NonTerminal n)const noexcept{
            return name!=nullptr    && 
                   n.name!=nullptr  && 
                   rules!=nullptr   && 
                   n.rules!=nullptr && 
                   name==n.name     && 
                   rules==n.rules;
        }
        
        bool operator!=(const NonTerminal n) const noexcept
        {
            return name != nullptr    &&
                   n.name != nullptr  &&
                   rules != nullptr   &&
                   n.rules != nullptr &&
                   *name != *n.name     &&
                   *rules != *n.rules;
        }

        First<t> getFirst()const{
            if(rules==nullptr)
                throw RulesNotFoundException{*this};
            First<t> f;
            for(auto& r: *rules)
                f.insert(f.end(),r.getFirst().begin(),r.getFirst().end());
            return f;
        }

        Follow<t> getFollow(const Grammar<t>& g)const{
            return g.getFollow(*this);
        }

        Rule<t>* operator->(){
            if(rules==nullptr)
                rules=make_shared<Rules<t>>();
            rules->add(Rule<t>{this});
            return (*rules)[rules->size()-1].getThis();
        }
        Rules<t>& getRules()const{
            if(rules==nullptr)
                throw RulesNotFoundException{};
            return *rules;
        }
        bool operator==(Terminal<t>){
            return false;
        }

        friend ostream& operator<<(ostream& o,NonTerminal n){
            if(n.name==nullptr)
            return o;
            o<<*n.name;
            return o;
        }

        friend class Rule<t>;
        friend class Rules<t>;
};

#endif // !_NONTERMINAL_HPP_