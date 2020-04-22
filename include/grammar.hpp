#ifndef _GRAMMAR_HPP_
#define _GRAMMAR_HPP_ 1


#ifndef _TYPES_HPP_
#include<types.hpp>
#endif // !_TYPES_HPP_


template<typename t>
class Grammar{
    private:
        struct Data{
            vector<Terminal<t>> terminals;
            vector<NonTerminal<t>> nonterminals;
            NonTerminal<t> start;
            Rules<t> rules;

            Data(vector<Terminal<t>> ts,vector<NonTerminal<t>> ns, NonTerminal<t> s):start{s}{
                for(auto temp:ts)
                    terminals.push_back(temp);
                for(auto temp:ns)
                    nonterminals.push_back(temp);
                
                for(auto n:ns){
                    for(auto r:n.getRules()){
                        if(r.isNull())
                            throw GrammarContainNullException{};
                        if(r.isLeftRecursion())
                            throw GrammarContainLeftRecursionException{};
                        if(r.isNull())
                            throw GrammarContainUnitProductionException{};
                        rules.add(r);
                    }
                }
            }

            Data(const Data& d):terminals{d.terminals},nonterminals{d.nonterminals},start{d.start}{}
            Data(Data&& d):terminals{move(d.terminals)},nonterminals{move(d.nonterminals)},start{move(d.start)}{}

            Data& operator=(const Data& d){
                terminals=d.terminals;
                nonterminals=d.nonterminals;
                start=d.start;
                return *this;
            }

            Data& operator=(Data&& d){
                terminals=move(d.terminals);
                nonterminals=move(d.nonterminals);
                start=move(d.start);
                return *this;
            }


        };

        shared_ptr<Data> data;

    public:
        Grammar(vector<Terminal<t>> ts,vector<NonTerminal<t>> ns, NonTerminal<t> s):data{make_shared<Data>(ts,ns,s)}{}
        
        Grammar(const Grammar& g):data{g.data}{}
        Grammar(Grammar&& g):data{move(g.data)}{}

        Grammar& operator=(const Grammar& g){
            data=g.data;
            return *this;
        }

        Grammar& operator=(Grammar&& g){
            data=move(g.data);
            return *this;
        }

        ~Grammar(){}

        vector<Terminal<t>>& getTerminals()const{
            return data->terminals;
        }

        vector<NonTerminal<t>>& getNonTerminals()const{
            return data->nonterminals;
        }

        NonTerminal<t>& getStart()const{
            return data->start;
        }
};


#endif // !_GRAMMAR_HPP_