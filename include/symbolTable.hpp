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
    variant<Variable,Function,Class,>
    void insert()
};


#endif
