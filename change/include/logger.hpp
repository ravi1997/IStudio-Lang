#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_ 1

#ifndef _TYPES_HPP_
#include <types.hpp>
#endif // !_TYPES_HPP_

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
    Logger(string s):type{Type::FILESTREAM},file{s,ios::out},fileName{s}{}

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
        static bool data=true;
        if(type==Type::FILESTREAM)
            file<<((data)?return_current_time_and_date():"")<<((data)?" : ":"")<<s;
        else
            cout<<((data)?return_current_time_and_date():"")<<((data)?" : ":"")<<s;
        if(data)
            data=false;
        if(s==Logger::endl)
            data=true;
        return *this;
    }

    Logger &operator<<(integral auto s){
        if (type == Type::FILESTREAM)
            file << to_string(s);
        else
            cout << to_string(s);
        return *this;
    }

        ~Logger()
    {
        if(type==Type::FILESTREAM)
            file.close();
    }

    constexpr static const char * endl="\n";
};

#endif
