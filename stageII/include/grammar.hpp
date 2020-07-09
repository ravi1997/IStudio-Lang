#ifndef _GRAMMAR_HPP_
#define _GRAMMAR_HPP_ 1

#ifndef _TYPES_HPP_
#include <types.hpp>
#endif // !_TYPES_HPP_

#ifndef _RULE_HPP_
#include <rule.hpp>
#endif // !_RULE_HPP_

#ifndef _RULES_HPP_
#include <rules.hpp>
#endif // !_RULES_HPP_

template <typename t>
class Grammar
{
    struct Data
    {
        vector<Terminal<t>> terminals;
        vector<NonTerminal<t>> nonterminals;
        NonTerminal<t> start;
        Rules<t> rules;

        Data(vector<Terminal<t>> ts, vector<NonTerminal<t>> ns, NonTerminal<t> s) : terminals{move(ts)},nonterminals{move(ns)},start{move(s)}
        {
            for(auto nss:nonterminals)
                for(auto r:nss.getRules())
                    rules.add(r);
        }
        Data(const Data &d) : terminals{d.terminals}, nonterminals{d.nonterminals}, start{d.start},rules{d.rules} {}
        Data(Data &&d) : terminals{move(d.terminals)}, nonterminals{move(d.nonterminals)}, start{move(d.start)},rules{move(d.rules)} {}
        Data &operator=(const Data &d)
        {
            terminals = d.terminals;
            nonterminals = d.nonterminals;
            start = d.start;
            rules = d.rules;
            return *this;
        }

        Data &operator=(Data &&d)
        {
            terminals = move(d.terminals);
            nonterminals = move(d.nonterminals);
            start = move(d.start);
            rules = move(d.rules);
            return *this;
        }
    };

    shared_ptr<Data> data;

public:
    Grammar(vector<Terminal<t>> ts, vector<NonTerminal<t>> ns, NonTerminal<t> s) : data{make_shared<Data>(move(ts), move(ns), move(s))} {}

    Grammar(const Grammar &g) : data{g.data} {}
    Grammar(Grammar &&g) : data{move(g.data)} {}

    Grammar &operator=(const Grammar &g)
    {
        data = g.data;
        return *this;
    }

    Grammar &operator=(Grammar &&g)
    {
        data = move(g.data);
        return *this;
    }

    ~Grammar() {}

    vector<Terminal<t>> &getTerminals() const
    {
        return data->terminals;
    }

    vector<NonTerminal<t>> &getNonTerminals() const
    {
        return data->nonterminals;
    }

    NonTerminal<t> &getStart() const
    {
        return data->start;
    }
    Rules<t> &getRules() const
    {
        return data->rules;
    }

    Grammar getAugmented(NonTerminal<t> sdash)const{
        vector<NonTerminal<t>> ns=getNonTerminals();
        ns.emplace_back(sdash);
        return Grammar{getTerminals(),move(ns),move(sdash)};
    }

    bool hasNull()const{
        for(auto r:getRules())
            if(r.isNull()){
                //cout<<r<<endl;
                return true;
            }
          
        return false;
    }

    Rules<t> getNullProduction()const{
        Rules<t> rs;
        
        for(auto r:getRules())
            if(r.isNull()){
                //cout<<r<<endl;
                rs.add(r);
            }


        //cout<<rs.size()<<endl;
        return rs;
    }


    Grammar getReduceGrammar(const Rule<t>& r)const{
        Grammar g{getTerminals(),getNonTerminals(),getStart()};
        g.data->rules.remove(r);

        if(r.getLeft().getRules().size()!=1){
            Rules<t> rr=g.getRules();
            g.removeAllRules();
            g.addRules(rr.returnReduce(r));
        }
        else{
            cout<<"here for : "<<r<<endl;
            Rules<t> rr;
            cout << "Debuging [rules.size ] : " << g.getRules().size() << endl;
            cout<<"Debug Start : "<<endl;
            for (auto rs : g.getRules())
            {
                cout<<"Rule found : "<<rs<<endl;
                cout<<"Changed Rule is : "<<(*rs.getLeft().getThis())<<" -> ";
                Rule<t> r1{rs.getLeft().getThis()};
                for(auto right:rs.getRightAssociates())
                    if(right!=r.getLeft()){
                        r1.add(right);
                        cout<<right<<" ";
                    }
                rr.add(r1);
                cout<<endl;
            }
            cout<<"Rules After change : "<<endl<<rr<<endl;
            g.removeNonTerminal(r.getLeft());
            g.removeAllRules();
            cout<<"Debug [Ensuring Delete ] : "<<g.getRules().size()<<endl;
            g.addRules(rr);
        }
        
        return g;
    }


    Grammar removeNull()const{
        if(hasNull()){
            cout<<endl<<*this<<endl;
            if(getNullProduction().size()<=0)
                throw SyntaxError{};
            Rule<t> r=getNullProduction()[0];//This will only remove one null production
            Grammar g=getReduceGrammar(r);
            cout<<endl<<"reducing for : "<<r<<endl<<g<<endl;
            return g.removeNull();
        }
        else
            return *this;
    }

    void removeAllRules(){
        if(data!=nullptr)
            data->rules.removeAll();
    }

    void addRules(const Rules<t>& r){
        if(data!=nullptr)
            data->rules=r;
    }


    friend ostream& operator<<(ostream& o,Grammar g){
        o<<"NonTerminals : ";
        for(auto n:g.getNonTerminals())
            o<<n<<" ";
        o<<endl;
        o << "Terminals : ";
        for (auto n : g.getTerminals())
            o << n << " ";
        o << endl;

        o<<"Start Symbol : "<<g.getStart()<<endl;

        o<<"Rules :"<<endl;
        o<<g.getRules();
        return o;
    }
    void removeNonTerminal(const NonTerminal<t>& n){
        if(data!=nullptr){
            if(find(getNonTerminals().begin(),getNonTerminals().end(),n)!=getNonTerminals().end())
                data->nonterminals.erase(find(getNonTerminals().begin(), getNonTerminals().end(), n));
        }
    }
};

#endif // !_GRAMMAR_HPP_