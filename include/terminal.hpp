#ifndef _TERMINAL_HPP_
#define _TERMINAL_HPP_ 1

#ifndef _TYPES_HPP_
#include <types.hpp>
#endif // !_TYPES_HPP_

#ifndef _LOGGER_HPP_
#include<logger.hpp>
#endif // !_LOGGER_HPP_

template<typename t>
class Terminal{
    public:
        using ActionType= function<t(const Parser<t>&)>;
        enum class TerminalType{
            NORMAL,
            OPERATOR,
            EPSILON,
            END
        };
    private:
        struct Data{
            TerminalType type=TerminalType::NORMAL;
            variant<string,vector<string>> pattern;
            vector<ActionType> action;

            Data()=default;
            Data(string s,TerminalType g):type{g},pattern{s}{}
            Data(string s, invocable auto x, TerminalType g):type{g},pattern{s}{
                action.push_back(x);
            }

            Data(const Data& d):type{d.type},pattern{d.pattern}{
                for (auto x : d.action)
                    action.push_back(x);
            }
            Data(const Data&& d):type{move(d.type)},pattern{move(d.pattern)},action{move(d.action)}{}

            Data& operator=(const Data& d){
                type=d.type;
                pattern=d.pattern;
                
                action.clear();
                for(auto x:d.action)
                    action.push_back(x);

                return *this;
            }

            Data& operator=(const Data&& d){
                type=move(d.type);
                pattern=move(d.pattern);
                action=move(d.action);
                return *this;
            }

            ~Data()=default;


            bool operator==(const Data d)const{
                if(type==d.type){
                    if(type==TerminalType::NORMAL){
                        return get<string>(pattern)==get<string>(d.pattern);
                    }
                    else if (type == TerminalType::OPERATOR)
                    {
                        return get<vector<string>>(pattern)[0]==get<vector<string>>(d.pattern)[0];
                    }
                    else
                    {
                        return true;
                    }
                }
                return false;
            }

            bool operator!=(const Data d)const{
                return !(*this==d);
            }
        };
        shared_ptr<Data> data;
    public:
        Terminal():data{make_shared<Data>()}{}
        Terminal(string s="",TerminalType g=TerminalType::NORMAL):data{make_shared<Data>(s,g)}{}
        Terminal(string s, invocable auto x, TerminalType g = TerminalType::NORMAL):data{make_shared<Data>(s,x,g)}{}
        Terminal(const Terminal & d) : data{d.data} {}
        Terminal(const Terminal&& d):data{move(d.data)}{}

        Terminal& operator=(const Terminal& d){
            data=d.data;
            return *this;
        }

        Terminal& operator=(const Terminal&& d){
            data=move(d.data);
            return *this;
        }
        ~Terminal()=default;


        bool operator==(const Terminal d)const{
            return data!=nullptr &&
                   d.data!=nullptr &&
                   *data==*d.data; 
        }

        bool operator!=(const Terminal d) const
        {
            return data != nullptr &&
                   d.data != nullptr &&
                   *data != *d.data;
        }


        bool isOperator()const{
            if(data==nullptr)
                throw TerminalNotSetException{};
            return data->type==TerminalType::OPERATOR;
        }

        void add(string s,invocable auto x){
            try{
                assert(isOperator());
            }catch(...)
            {
                data=make_shared<Data>();
            }
            get<vector<string>>(data->pattern).push_back(s);
            data->action.push_back(x);
        }


        First<t> getFirst()const{
            return First<t>{*this};
        }

        string getMatch(string s) const
        {
            if (data == nullptr)
                throw TerminalNotSetException{};
            smatch m;
            if(data->type==TerminalType::NORMAL){
                regex_search(s, m, regex{(get<string>(data->pattern) != string{""}) ? string{"^"} + get<string>(data->pattern) : data->pattern});
                for (auto x : m)
                    return x;
            }
            else if (data->type == TerminalType::OPERATOR)
            {
                string max="";
                for(auto i:get<vector<string>>(data->pattern)){
                    regex_search(s, m, regex{(i != string{""}) ? string{"^"} + i : string{""}});
                    for (auto x : m){
                        if(max.length()<x.length())
                            max=x;
                        break;
                    }
                }
                return max;
            }
            return string{""};
        }
        friend ostream &operator<<(ostream &o, const Terminal &tt)
        {
            if (tt.data != nullptr)
            {
                //o<<"ok"<<endl;
                //cout<<(tt.data!=nullptr)<<endl;
                if(!tt.isOperator())
                    o << *tt.data;
                else
                    o << "OPERATOR";
            }
            return o;
        }
        friend Logger &operator<<(Logger &o, const Terminal &tt)
        {
            if (tt.data != nullptr)
            {
                //o<<"ok"<<endl;
                //cout<<(tt.data!=nullptr)<<endl;
                if (!tt.isOperator())
                    o << *tt.data;
                else
                    o << "OPERATOR";
            }
            return o;
        }

        bool operator<(const Terminal tt) const{
            return *this!=tt;
        }

        const static Terminal EPSILON;
        const static Terminal DOLLAR;
};

#endif // !_TERMINAL_HPP_