#ifndef _RULES_HPP_
#define _RULES_HPP_ 1

#ifndef _TYPES_HPP_
#include <types.hpp>
#endif // !_TYPES_HPP_

template<typename t>
class Rules{
    private:
        shared_ptr<vector<Rule<t>>> data;

    public:

    Rules():data{make_shared<vector<Rule<t>>>()}{}
    Rules(const Rules &d) : data{d.data} {}
    Rules(const Rules &&d) : data{move(d.data)} {}
    Rules& operator=(const Rules &d){
        data.reset();
        data=d.data;
        return *this;
    }
    Rules &operator=(const Rules &&d)
    {
        data.reset();
        data = move(d.data);
        return *this;
    }

    ~Rules()=default;

    auto begin(){
        if(data==nullptr)
            throw RulesNotFoundException{};
        return data->begin();
    }


    auto end(){
        if (data == nullptr)
            throw RulesNotFoundException{};
        return data->end();
    }

    auto begin() const
    {
        if (data == nullptr)
            throw RulesNotFoundException{};
        return data->begin();
    }

    auto end() const
    {
        if (data == nullptr)
            throw RulesNotFoundException{};
        return data->end();
    }

    void add(const Rule<t>& r){
        if(data==nullptr)
            data=make_shared<vector<Rule<t>>>();

        data->push_back(r);
    }


    size_t size()const{
        if (data == nullptr)
            throw RulesNotFoundException{};

        return data->size();
    }

    auto& operator[](size_t i){
        if (data == nullptr)
            throw RulesNotFoundException{};

        return (*data)[i];
    }

    auto &operator[](size_t i)const
    {
        if (data == nullptr)
            throw RulesNotFoundException{};

        return (*data)[i];
    }

    Rules& operator|(const Rule<t> r){
        if(r.data->left==nullptr)
            r.data->left=(*data)[0].data->left;
        add(r);
        return *this;
    }


    First<t> getFirst()const{
        First<t> f;
        try{
            for(auto x:*this){
                ////cout<<x<<endl;
                try{
                    for(auto u:x.getFirst())
                        f.push_back(u);
                }catch(...){}
            }
        }catch(...){
        }
        return f;
    }


    bool operator==(const Rules& r) const{
        if(data==nullptr || r.data==nullptr)
            return false;
        if(data->size()!=r.data->size())
            return false;
        for (size_t i = 0, j = data->size();i<j;i++)
            if((*this)[i]!=r[i])
                return false;
        return true;
    }
    bool operator!=(const Rules& r)const
    {
        if (data == nullptr || r.data == nullptr)
            return false;
        if (data->size() != r.data->size())
            return false;
        return !(*this==r);
    }

    void remove(const Rule<t>& r){
        if(data!=nullptr){
            if(find(data->begin(),data->end(),r)!=data->end())
                data->erase(find(data->begin(), data->end(), r));
        }
    }

    void removeAll(){
        if(data!=nullptr){
            for(auto r:*this)
                r.getLeft().removeRule(r);

            data->clear();
        }
    }

    Rules returnReduceInner(const Rule<t> r){
        Rules rs;
        //cout<<"Checkpoint : returnReduceInner for "<<r<<endl;
        if(size()>0){
            for(auto i:*this){
                //cout<< i <<endl;

                if(i.countOccurence(r.getLeft())>0){
                    //cout<<"Occurence found are "<<i.countOccurence(r.getLeft())<<endl;
                    for (size_t j = i.countOccurence(r.getLeft());j>0;j--){
                        //cout << "adding new rule : " << i.removeFromOccurence(r.getLeft(), j) << endl;
                        rs.add(i.removeFromOccurence(r.getLeft(),j));
                        i.removeFromOccurence(r.getLeft(), j).getLeft()->add(i.removeFromOccurence(r.getLeft(), j).getRightAssociates());
                    }
                    //cout<<endl;
                }
            }
            if(rs.size()>0){
                rs.add(rs.returnReduceInner(r));
            }
        }

        //cout<<endl<<endl;
        return rs;
    }


    Rules returnReduce(const Rule<t> r){
        Rules rs;
        
        //cout<<"Checkpoint : returnReduce"<<endl;

        for(auto r1:*this)
            rs.add(r1);
        
        ////cout<<rs<<endl;

        Rules temp=returnReduceInner(r);

        ////cout<<endl<<temp<<endl;


        for (auto r1 : temp)
            rs.add(r1);

        return rs;
    }

    Rules returnReduceUnit(const Rule<t> r)
    {
        Rules rs;
        if (size() > 0)
        {
            for (auto i : *this)
            {
                Rule<t> temp{i.getLeft().getThis()};
                for(auto j:i.getRightAssociates())
                    if(j==r.getLeft())
                        temp.add(r.getRightAssociates()[0]);
                    else
                        temp.add(j);
                rs.add(temp);
                temp.getLeft().removeRule(i);
                temp.getLeft()->add(temp.getRightAssociates());
            }
        }

        ////cout<<endl<<temp<<endl;
        return rs;
    }

    void add(const Rules& r){
        try{
            if(data==nullptr){
                data=r.data;
            }
            else if(r.size()>0){
                for(auto i:r)
                    add(i);
            }

        }catch(...){}
    }

    friend ostream& operator<<(ostream& o,Rules rs){
        for(auto r:rs)
            o<<r<<endl;
        return o;
    }

    Rules& removeRedundant(){
        //sort( data->begin(), data->end() );
        auto ip = std::unique(data->begin(), data->end());
        data->resize(std::distance(data->begin(), ip));
        //data->erase( unique( data->begin(), data->end() ), data->end() );
        return *this;
    }

    friend class Grammar<t>;
};

#endif // !_RULES_HPP_