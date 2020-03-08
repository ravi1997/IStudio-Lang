#ifndef _RULE_HPP_
#define _RULE_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif

template<typename T>
class Rule{
    class rightAssociate{
    private:
        enum class Type{
            TERMINAL,
            NONTERMINAL,
            FAULTY
        };
        Type getType([[maybe_unused]]NonTerminal<T>)const{
            return Type::NONTERMINAL;
        }
        Type getType([[maybe_unused]]Terminal<T>)const{
            return Type::TERMINAL;
        }
        union Data{
            NonTerminal<T> n;
            Terminal<T> t;
            char x;
        };
        Type type;
        Data data;
    public:
        rightAssociate(NonTerminal<T> x):type{Type::NONTERMINAL}{
            data.n=x;
        }
        rightAssociate(Terminal<T> x):type{Type::TERMINAL}{
            data.t=x;
        }
        rightAssociate():type{Type::FAULTY}{
            data.x=char{};
        }
        rightAssociate(const rightAssociate& r):type{r.type}{
            if(type==Type::NONTERMINAL)
                data.n=r.data.n;
            else if(type==Type::TERMINAL)
                data.t=r.data.t;
            else
                data.x='\0';
        }
        rightAssociate(const rightAssociate&& r):type{r.type}{
            if(type==Type::NONTERMINAL)
                data.n=r.data.n;
            else if(type==Type::TERMINAL)
                data.t=r.data.t;
            else
                data.x='\0';
        }
        rightAssociate& operator=(const rightAssociate& r){
            type=r.type;
            if(type==Type::NONTERMINAL)
                data.n=r.data.n;
            else if(type==Type::TERMINAL)
                data.t=r.data.t;
            else
                data.x='\0';
            return *this;
        }
        rightAssociate& operator=(const rightAssociate&& r){
            type=r.type;
            if(type==Type::NONTERMINAL)
                data.n=r.data.n;
            else if(type==Type::TERMINAL)
                data.t=r.data.t;
            else
                data.x='\0';
            return *this;
        }
        ~rightAssociate(){}
        bool operator==(const rightAssociate r)const{
            if(type!=r.type)
                return false;
            if(type==Type::NONTERMINAL)
                return data.n==r.data.n;
            else if(type==Type::TERMINAL)
                return data.t==r.data.t;
            else
                return true;
        }
        bool operator!=(const rightAssociate r)const{
            return !(*this==r);
        }
        First<T> getFirst(){
            if(type==Type::NONTERMINAL)
                return data.n.getFirst();
            else if(type==Type::TERMINAL)
                return First<T>{data.t};
            return First<T>{};
        }
        bool operator==(NonTerminal<T> n)const{
            return *this==rightAssociate{n};
        }
        bool operator!=(NonTerminal<T> n)const{
            return *this!=rightAssociate{n};
        }
        bool operator==(Terminal<T> n)const{
            return *this==rightAssociate{n};
        }
        bool operator!=(Terminal<T> n)const{
            return *this!=rightAssociate{n};
        }

    };

    typedef T (*ActionType)(Parser<T>);

    Rules<T>* rs=nullptr;
    ActionType action=nullptr;
    vector<rightAssociate> r;
public:
    Rule(){};
    ~Rule(){};
    Rule(Rules<T>* sr):rs{sr}{}
    Rule(const Rule& f):r{f.r},action{f.action},rs{f.rs}{}
    Rule(const Rule&& f):r{f.r},action{f.action},rs{f.rs}{}
    Rule& operator=(const Rule& f){
        r.clear();
        for(auto i:f.r)
            r.push_back(i);
        rs=f.rs;
        action=f.action;
        return *this;
    }
    Rule& operator=(const Rule&&f){
        r.clear();
        for(auto i:f.r)
            r.push_back(i);
        rs=f.rs;
        action=f.action;
        return *this;
    }
    First<T> getFirst(){
        First<T> f;
        for(auto i:r){
            First<T> t=i.getFirst();
            if(t.size()==1)
                return t.size();
            else{
                bool flag=false;
                for(auto x:t)
                    if(x==Terminal<T>::epsilon){
                        flag=true;
                        break;
                    }
                if(flag==true){
                    f.insert(f.end(),t.begin(),t.end());
                    continue;
                }
                return t;
            }
        }
        return f;
    }

    template<typename... v>
    Rule& add(isSomething<T>& x,v&&... M){
        r.push_back(rightAssociate{x});
        return add(M...);
    }


    Rule& add(isSomething<T>& x){
        r.push_back(rightAssociate{x});
        return *this;
    }
    Rule& add(){
        r.push_back(rightAssociate{Terminal<T>::epsilon});
        return *this;
    }


    Rule& operator()(ActionType a){
        action=a;
        return *this;
    }
    T operator()(Parser<T>& x){
        if(action==nullptr)
            throw ActionNotSet{};
        return action(x);
    }
    Follow<T> getFollowOf(Grammar<T> g,NonTerminal<T> n){
        bool flag=false;
        Follow<T> f;
        for(auto i:r){
            if(flag){
                flag=false;
                First<T> t=i.getFirst();
                for(auto i:t)
                    if(t==Terminal<T>::epsilon){
                        flag=true;
                        t.erase(find(t.begin(),t.end(),i));
                    }
                f.insert(f.end(),t.begin(),t.end());
            }
            if(i==n)
                flag=true;
        }
        return f;
    }
    Rules<T>& operator|(Rule r){
        return (*rs)|r;
    }

    friend class Rules<T>;
};

template<typename t, typename... T>
Rule<t> add(isSomething<t> x,T... M){
    return Rule<t>{}.add(x,M...);
}

template<typename t>
Rule<t> add(isSomething<t> x){
    return Rule<t>{}.add(x);
}

template<typename t>
Rule<t> add(){
    return Rule<t>{}.add();
}

#endif
