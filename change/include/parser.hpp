#ifndef _PARSER_HPP_
#define _PARSER_HPP_ 1

#ifndef _OPTIONS_HPP_
#include <options.hpp>
#endif // !_OPTIONS_HPP_

#ifndef _LOGGER_HPP_
#include<logger.hpp>
#endif // !_LOGGER_HPP_

#ifndef _GRAMMAR_HPP_
#include <grammar.hpp>
#endif // !_Grammar_HPP_

#ifndef _HANDLE_RULE_HPP_
#include <handlerule.hpp>
#endif

        enum class ParserType
        {
            LL1,
            SLR,
            CLR
        };
        Logger &operator<<(Logger &o, ParserType p)
        {
            switch (p)
            {
            case ParserType::LL1:
                o << "LL1";
                break;
            case ParserType::SLR:
                o << "SLR";
                break;
            case ParserType::CLR:
                o << "CLR";
                break;
            }
            return o;
        }
template<typename t>
class Parser{
    public:



    private:
    mutable string code = "";
    mutable unsigned int line = 0;
    const string fileName;
    const Options options;
    vector<Terminal<t>> skipTerminals;
    Grammar<t> grammar;


    using LL1Parser=map<NonTerminal<t>,map<Terminal<t>,Rule<t>>>;

    using SLRState = vector<HandleRule<t>>;
    enum class SR{
        SHIFT,
        REDUCE
    };

    using SLRAction = map<SLRState,map<Terminal<t>,pair<SR,int>>>;
    using SLRGoto = map<SLRState, map<NonTerminal<t>, int>>;
    using SLRParser = pair<SLRAction, SLRGoto>;

    using LookAheads = vector<Terminal<t>>;
    using CLRState = vector<pair<HandleRule<t>, LookAheads>>;
    using CLRAction = map<CLRState, map<Terminal<t>, pair<SR, int>>>;
    using CLRGoto = map<CLRState, map<NonTerminal<t>, int>>;
    using CLRParser = pair<CLRAction, CLRGoto>;


    const ParserType parserType;
    variant<LL1Parser, SLRParser,CLRParser> table;

public:
    Parser(string f, Grammar<t> gg, vector<string> o, vector<Terminal<t>> ng, ParserType s=ParserType::CLR) : fileName{f}, options{o}, grammar{gg}, parserType{s}
    {
        Logger lg;
        auto x = options.getLogger();
        if (x)
            lg = options.getLoggerFile();

        if (x)
            lg << "Parsing started for : " << fileName << Logger::endl;

        ifstream file(fileName);
        if (!file.good())
            throw FileNotFound{};

        if (x)
            lg << "File Opened Successfully : " << fileName << Logger::endl;

        if (x)
            lg << "File character read : started" << Logger::endl;
        char c;
        while (file >> noskipws >> c)
            code += c;

        if (x)
            lg << "File character read : successfull" << Logger::endl;

        if (x)
            lg << "Skip Character read : started" << Logger::endl;

        for (auto st : ng)
            skipTerminals.push_back(st);

        if (x)
            lg << "Skip Character read : successfull" << Logger::endl;

        if (x)
            lg << "Parser Type : " << s << Logger::endl;
    }
};

ostream &operator<<(ostream &o,ParserType p)
{
    switch (p)
    {
    case ParserType::LL1:
        o << "LL1";
        break;
    case ParserType::SLR:
        o << "SLR";
        break;
    case ParserType::CLR:
        o << "CLR";
        break;
    }
    return o;
}

#endif // ! _PARSER_HPP_