#ifndef _TERMINAL_HPP_
#define _TERMINAL_HPP_ 1

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif // !_TYPES_HPP_

template<typename t>
class Terminal{
    public:
        using ActionType = function < void(const Parser<t> &)>;
        enum class TerminalType{
            NORMAL,
            OPERATOR,
            EPSILON,
            END
        };
    private:

    struct Data {
        string pattern="";
        TerminalType type=TerminalType::NORMAL;
        vector<ActionType> action;
        Data()=default;
        Data(const string s, TerminalType T = TerminalType::NORMAL) : pattern{s}, type{T} {}
        Data(const string s, invocable auto a,TerminalType T = TerminalType::NORMAL) : pattern{s}, type{T} {
            action.emplace_back(a);
        }
        Data(const Data& d):pattern{d.pattern}{
            for(auto a: d.action)
                action.push_back(a);
        }
        Data(const Data&& d):pattern{move(d.pattern)},action{move(d.action)}{}
        Data& operator=(const Data& d){
            pattern=d.pattern;
            for (auto a : d.action)
                action.push_back(a);
            return *this;
        }
        Data& operator=(const Data&& d){
            pattern=move(pattern);
            action=move(action);
            return *this;
        }
        ~Data()=default;
        bool operator==(Data d)const{
            return pattern==d.pattern && type==d.type;
        }
        bool operator!=(Data d)const{
            return !(*this==d);
        }
    };

    shared_ptr<Data> data;


    public:
        Terminal(string pattern, TerminalType T = TerminalType::NORMAL) : data{make_shared<Data>(pattern, T)} {}
        
        Terminal(string pattern, invocable auto a,TerminalType T = TerminalType::NORMAL) : data{make_shared<Data>(pattern,a, T)} {}
        Terminal(const Terminal& d):data{d.data}{}
        Terminal(const Terminal&& d):data{move(d.data)}{}

        Terminal& operator=(const Terminal& T){
            data=T.data;
            return *this;
        }
        
        Terminal& operator=(const Terminal&& T){
            data=move(T.data);
            return *this;
        }

        ~Terminal()=default;

        bool operator==(const Terminal& T)const{
            return data!=nullptr && T.data!=nullptr && *data==*T.data;
        }

        bool operator!=(const Terminal& T)const{
            return data!=nullptr && T.data!=nullptr && !(*this==data);
        }

        virtual string getMatch(const string s)const{
            if (data == nullptr)
                throw TerminalNotSetException{};
            smatch m;
            regex_search(s, m, regex{(data->pattern != string{""}) ? string{"^"} + data->pattern : data->pattern});
            for (auto x : m)
                return x;
            return string{""};
        }
        
        First<t> getFirst()const{
            return First<t>{*this};
        }

        const string &getPattern() const{
            if (data == nullptr)
                throw TerminalNotSetException{};
            return data->pattern;
        }

        friend ostream& operator<<(ostream& o,Terminal d){
            o<<d.getPattern();
            return o;
        }

        const static Terminal EPSILON;
        const static Terminal DOLLAR;
};

#endif // !_TERMINAL_HPP_