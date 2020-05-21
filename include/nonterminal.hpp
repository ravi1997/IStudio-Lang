#ifndef _NON_TERMINAL_HPP_
#define _NON_TERMINAL_HPP_ 1

#ifndef _TYPES_HPP_
#include <types.hpp>
#endif // !_TYPES_HPP_

template<typename t>
class NonTerminal{
    private:

        shared_ptr<Rules<t>> data;
        shared_ptr<string> name;

    public:

        NonTerminal(string s=""):data{make_shared<Rules<t>>()},name{make_shared<string>(s)}{}
        NonTerminal(const NonTerminal &n) : data{n.data}, name{n.name} {}
        NonTerminal(const NonTerminal &&n) : data{move(n.data)}, name{move(n.name)} {}

        NonTerminal& operator=(const NonTerminal& n){
            data=n.data;
            name=n.name;
            return *this;
        }
        NonTerminal &operator=(const NonTerminal &&n)
        {
            data = move(n.data);
            name = move(n.name);
            return *this;
        }


        ~NonTerminal()=default;

        bool operator==(const NonTerminal& n) const{
            return data != nullptr &&
                   n.data != nullptr &&
                   data == n.data;
        }

        bool operator!=(const NonTerminal& n) const{
            return data != nullptr &&
                   n.data != nullptr &&
                   data != n.data;
        }

        bool operator<(const NonTerminal& tt) const
        {
            return *this != tt;
        }

        Rule<t>* operator->(){
            if(data==nullptr)
                data=make_shared<Rules<t>>();
        
            Rule<t> r{this};
            data->add(r);
            return (*data)[data->size()-1].getThis();
        }

        First<t> getFirst()const{
            return data->getFirst();
        }

        Rules<t>& getRules()const{
            return *data;
        }


        friend Logger& operator<<(Logger& l,NonTerminal& n){
            if(n.name!=nullptr)
                l<<*n.name;
            return l;
        }

        friend ostream &operator<<(ostream &l, NonTerminal &n)
        {
            if (n.name != nullptr)
                l << *n.name;
            return l;
        }
        
        bool operator==(const Terminal<t> n) const
        {
            return false;
        }

        friend class Rule<t>;
        friend class Rules<t>;
};

#endif // !_NON_TERMINAL_HPP_