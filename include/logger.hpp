#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_


class Logger{
private:
    enum class Type{
        ERRSTREAM,
        FILESTREAM,
        NETWORKSTREAM
    };
    Type type;
    ofstream file;
    string fileName;
    std::string return_current_time_and_date()
    {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        return ss.str();
    }
public:
    Logger():type{Type::ERRSTREAM}{}
    Logger(string s):type{Type::FILESTREAM},file{s,ios::app},fileName{s}{}

    Logger(const Logger& l):type{l.type},fileName{l.fileName}{
        if(type==Type::FILESTREAM)
            file.open(fileName,ios::app);
    }
    Logger(const Logger&& l):type{l.type},fileName{l.fileName}{
        if(type==Type::FILESTREAM)
            file.open(fileName,ios::app);
    }

    Logger& operator=(const Logger& l){
        if(type==Type::FILESTREAM)
            file.close();
        
        type=l.type;
        fileName=l.fileName;
        if(type==Type::FILESTREAM)
            file.open(fileName,ios::app);
        return *this;
    }

    Logger& operator=(const Logger&& l){
        if(type==Type::FILESTREAM)
            file.close();
        type=l.type;
        fileName=l.fileName;
        if(type==Type::FILESTREAM)
        file.open(fileName,ios::app);
        return *this;
    }

    Logger& operator<<(string s){
        if(type==Type::FILESTREAM)
            file<<return_current_time_and_date()<<" : "<<s<<endl;
        else
            cout<<return_current_time_and_date()<<" : "<<s<<endl;
        return *this;
    }


    ~Logger(){
        if(type==Type::FILESTREAM)
            file.close();
    }

};

#endif
