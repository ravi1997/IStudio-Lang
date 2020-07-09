#ifndef _CSV_HPP_
#define _CSV_HPP_ 1

#ifndef _OPTIONS_HPP_
#include"options.hpp"
#endif


class CSV{

    using Row = pair<string,string>;
    vector<Row> rows;

public:
    CSV(string file,Options o){

        ifstream fin(file,ios::in);
        if (!fin.is_open())
            throw FileNotFound{file};
        vector<string> row;
        string line, word, temp;
        Logger l;
        if(o.getLoggerFlag()){
            l =  o.getLoggerFile();
            l << "CSV status : started"<<Logger::endl;
            l << "File Opened : " << file << Logger::endl;
        }

        while (fin >> temp)
        {
            row.clear();
            getline(fin, line);
            stringstream s(temp);
            //cout << temp << endl;
            while (getline(s, word, ','))
                row.push_back(word);
            rows.push_back(pair{row[0],row[1]});
            if (o.getLoggerFlag())    
                l << row[0] << " : " << row[1] << Logger::endl;
        }
        if (o.getLoggerFlag())
        {
            l << "Records readed succeffully : " << rows.size() << Logger::endl;
            l << "File closed : " << file << Logger::endl;
        }
    }
 
    string operator[](const string s){
        for(auto [key,value]:rows)
            if(key==s)
                return value;
        throw SyntaxError{};
    }


    auto begin(){
        return rows.begin();
    }

    auto end(){
        return rows.end();
    }

    auto begin() const
    {
        return rows.begin();
    }

    auto end() const
    {
        return rows.end();
    }
};

#endif //! _CSV_HPP_