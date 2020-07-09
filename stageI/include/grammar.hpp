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

        Data(vector<Terminal<t>> ts, vector<NonTerminal<t>> ns, NonTerminal<t> s,bool val=true) : terminals{move(ts)},nonterminals{move(ns)},start{move(s)}
        {
            if(val){
                for(auto nss:nonterminals)
                    for(auto r:nss.getRules())
                        rules.add(r);
            } 
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
    Grammar(vector<Terminal<t>> ts, vector<NonTerminal<t>> ns, NonTerminal<t> s,bool val=true) : data{make_shared<Data>(move(ts), move(ns), move(s),val)} {}

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

    bool  hasNull()const{
        for(auto r:getRules())
            if(r.isNull()){
                ////cout<<r<<endl;
                return true;
            }
          
        return false;
    }
    bool hasUnitProduction()const{
        for (auto r : getRules())
            if (r.isUnitProduction())
            {
                ////cout<<r<<endl;
                return true;
            }

        return false;
    }

    bool hasLeftRecursion() const
    {
        for(auto r:getRules())
            if(r.isLeftRecursion()){
                ////cout<<r<<endl;
                return true;
            }
          
        return false;
    }

    Rules<t> getNullProduction()const{
        Rules<t> rs;
        
        for(auto r:getRules())
            if(r.isNull()){
                ////cout<<r<<endl;
                rs.add(r);
            }


        ////cout<<rs.size()<<endl;
        return rs;
    }
    Rules<t> getUnitProduction()const{
        Rules<t> rs;

        for (auto r : getRules())
            if (r.isUnitProduction())
            {
                ////cout<<r<<endl;
                rs.add(r);
            }

        ////cout<<rs.size()<<endl;
        return rs;
    }

    Rules<t> getLeftRecursionProduction() const
    {
        Rules<t> rs;

        for (auto r : getRules())
            if (r.isLeftRecursion())
            {
                ////cout<<r<<endl;
                rs.add(r);
            }

        ////cout<<rs.size()<<endl;
        return rs;
    }

    Grammar getReduceGrammarNull(const Rule<t>& r)const{
        Grammar g{getTerminals(),getNonTerminals(),getStart(),false};
        //g.data->rules.remove(r);

        //cout<<"checkpoint : getReduceGrammarNull"<<endl;
 
        if(r.getLeft().getRules().size()!=1){
            //cout<<"Reducing For : "<<r<<endl;
            //cout << "rules(left nonterminal): " << r.getLeft().getRules().size()<<endl;
            r.getLeft().getRules().remove(r);
            //cout << r.getLeft().getRules();
            g.initRules();
            ////cout<<g.getRules();
            Rules<t> rr =   g.getRules();
            //cout<<"New Grammar Rules : "<<endl<<rr<<endl;  
            //g.getRules().data->clear();
            ////cout<<rr.returnReduce(r)<<endl;
            g.data->rules=rr.returnReduce(r);
            //g.addRules(rr.returnReduce(r));
            //cout<<"Debug : "<<endl;
            //cout<<g<<endl;
        }
        else{
            Rules<t> rr;
            //cout<<"here for : "<<r<<endl;
            r.getLeft().getRules().remove(r);
            g.initRules();
            //cout<<"left.size()"<<r.getLeft().getRules().size()<<endl;
            //cout << "Debuging [rules.size ] : " << g.getRules().size() << endl;
            //cout<<"Debug Start : "<<endl;
            for (auto rs : g.getRules())
            {
                //cout<<"Rule found : "<<rs<<endl;
                //cout<<"Changed Rule is : "<<(*rs.getLeft().getThis())<<" -> ";
                Rule<t> r1{rs.getLeft().getThis()};
                for(auto right:rs.getRightAssociates())
                    if(right!=r.getLeft()){
                        r1.add(right);
                        //cout<<right<<" ";
                    }
                rr.add(r1);
                r1.getLeft()->add(r1.getRightAssociates());
                //cout<<endl;
            }
            //cout<<"Rules After change : "<<endl<<rr<<endl;
            g.removeNonTerminal(r.getLeft());
            g.removeAllRules();
            //cout<<"Debug [Ensuring Delete ] : "<<g.getRules().size()<<endl;
            g.addRules(rr);
        }
        
        return g;
    }

    Grammar getReduceGrammarRecursion(const Rule<t> &r) const{
        Grammar g{getTerminals(), getNonTerminals(), getStart()};
        //g.data->rules.remove(r);

        if (r.getLeft().getRules().size() < 2)
        {
            throw SyntaxError{};
        }
        else
        {
            for(auto rl:r.getLeft().getRules())
                if(rl.isLeftRecursion()){
                    if(rl.getRightAssociates().size()==1)
                        throw SyntaxError{};
                }
                    
        }

        return g;
    }
    Grammar getReduceGrammarUnitProduction(const Rule<t>& r)const{
        Grammar g{getTerminals(), getNonTerminals(), getStart()};
        //g.data->rules.remove(r);
            Rules<t> rr;
            //cout << "here for : " << r << endl;
            r.getLeft().getRules().remove(r);
            //if (find(g.getNonTerminals().begin(), g.getNonTerminals().end(),r.getLeft())!=g.getNonTerminals().end())
              //  g.getNonTerminals().erase(find(g.getNonTerminals().begin(), g.getNonTerminals().end(), r.getLeft()));
            g.initRules();
            g.removeRedundant();
            //cout<<"left.size()"<<r.getLeft().getRules().size()<<endl;
            //cout << "Debuging [rules.size ] : " << g.getRules().size() << endl;
            //cout<<"Debug Start : "<<endl;
            for (auto rs : g.getRules())
            {
                //cout<<"Rule found : "<<rs<<endl;
                //cout<<"Changed Rule is : "<<(*rs.getLeft().getThis())<<" -> ";
                Rule<t> r1{rs.getLeft().getThis()};
                for (auto right : rs.getRightAssociates())
                    if (right != r.getLeft())
                    {
                        r1.add(right);
                        //cout<<right<<" ";
                    }
                    else
                        r1.add(r.getRightAssociates()[0]);
                rr.add(r1);
                r1.getLeft()->add(r1.getRightAssociates());
                //cout<<endl;
            }
            //cout<<"Rules After change : "<<endl<<rr<<endl;
            g.removeNonTerminal(r.getLeft());
            g.removeAllRules();
            //cout<<"Debug [Ensuring Delete ] : "<<g.getRules().size()<<endl;
            g.addRules(rr);
            g.getNonTerminals().erase(find(g.getNonTerminals().begin(), g.getNonTerminals().end(), r.getLeft()));
            return g;
    }

    Grammar removeNull()const{
        //cout<<"checkpoint : removeNull"<<endl;
        //cout<<endl<<*this<<endl;
        if(hasNull()){
            if(getNullProduction().size()<=0)
                throw SyntaxError{};
            Rule<t> r=getNullProduction()[0];//This will only remove one null production
            Grammar g=getReduceGrammarNull(r);
            //cout<<endl<<"reducing for : "<<r<<endl<<*this<<endl<<g<<endl;
            return g.removeNull();
        }
        else
            return *this;
    }
    Grammar removeUnitProduction()const{
        if(hasUnitProduction()){
            if(getUnitProduction().size()<=0)
                throw SyntaxError{};
            Rule<t> r=getUnitProduction()[0];
            Grammar g=getReduceGrammarUnitProduction(r);
            return g.removeUnitProduction();
        }
        else
            return *this;
    }

    Grammar reduce(){
        removeRedundant();
        if(hasNull() || hasUnitProduction()){
            if(hasNull())
                return removeNull().reduce();
            else
                return removeUnitProduction().reduce();
        }
        else
            return *this;
    }


    Grammar removeLeftRecursion()const{
        if(hasLeftRecursion()){
            //cout<<endl<<*this<<endl;
            if(getLeftRecursionProduction().size()<=0)
                throw SyntaxError{};
            Rule<t> r = getLeftRecursionProduction()[0]; //This will only remove one null production
            Grammar g=getReduceGrammarRecursion(r);
            //cout<<endl<<"reducing for : "<<r<<endl<<g<<endl;
            return g.removeLeftRecursion();
        }
        else
            return *this;
    }

    void removeAllRules(){
        if(data!=nullptr)
            data->rules.removeAll();
    }
    void addRules(const Rules<t>& rs){
        if(data!=nullptr)
            data->rules=rs;
        for(auto r:rs)
            r.getLeft().add(r);
    }


    void initRules(){
        if(data!=nullptr)
            for (auto nss : getNonTerminals())
                for (auto r : nss.getRules())
                    data->rules.add(r);
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

    void removeRedundant(){
        Rules<t> rs;
        for(auto r : getRules()){
            bool flag=false;

            for(auto i:rs)
                if(r==i){
                    flag=true;
                    break;
                }

            if(!flag)
                rs.add(r);
        }

        removeAllRules();
        addRules(rs);

        for(auto n:getNonTerminals())
            n.getRules().data->clear();
        
        for(auto r1:rs)
            r1.getLeft()->add(r1.getRightAssociates());
    }
};

#endif // !_GRAMMAR_HPP_