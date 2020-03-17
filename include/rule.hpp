#ifndef _RULE_HPP_
#define _RULE_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif


template<typename cc>
class Rule{
    class rightAssociate{
    private:
        enum class Type{
            FAULTY,
            TERMINAL,
            NONTERMINAL
        };
        friend ostream& operator<<(ostream& o,Type t){
          switch (t) {
            case Type::TERMINAL:o << "terminal" ;break;
            case Type::NONTERMINAL:o << "Non terminal";break;
            case Type::FAULTY:o << "Faulty";break;
          };
          return o;
        }
        Type getType([[maybe_unused]]NonTerminal<cc>)const{
            return Type::NONTERMINAL;
        }
        Type getType([[maybe_unused]]Terminal<cc>)const{
            return Type::TERMINAL;
        }
        union Data{
            char x[48];
            NonTerminal<cc> n;
            Terminal<cc> t;
            Data():x{""}{}
            ~Data(){}
            Data(const Data&){}
            Data(const Data&&){}
            Data& operator=(const Data&){}
            Data& operator=(const Data&&){}

            Data(NonTerminal<cc> d):n{d}{}
            Data(Terminal<cc> d):t{d}{}

        };
        Type type;
        Data data;
    public:
        rightAssociate(NonTerminal<cc> x):type{Type::NONTERMINAL},data{x}{}
        rightAssociate(Terminal<cc> x):type{Type::TERMINAL},data{x}{}
        rightAssociate():type{Type::FAULTY},data{}{
        }
        rightAssociate(const rightAssociate& r):type{r.type}{
          if (type == Type::NONTERMINAL)
            data.n=r.data.n;
          else if (type == Type::TERMINAL)
            data.t=r.data.t;
        }
        rightAssociate(const rightAssociate&& r):type{r.type}{
          if (type == Type::NONTERMINAL)
            data.n=r.data.n;
          else if (type == Type::TERMINAL)
            data.t=r.data.t;
        }
        rightAssociate& operator=(const rightAssociate& r){
            type=r.type;
            if(type==Type::NONTERMINAL)
                data.n=r.data.n;
            else if(type==Type::TERMINAL)
                data.t=r.data.t;
            return *this;
        }
        rightAssociate& operator=(const rightAssociate&& r){
            type=r.type;
            if(type==Type::NONTERMINAL)
                data.n=r.data.n;
            else if(type==Type::TERMINAL)
                data.t=r.data.t;
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
        First<cc> getFirst(){
            if(type==Type::NONTERMINAL)
                return data.n.getFirst();
            else if(type==Type::TERMINAL)
                return First<cc>{data.t};
            return First<cc>{};
        }
        bool operator==(NonTerminal<cc> n)const{
            return *this==rightAssociate{n};
        }
        bool operator!=(NonTerminal<cc> n)const{
            return *this!=rightAssociate{n};
        }
        bool operator==(Terminal<cc> n)const{
            return *this==rightAssociate{n};
        }
        bool operator!=(Terminal<cc> n)const{
            return *this!=rightAssociate{n};
        }

    };
    typedef cc (*ActionType)(Parser<cc>);
    Rules<cc>* rs=nullptr;
    ActionType action=nullptr;
    vector<rightAssociate> r;
public:
    Rule(){};
    ~Rule(){};
    Rule(Rules<cc>* sr):rs{sr},r{}{}
    Rule(const Rule& f):rs{f.rs},action{f.action},r{f.r}{}
    Rule(const Rule&& f):rs{f.rs},action{f.action},r{f.r}{}
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
    First<cc> getFirst(){
        First<cc> f;
        for(auto i:r){
            First<cc> t=i.getFirst();
            if(t.size()==1)
                return t.size();
            else{
                bool flag=false;
                for(auto x:t)
                    if(x==Terminal<cc>::epsilon){
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
    Rule& add(isSomething<cc> x,v... M){
        r.push_back(rightAssociate{x});

        return add(M...);
    }


    Rule& add(isSomething<cc> x){
        r.push_back(rightAssociate{x});
        return *this;
    }

    Rule& add(){
        r.push_back(rightAssociate{Terminal<cc>::epsilon});
        return *this;
    }


    Rule& operator()(ActionType a){
        action=a;
        return *this;
    }
    cc operator()(Parser<cc>& x){
        if(action==nullptr)
            throw ActionNotSet{};
        return action(x);
    }
    Follow<cc> getFollowOf(Grammar<cc> g,NonTerminal<cc> n){
        bool flag=false;
        Follow<cc> f;
        for(auto i:r){
            if(flag){
                flag=false;
                First<cc> t=i.getFirst();
                for(auto i:t)
                    if(t==Terminal<cc>::epsilon){
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
    Rules<cc>& operator|(Rule r){
        return (*rs)|r;
    }

    bool operator==(Rule x)const{
      if(rs!=x.rs || r.size()!=x.r.size())
        return false;
      for(int i=0;i<r.size();i++)
        if(r[i]!=x.r[i])
          return false;
      return true;
    }

    bool operator!=(Rule x)const{
      return !(*this==x);
    }
    friend class Rules<cc>;
};

template<typename tt,template<typename xx>typename cc, typename... VV>requires isSomething<cc<tt>,tt>
Rule<tt> add(cc<tt> x,VV... M){
    return Rule<tt>{}.add(x,M...);
}

template<typename tt,template<typename xx>typename cc> requires isSomething<cc<tt>,tt>
Rule<tt> add(cc<tt> x){
    return Rule<tt>{}.add(x);
}

template<typename cc>
Rule<cc> add(){
    return Rule<cc>{}.add();
}


#endif
