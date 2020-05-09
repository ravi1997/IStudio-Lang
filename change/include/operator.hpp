#ifndef _OPERATOR_HPP_
#define _OPERATOR_HPP_ 1

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif // !_TYPES_HPP_

enum class OperatorType{
    UNARYPRE,
    UNARYPOST,
    BINARY
};
template <typename t, OperatorType o>
class Operator;

template <typename t>
class Operator<t,OperatorType::UNARYPRE>
{
    public:
        using ActionType = function<void(const Parser<t> &)>;
    private:
    struct Data
    {
            vector<pair<string, optional<ActionType>>> ops;
    };
    shared_ptr<Data> data;
    Operator():data{make_shared<Data>()}{}

    void addOperator(string s){
        if(data==nullptr)
            data=make_shared<Data>();
        if(findOperator(s))
            throw OperatorExist{s};
        data->ops.push_back(pair<string,optional<ActionType>>{s,nullopt});
    }
    void addOperator(string s,invocable auto a){
        if (data == nullptr)
            data = make_shared<Data>();
        if (findOperator(s))
            throw OperatorExist{s};
        data->ops.push_back(pair<string, optional<ActionType>>{s, nullopt});
    }

    void operator()(string s,const Parser<t>& p){
        if (data == nullptr)
            return;
        for (auto x : data->ops)
        {
            if (x.first == s){
                if(x.second.has_value())
                    x.second(p);
                break;    
            }
        }
    }
    bool findOperator(string s) const{
        if(data==nullptr)
            return false;
        for(auto x:data->ops){
            if(x.first==s)
                return true;
        }
        return false;
    }
    friend class Parser<t>;
};

template <typename t>
class Operator<t, OperatorType::UNARYPOST>
{
public:
    using ActionType = function<void(const Parser<t> &)>;

private:
    struct Data
    {
        vector<pair<string, optional<ActionType>>> ops;
    };
    shared_ptr<Data> data;
    Operator() : data{make_shared<Data>()} {}

    void addOperator(string s)
    {
        if (data == nullptr)
            data = make_shared<Data>();
        if (findOperator(s))
            throw OperatorExist{s};
        data->ops.push_back(pair<string, optional<ActionType>>{s, nullopt});
    }
    void addOperator(string s, invocable auto a)
    {
        if (data == nullptr)
            data = make_shared<Data>();
        if (findOperator(s))
            throw OperatorExist{s};
        data->ops.push_back(pair<string, optional<ActionType>>{s, nullopt});
    }

    void operator()(string s, const Parser<t> &p)
    {
        if (data == nullptr)
            return;
        for (auto x : data->ops)
        {
            if (x.first == s)
            {
                if (x.second.has_value())
                    x.second(p);
                break;
            }
        }
    }
    bool findOperator(string s) const
    {
        if (data == nullptr)
            return false;
        for (auto x : data->ops)
        {
            if (x.first == s)
                return true;
        }
        return false;
    }
    friend class Parser<t>;
};

template <typename t>
class Operator<t, OperatorType::BINARY>
{
public:
    using ActionType = function<void(const Parser<t> &)>;

private:
    struct Data
    {
        vector<pair<string, optional<ActionType>>> ops;
    };
    shared_ptr<Data> data;
    Operator() : data{make_shared<Data>()} {}

    void addOperator(string s)
    {
        if (data == nullptr)
            data = make_shared<Data>();
        if (findOperator(s))
            throw OperatorExist{s};
        data->ops.push_back(pair<string, optional<ActionType>>{s, nullopt});
    }
    void addOperator(string s, invocable auto a)
    {
        if (data == nullptr)
            data = make_shared<Data>();
        if (findOperator(s))
            throw OperatorExist{s};
        data->ops.push_back(pair<string, optional<ActionType>>{s, nullopt});
    }

    void operator()(string s, const Parser<t> &p)
    {
        if (data == nullptr)
            return;
        for (auto x : data->ops)
        {
            if (x.first == s)
            {
                if (x.second.has_value())
                    x.second(p);
                break;
            }
        }
    }
    bool findOperator(string s) const
    {
        if (data == nullptr)
            return false;
        for (auto x : data->ops)
        {
            if (x.first == s)
                return true;
        }
        return false;
    }
    friend class Parser<t>;
};



template <typename t>
using UnaryPre = Operator<t, OperatorType::UNARYPRE>;

template <typename t>
using UnaryPost = Operator<t, OperatorType::UNARYPOST>;

template <typename t>
using Binary = Operator<t, OperatorType::BINARY>;



#endif // !_OPERATOR_HPP_