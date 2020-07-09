#ifndef _RULE_HPP_
#define _RULE_HPP_ 1

#ifndef _RIGHT_ASSOCIATE_HPP_
#include<rightassociate.hpp>
#endif // !_RIGHT_ASSOCIATE_HPP_


template<typename t>
class Rule{
    private:
        struct Data{
            vector<RightAssociate<t>> right;
            vector<function<t (const Parser<t>&)>> action;
            NonTerminal<t>* left=nullptr;

            Data()=default;
            ~Data()=default;
            Data(NonTerminal<t>* l):left{l}{}
            Data(NonTerminal<t>* l,vector<RightAssociate<t>> a,vector<RightAssociate<t>> b):left{l}{
                for(auto x:a)
                    right.push_back(x);
                for(auto x:b)
                    right.push_back(x);
            }
            Data(const Data& d):left{d.left}{
                for(auto x:d.action)
                    action.emplace_back(x);
                for(auto x:d.right){
                    right.push_back(x);
                }
            }


            Data(Data&& d):right{move(d.right)},action{move(d.action)},left{d.left}{
            }

            Data &operator=(const Data &d){
                for (auto x : d.action)
                    action.emplace_back(x);
                for (auto x : d.right)
                {
                    right.push_back(x);
                }
                left=d.left;
            }
            Data & operator=(const Data &&d){
                right = move(d.right);
                action = move(d.action);
                left = d.left;
                return *this;
            }

            friend ostream& operator<<(ostream& o,const Data& d){
                if(d.left!=nullptr)
                    o<<*d.left<<" -> ";
                for(auto r:d.right){
                    switch(r.first){
                        case RightAssociateType::TERMINAL: o<<get<Terminal<t>>(r.second);break;
                        case RightAssociateType::NONTERMINAL: o<<get<NonTerminal<t>>(r.second);break;
                    }
                    o<<" ";
                }
                return o;
            }
            friend Logger& operator<<(Logger& o,const Data& d){
                if(d.left!=nullptr)
                    o<<*d.left<<" -> ";
                for(auto r:d.right){
                    switch(r.first){
                        case RightAssociateType::TERMINAL: o<<get<Terminal<t>>(r.second);break;
                        case RightAssociateType::NONTERMINAL: o<<get<NonTerminal<t>>(r.second);break;
                    }
                    o<<" ";
                }
                return o;
            }

            bool operator==(const Data& d)const{
                if(left!=d.left || right.size()!=d.right.size())
                    return false;

                for(size_t i=0,j=right.size();i<j;i++)
                    if(right[i]!=d.right[i])
                        return false;
                
                return true;
            }

            bool operator!=(const Data& d)const{
                if (left != d.left || right.size() != d.right.size())
                    return false;
                return !(*this==d);
            }

            //Data(NonTerminal<t>* l){}
        };

        constexpr auto getType(Terminal<t>)const{
            return RightAssociateType::TERMINAL;
        }

        constexpr auto getType(NonTerminal<t>) const{
            return RightAssociateType::NONTERMINAL;
        }

        shared_ptr<Data> data;
        Rule(NonTerminal<t>* left,vector<RightAssociate<t>> a,vector<RightAssociate<t>> b):data{make_shared<Data>(left,a,b)}{}
    public:
        Rule():data{make_shared<Data>()}{}
        Rule(NonTerminal<t>* l):data{make_shared<Data>(l)}{}

        Rule(const Rule& r):data{r.data}{}
        Rule(Rule&& r):data{move(r.data)}{}

        Rule& operator=(const Rule& r){
            data=r.data;
            return *this;
        }

        Rule& operator=(Rule&& r){
            data=move(r.data);
            return *this;
        }

        bool operator<(Rule& r)const{
            return *this!=r;
        }



        template<typename ...V>
        Rule& add(isRightAssociate<t> auto x,V... y){
            data->right.push_back(pair{getType(x),x});
            return add(y...);
        }

        Rule& add(isRightAssociate<t> auto x){
            data->right.push_back(pair{getType(x),x});
            return *this;
        }
        
        Rule& add(){
            data->right.push_back(pair{RightAssociateType::TERMINAL,Terminal<t>::EPSILON});
            return *this;
        }

        Rule& add(RightAssociate<t>& r){
            data->right.push_back(r);
            return *this;
        }

        Rule& add(vector<RightAssociate<t>>& r){
            for(auto a:r)
                data->right.push_back(a);
            return *this;
        }

        Rule* getThis(){
            return this;
        }


        Rule& operator()(function<t (const Parser<t>&)> p){
            data->action.push_back(p);
            //cout<<data->action.size()<<endl;
            return *this;
        }


        t operator()(const Parser<t>& p)const{
            if(data!=nullptr && data->action.size()!=0)
                return data->action[data->action.size()-1](p);
            else 
                throw ActionNotSet{};
        }

        function<t (const Parser<t>&)>& getAction()const{
            return data->action.back();
        }

        bool hasAction()const{
            return data->action.size()>0;
        }

        void removeAction(){
            data->action.pop_back();
        }

        Rules<t>& operator|(const Rule& r)const{
            if(r.data->left==nullptr){
                r.data->left=data->left;
            }
            auto & x=data->left;
            auto & y=x->data;
        
            y->add(r);
            //cout<<"print"<<endl;
            /*
            if(data==nullptr)
                cout<<"1"<<endl;
            else if(data->left==nullptr)
                cout<<"2"<<endl;
            else if(data->left->data==nullptr)
                cout<<"3"<<endl;
            */
            return *y;
        }
        
        First<t> getFirst()const{
            if(data==nullptr)
                throw RulesNotFoundException{};
            //cout<<(data->right[0].first==RightAssociateType::NONTERMINAL)<<endl;
            if(data->right[0].first==RightAssociateType::NONTERMINAL){
                
                //cout<<"ok"<<endl;
                return std::get<NonTerminal<t>>(data->right[0].second).getFirst();
            }
            else 
                return std::get<Terminal<t>>(data->right[0].second).getFirst();
        }


        vector<RightAssociate<t>>& getRightAssociates()const{
            return data->right;
        }

        friend ostream& operator<<(ostream& o,const Rule& r){
            if(r.data!=nullptr)
                o<<*r.data;
            return o;
        }

        friend Logger& operator<<(Logger& o,const Rule& r){
            if(r.data!=nullptr)
                o<<*r.data;
            return o;
        }

        HandleRule<t> getHandleRule()const{
            return HandleRule<t>{data->left,{},getRightAssociates()};
        }

        bool operator==(const Rule& r)const{
            return data!=nullptr &&
                   r.data!=nullptr &&
                   *data==*r.data;
        }

        bool operator!=(const Rule& r) const
        {
            return data != nullptr &&
                   r.data != nullptr &&
                   *data != *r.data;
        }

        NonTerminal<t>& getLeft()const{
            return *data->left;
        }

        size_t getNumberOfNonTerminal()const{
            size_t i=0;

            for(auto k:getRightAssociates())
                if(isNonTerminal(k))
                    i++;
            return i;
        }

        bool isNull()const{
            return getRightAssociates().size()==1 && getRightAssociates()[0]==Terminal<t>::EPSILON;
        }
        bool isUnitProduction()const{
            return getRightAssociates().size() == 1 && getLeft().getRules().size()==1;
        }

        bool isLeftRecursion()const{
            return getLeft() == getRightAssociates()[0];
        }

        size_t countOccurence(const NonTerminal<t>& n)const{
            size_t o=0;
            for(const RightAssociate<t>& r:getRightAssociates())
                if(r==n)
                    o++;
            return o;
        }

        Rule removeFromOccurence(const NonTerminal<t> &n, size_t o)
        {
            //cout<<"checkpoint : removeFromOccurence ( "<<n<<" , "<<o<<" )"<<endl<<endl;
            size_t i = 0;
            Rule s{getLeft().getThis()};
            for (auto r : getRightAssociates()){
                //cout<<r<<endl;
                if (r == n){
                    //cout<<"checking : ok"<<endl<<endl;
                    i++;
                    if(i!=o)
                        s.add(r);
                }
                else
                    s.add(r);
            }
            //cout<<endl;
            if(hasAction())
                s(getAction());
            return s;
        }

        

        friend class Rules<t>;
        friend class NonTerminal<t>;
        friend class HandleRule<t>;
};

template<typename tt,template<typename xx>typename cc, typename... VV>requires isRightAssociate<cc<tt>,tt>
Rule<tt> add(cc<tt> x,VV... M){
    return Rule<tt>{}.add(x,M...);
}

template<typename tt,template<typename xx>typename cc> requires isRightAssociate<cc<tt>,tt>
Rule<tt> add(cc<tt> x){
    return Rule<tt>{}.add(x);
}

template<typename cc>
Rule<cc> add(){
    return Rule<cc>{}.add();
}



#endif // !_RULES_HPP_