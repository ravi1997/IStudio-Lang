#ifndef _TERMINAL_HPP_
#define _TERMINAL_HPP_ 1

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif // !_TYPES_HPP_

enum class TerminalType{
    NORMAL,
    EPSILON,
    END
};

template<typename t>
concept isNotString= !is_same<t,string>::value && !is_same<t,const char*>::value;

template<typename t>
class Terminal{
    struct Data{
        string pattern;
        TerminalType end;
        vector<function<void (const Parser<t>&)>>action;

        Data(string s,bool e):pattern{s},end{(e==true)?TerminalType::END : (s=="")?TerminalType::EPSILON: TerminalType::NORMAL},action{[](const Parser<t>&){}}{}

        Data(isNotString a,string s="",bool e=false):pattern{s},end{(e==true)?TerminalType::END : (s=="")?TerminalType::EPSILON: TerminalType::NORMAL},action{a}{}

        Data(const Data& d):pattern{d.pattern},end{d.end},action{d.action}{}
        Data(Data&& d):pattern{move(d.pattern)},end{d.end},action{move(d.action)}{}

        Data& operator=(const Data& d){
            pattern=d.pattern;
            end=d.end;
            action.clear();

            for(auto a:d.action)
                action.push_back(a);
            
            return *this;
        }

        Data& operator=(Data&& d){
            pattern=move(d.pattern);
            end=d.end;
            action.clear();

            action=move(d.action);         
            return *this;
        }
        friend ostream& operator<<(ostream& o,Data& d){
            //cout<<"ok"<<endl;
            switch (d.end)
            {
                case TerminalType::EPSILON:
                    o<<"Epsilon(e)";
                break;
                case TerminalType::END:
                    o<<"Dollar($)";
                break;
                default:
                    o<<d.pattern;
                break;
            }
        
            return o;
        }
        friend Logger& operator<<(Logger & o,Data& d){
            //cout<<"ok"<<endl;
            switch (d.end)
            {
                case TerminalType::EPSILON:
                    o<<"Epsilon(e)";
                break;
                case TerminalType::END:
                    o<<"Dollar($)";
                break;
                default:
                    o<<d.pattern;
                break;
            }
        
            return o;
        }
    };

    shared_ptr<Data> data;

public:
    Terminal(string s="",bool e=false):data{make_shared<Data>(s,e)}{}
    
    Terminal(isNotString a,string s="",bool e=false):data{make_shared<Data>(a,s,e)}{}

    Terminal(const Terminal& dt):data{dt.data}{}
    Terminal(Terminal&& dt):data{move(dt.data)}{}

    Terminal& operator=(const Terminal& dt){
        data=dt.data;
        return *this;
    }

    Terminal& operator=(Terminal&& dt){
        data=move(dt.data);
        return *this;
    }

    bool operator==(Terminal dt) const{
        return data==dt.data;
    }

    bool operator!=(Terminal dt)const{
        return !(*this==dt);
    }

    bool operator<(Terminal dt)const{
        return data->pattern<dt.data->pattern;
    }

    void operator()(const Parser<t>& p)const{
        if(data==nullptr || data->action.size()==0)
            throw ActionNotSet{};
        data->action[0](p);
    }

    First<t> getFirst()const{
        return First<t>{*this};
    }

    friend ostream& operator<<(ostream& o,const Terminal& tt){
        if(tt.data!=nullptr){
            //o<<"ok"<<endl;
            //cout<<(tt.data!=nullptr)<<endl;
            o<<*tt.data;
        }
        return o;
    }
    friend Logger& operator<<(Logger& o,const Terminal& tt){
        if(tt.data!=nullptr){
            //o<<"ok"<<endl;
            //cout<<(tt.data!=nullptr)<<endl;
            o<<*tt.data;
        }
        return o;
    }

    string getMatch(string s)const {
      if(data==nullptr)
        throw TerminalNotSetException{};
      smatch m;
      regex_search(s, m, regex{(data->pattern!=string{""})?string{"^"}+data->pattern:data->pattern});
      for(auto x:m)
          return x;
      return string{""};
    }

    const static Terminal EPSILON;
    const static Terminal DOLLAR;
};

#endif // !_TERMINAL_HPP_