#ifndef _SYMBOL_TABLE_HPP_
#define _SYMBOL_TABLE_HPP_


class SymbolTable{
    enum class Type{
        CLASS,
        FUNCTION,
        VARIABLE,
        UNION,
        INTERFACE
    };
    struct variable{
        string name;
        string file;
        unsigned int line;
        boolean known;
    };
    map<Type,Map<string,variable>> table;
};


#endif