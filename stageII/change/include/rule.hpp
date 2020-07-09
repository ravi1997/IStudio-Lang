#ifndef _RULE_HPP_
#define _RULE_HPP_ 1

#ifndef _RIGHTASSCIATE_HPP_
#include<rightassociate.hpp>
#endif

template<typename t>
class Rule{
    private:
        using actionType=function<t (const Parser<t>&)>;
        struct  Data
        {
            vector<RightAssociate<t>> right;
            vector<actionType> action;
            NonTerminal<t>* left=nullptr;

        };
        constexpr auto getType(Terminal<t>) const
        {
            return RightAssociateType::TERMINAL;
        }

        constexpr auto getType(NonTerminal<t>) const
        {
            return RightAssociateType::NONTERMINAL;
        }

        constexpr auto getType(UnaryPost<t>) const
        {
            return RightAssociateType::UNARYPOST;
        }

        constexpr auto getType(UnaryPre<t>) const
        {
            return RightAssociateType::UNARYPRE;
        }

        constexpr auto getType(Binary<t>)const{
            return RightAssociateType::BINARY;
        }
        shared_ptr<Data> data;
    public:
        Rule():data{make_shared<Data>()}{}

        Rule(NonTerminal<t> *l) : data{make_shared<Data>()}
        {
            data->left = l;
        }
        Rule(const Rule& r):data{r.data}{}
        Rule(const Rule&& r):data{move(r.data)}{}

        Rule& operator=(const Rule& r){
            data=r.data;
            return *this;
        }

        Rule &operator=(const Rule &&r)
        {
            data = move(r.data);
            return *this;
        }

        Rule* getThis(){
            return this;
        }


        First<t> getFirst()const{
            if(data==nullptr)
                throw RulesNotFoundException{};
            First<t> f;
            bool flag=false;
            for(auto i:data->right){
                flag=false;
                switch(i.first){
                case RightAssociateType::TERMINAL:
                    f.insert(get<Terminal<t>>(i.second));
                    goto calculated;
                case RightAssociateType::NONTERMINAL:
                    {
                        auto n=get<NonTerminal<t>>(i.second);
                        auto z=n.getFirst();
                        for(auto x:z){
                            if(x==Terminal<t>::EPSILON)
                                flag=true;

                            f.insert(x);
                        }
                            
                        if (flag)
                            continue;
                        goto calculated;
                    }
                    break;
                case RightAssociateType::UNARYPOST:
                    f.insert(get<UnaryPost<t>>(i.second));
                    goto calculated;
                case RightAssociateType::UNARYPRE:
                    f.insert(get<UnaryPre<t>>(i.second));
                    goto calculated;
                case RightAssociateType::BINARY:
                    f.insert(get<Binary<t>>(i.second));
                    goto calculated;
                }
            }
            calculated:
            return f;
        }

        template <typename... V>
        Rule &add(isRightAssociate<t> auto x, V... y)
        {
            //cout<<x<<endl;
            if(x==Terminal<t>::EPSILON)
                throw RuleWithNull{};


            data->right.push_back(pair{getType(x), x});
            return add(y...);
        }

        Rule &add(isRightAssociate<t> auto x)
        {
            if (data->right.size() > 0 && x == Terminal<t>::EPSILON)
                throw RuleWithNull{};
            data->right.push_back(pair{getType(x), x});
            return *this;
        }

        Rule &add()
        {

            data->right.push_back(pair{RightAssociateType::TERMINAL, Terminal<t>::EPSILON});
            return *this;
        }

        Rules<t> &operator|(const Rule &r) const
        {
            if (r.data->left == nullptr)
            {
                r.data->left = data->left;
            }
            auto &x = data->left;
            auto &y = x->rules;
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


        friend Logger& operator<<(Logger& l,Rule r){
            if(r.data==nullptr)
                return l;
            l<<*r.data->left<<" -> ";
            for(auto rs:r.data->right)
                l<<rs<<" ";
            l<<Logger::endl;
            return l;
        }

        HandleRule<t> getHandleRule(){
            return HandleRule<t>{data->left,{},data->right};
        }

        friend class Rules<t>;
};

template <typename tt, template <typename xx> typename cc, typename... VV>
requires isRightAssociate<cc<tt>, tt>
    Rule<tt> add(cc<tt> x, VV... M)
{
    return Rule<tt>{}.add(x, M...);
}

template <typename tt, template <typename xx> typename cc>
requires isRightAssociate<cc<tt>, tt>
    Rule<tt> add(cc<tt> x)
{
    return Rule<tt>{}.add(x);
}

template <typename cc>
Rule<cc> add()
{
    return Rule<cc>{}.add();
}

#endif // !_RULE_HPP_