#ifndef _HANDLE_RULE_HPP_
#define _HANDLE_RULE_HPP_ 1

#ifndef _RULE_HPP_
#include <rule.hpp>
#endif // !_RULE_HPP_

template <typename t>

class HandleRule
{
    struct Data
    {
        vector<RightAssociate<t>> beforeHandle, AfterHandle;
        //vector<function<t(const Parser<t> &)>> action;
        NonTerminal<t> *left = nullptr;
        Data() = default;
        Data(NonTerminal<t> *l, vector<RightAssociate<t>> b, vector<RightAssociate<t>> a) : beforeHandle{b},
                                                                                            AfterHandle{a},
                                                                                            left{l}
        {
        }

        Data(const Data &d) : left{d.left}
        {
            for (auto x : d.beforeHandle)
                beforeHandle.emplace_back(x);
            for (auto x : d.AfterHandle)
                AfterHandle.push_back(x);
        }
        Data(const Data &&d) : beforeHandle{move(d.beforeHandle)},
                               AfterHandle{move(d.AfterHandle)},
                               left{move(d.left)}
        {
        }
        Data &operator=(const Data &d)
        {

            for (auto x : d.beforeHandle)
                beforeHandle.emplace_back(x);
            for (auto x : d.AfterHandle)
                AfterHandle.push_back(x);
        }
        ~Data() = default;

        bool operator==(const Data& d) const
        {
            //cout << (left != d.left || beforeHandle.size() != d.beforeHandle.size() || AfterHandle.size() != d.AfterHandle.size())<<endl;
            if (left != d.left || beforeHandle.size() != d.beforeHandle.size() || AfterHandle.size() != d.AfterHandle.size()) return false;


            for (int j = 0, i = beforeHandle.size(); j < i; j++)
                if (beforeHandle[j] != d.beforeHandle[j])
                    return false;

            //cout << AfterHandle.size() << endl;
            //cout<<"ok"<<endl;

            for (int j = 0, i = AfterHandle.size(); j < i; j++){
                //cout<<"ok"<<endl;
                if (AfterHandle[j] != d.AfterHandle[j])
                    return false;
            }

            return true;
        }
        bool operator!=(const Data& d) const
        {
            return !(*this == d);
        }

        friend Logger& operator<<(Logger& l,Data& d){
            if(d.left!=nullptr){
                l<<*d.left<<" -> ";

                for(auto r:d.beforeHandle)
                    l<<r<<" ";
                l<<". ";
                for (auto r : d.AfterHandle)
                    l << r << " ";
            }
            
            return l;
        }
        friend ostream &operator<<(ostream &l, Data &d)
        {
            if (d.left != nullptr)
            {
                l << *d.left << " -> ";

                for (auto r : d.beforeHandle)
                    l << r << " ";
                l << ". ";
                for (auto r : d.AfterHandle)
                    l << r << " ";
            }

            return l;
        }
    };
    shared_ptr<Data> data;

public:
    HandleRule() = default;
    HandleRule(NonTerminal<t> *l, vector<RightAssociate<t>> b, vector<RightAssociate<t>> a) : data{make_shared<Data>(l, b, a)} {}

    RightAssociate<t> &getNextSymbol() const
    {
        if (data == nullptr)
            throw RulesNotFoundException{};
        if (data->AfterHandle.size() == 0)
            throw Empty{};
        return data->AfterHandle[0];
    }

    bool isGoto() const
    {
        try
        {
            bool h = (getNextSymbol().first == RightAssociateType::NONTERMINAL);
            return h;
        }
        catch (...)
        {
            return false;
        }
    }

    bool isAction() const
    {
        return !isGoto();
    }

    State<t> getState(const Grammar<t>& g, LookAheads<t> ts)const 
    {
        State<t> I;
        I.push_back(pair{*this, ts});
        //cout << *this << endl;

        if (data->AfterHandle.size() > 0)
        {
            //cout<<"1"<<endl;
            auto [x, y] = getNextSymbol();
            //cout<<x<<endl;
            if (x == RightAssociateType::NONTERMINAL)
            {
                //cout<<"2"<<endl;
                for (auto r : get<NonTerminal<t>>(y).getRules()){
                    //cout<<"3"<<endl;
                    if (find(I.begin(), I.end(), pair{r.getHandleRule(), getLookheads()}) == I.end())
                    {
                        //cout<<4<<endl;
                        LookAheads<t> ls = getLookheads();
                        if (find(ls.begin(), ls.end(), Terminal<t>::EPSILON) != ls.end())
                        {
                            //cout<<5<<endl;
                            ls.erase(find(ls.begin(), ls.end(), Terminal<t>::EPSILON));

                            for (auto t1 : ts)
                                ls.push_back(t1);
                        }
                        I.push_back(pair{r.getHandleRule(), ls});
                        State<t> temp = r.getHandleRule().getState(g, move(ls));
                        //cout<<temp.size()<<endl;
                        if(temp.size()>0)
                            for(auto rs:temp){
                                if(!find(I,rs)){
                                    //cout<<"ok"<<endl;
                                    I.push_back(rs);
                                }
                            }
                            //I.insert(I.end(), temp.begin(), temp.end());
                        //cout<<6<<endl;
                    }
                }
            }
            //cout<<7<<endl;
        }
        //cout<<8<<endl;
        return I;
    }

    LookAheads<t> getLookheads() const
    {
        bool flag=false;
        LookAheads<t> ls;

        if (data->AfterHandle.size() > 1)
        {
            size_t i = 1;
            do
            {
                for(auto t1:getFirst(data->AfterHandle[i]))
                    ls.push_back(t1);

                if (find(ls.begin(), ls.end(), Terminal<t>::EPSILON) == ls.end()){
                    flag=false;
                    break;
                }
                else{
                    flag=true;
                    ls.erase(find(ls.begin(), ls.end(), Terminal<t>::EPSILON));
                }
                i++;
            } while (i < ls.size());
        }
        if(flag)
            ls.push_back(Terminal<t>::EPSILON);
        return (ls.size() > 0) ? move(ls) : LookAheads<t>{Terminal<t>::EPSILON};
    }

    HandleRule getShiftedHandleRule() const
    {
        vector<RightAssociate<t>> x = data->beforeHandle;
        vector<RightAssociate<t>> y = data->AfterHandle;
        x.push_back(y[0]);
        y.erase(y.begin());
        return HandleRule{data->left, x, y};
    }

    bool operator==(const HandleRule& h) const
    {
        //cout<< *this <<" == "<<h<<endl;
        //cout<<(h.data!=nullptr)<<endl;
        return data != nullptr &&
               h.data != nullptr &&
               *data == *h.data;
    }
    bool operator!=(const HandleRule& h) const
    {
        return data != nullptr &&
               h.data != nullptr &&
               !(*this == h);
    }



    friend Logger& operator<<(Logger& l,HandleRule h){
        if(h.data!=nullptr)
            l<<*h.data;
        return l;
    }
    
    friend ostream &operator<<(ostream &l, HandleRule h)
    {
        if (h.data != nullptr)
            l << *h.data;
        return l;
    }
    Rule<t> getRule()const{
        return Rule<t>{data->left,data->beforeHandle,data->AfterHandle};
    }
};

template <typename t>
vector<NonTerminal<t>> getGoto(State<t> I)
{
    vector<NonTerminal<t>> f;
    for (auto x : I)
    {
        if (x.first.isGoto())
        {
            try
            {
                f.push_back(get<NonTerminal<t>>(x.first.getNextSymbol().second));
            }
            catch (...)
            {
            }
        }
    }
    return f;
}

template <typename t>
vector<Terminal<t>> getAction(State<t> I)
{
    vector<Terminal<t>> f;
    for (auto x : I)
    {
        if (x.first.isAction())
        {
            try
            {
                f.push_back(get<Terminal<t>>(x.first.getNextSymbol().second));
            }
            catch (...)
            {
            }
        }
    }
    return f;
}

template <typename t>
State<t> getNextState(Grammar<t> g, State<t> I, NonTerminal<t> n)
{
    State<t> f;
    f.clear();
    for (auto& x : I)
    {
        try
        {
            if (x.first.getNextSymbol() == n)
            {
                //f.push_back(x);
                auto h = x.first.getShiftedHandleRule();
                State<t> temp = h.getState(g, x.second);
                //cout<<endl<<temp<<endl;

                for (auto t1 : temp)
                    f.push_back(t1);
                
               // cout<<endl<<endl<<f<<endl<<endl;
            }
        }
        catch (...)
        {
        }
    }
    return f;
}

template <typename t>
State<t> getNextState(Grammar<t> g, State<t> I, Terminal<t> n)
{
    State<t> f;
    for (auto x : I)
    {
        if (x.first.getNextSymbol() == n)
        {
            //f.push_back(x);
            auto h = x.first.getShiftedHandleRule();
            State<t> temp = h.getState(g, x.second);
            //cout<<endl<<temp<<endl;

            for (auto t1 : temp)
                f.push_back(t1);
            
            //cout<<endl<<endl<<f<<endl<<endl;

        }
    }
    return f;
}

template <typename t>
SR getSR(State<t> I)
{
    bool s = false, r = false;

    for (auto z : I)
    {
        try
        {
            z.first.getNextSymbol();
            s = true;
        }
        catch (...)
        {
            if(r)
                throw ReduceReduce{};
            r = true;
            
        }
    }
    if (s && r)
        throw ShiftReduce{};
    else if (s)
        return SR::SHIFT;
    else
        return SR::REDUCE;
}

template<typename t>
bool operator<(const State<t> a,const State<t> b){
    if(a.size()!=b.size())
        return false;
    for(size_t i=0,j=b.size();i<j;i++)
        if(a[i].first!=b[i].first)
            return true;
    
    return false;
}

template<typename t>
bool find(State<t> s,pair<HandleRule<t>,LookAheads<t>> r){
    /*cout<<s<<endl;
    State<t> rs=State<t>{r};
    cout<<endl<<rs<<endl;
    */
    for(auto [x,y]: s){
        if(r.first==x){
            //cout<<"ok"<<endl;
            if(r.second.size()==y.size()){
                size_t size=y.size();
                for(;size>0;size--){
                    if(r.second[size-1]!=y[size-1])
                        break;
                }
                if(size==0)
                    return true;
            }
        }
    }
    return false;
}

template<typename t>
bool find(vector<State<t>> states,State<t> I){

    for(auto s:states){
        size_t i = 0;
        for(auto [x,y]:s){
            if(x==I[i].first){
                size_t j=0;
                for(auto l:y){
                    if (l != I[i].second[j])
                        break;
                    j++;
                }
                if(j==y.size())
                    return true;
            }
        }
    }
    return false;
}

#endif // !_HANDLE_RULE_HPP_