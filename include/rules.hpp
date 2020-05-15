#ifndef _RULES_HPP_
#define _RULES_HPP_ 1

#ifndef _TYPES_HPP_
#include <types.hpp>
#endif // !_TYPES_HPP_

template<typename t>
class Rules{
    private:
        shared_ptr<vector<Rule<t>>> data;

    public:

    Rules():data{make_shared<vector<Rule<t>>>()}{}
    Rules(const Rules &d) : data{d.data} {}
    Rules(const Rules &&d) : data{move(d.data)} {}
    Rules& operator=(const Rules &d){
        data=d.data;
        return *this;
    }
    Rules &operator=(const Rules &&d)
    {
        data = move(d.data);
        return *this;
    }

    ~Rules()=default;

    auto begin(){
        if(data==nullptr)
            throw RulesNotFoundException{};
        return data->begin();
    }


    auto end(){
        if (data == nullptr)
            throw RulesNotFoundException{};
        return data->end();
    }

    auto begin() const
    {
        if (data == nullptr)
            throw RulesNotFoundException{};
        return data->begin();
    }

    auto end() const
    {
        if (data == nullptr)
            throw RulesNotFoundException{};
        return data->end();
    }

    void add(Rule<t> r){
        if(data==nullptr)
            data=make_shared<vector<Rule<t>>>();

        data->push_back(r);
    }


    size_t size()const{
        if (data == nullptr)
            throw RulesNotFoundException{};

        return data->size();
    }

    auto& operator[](size_t i){
        if (data == nullptr)
            throw RulesNotFoundException{};

        return (*data)[i];
    }

    auto &operator[](size_t i)const
    {
        if (data == nullptr)
            throw RulesNotFoundException{};

        return (*data)[i];
    }

    Rules& operator|(const Rule<t> r){
        if(r.data->left==nullptr)
            r.data->left=(*data)[0].data->left;
        add(r);
        return *this;
    }


    First<t> getFirst()const{
        First<t> f;
        try{
            for(auto x:*this){
                try{
                    f.insert(f.end(),x.getFirst().begin(),x.getFirst().end());
                }catch(...){}
            }
        }catch(...){
        }
        return f;
    }


    bool operator==(const Rules r) const{
        if(data==nullptr || r.data==nullptr)
            return false;
        if(data->size()!=r.data->size())
            return false;
        for (size_t i = 0, j = data->size();i<j;i++)
            if((*this)[i]!=r[i])
                return false;
        return true;
    }
    bool operator!=(const Rules r)const
    {
        if (data == nullptr || r.data == nullptr)
            return false;
        if (data->size() != r.data->size())
            return false;
        return !(*this==r);
    }
};

#endif // !_RULES_HPP_