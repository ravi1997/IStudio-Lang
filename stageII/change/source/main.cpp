// #define DEBUG 1

#include <parser.hpp>

#include <rule.cpp>
#include <rules.cpp>
#include <shared_ptr.cpp>
int main()
{
    try
    {
        N(functionDeclaration);
        N(constexprCheck);
        N(returnType);
        N(name);
        N(parameterList);
        N(exceptionSyntax);
        N(contracts);
        N(returnInitialisationType);
        N(Type);
        N(returnList);
        N(Initialisation);
        N(rdash);
        N(returnInitialisation);
        N(parameterInitialisation);
        N(pdash);
        N(parameterInitialisationType);
        N(exceptionListDash);
        N(exceptSyntax);
        N(ensureSyntax);
        N(pdash3);
        N(rdash6);
        N(functionDeclaration15);
        N(functionDeclaration1516);
        N(functionDeclaration151617);
        N(functionDeclaration15161718);
        N(functionDeclaration15161719);
        N(functionDeclaration151620);
        N(functionDeclaration15162021);
        N(functionDeclaration15162022);
        N(functionDeclaration1523);
        N(functionDeclaration152324);
        N(functionDeclaration152325);
        N(functionDeclaration1526);
        N(functionDeclaration152627);
        N(functionDeclaration152628);
        N(functionDeclaration1531);
        N(functionDeclaration153132);
        N(functionDeclaration153133);

        T(function, "function");
        T(squareOpen, "\\[");
        T(squareClose, "\\]");
        T(ID, "[_a-zA-Z][_a-zA-Z0-9]*");

        T(parenthesisOpen, "\\(");
        T(parenthesisClose, "\\)");

        T(curlyOpen, "\\{");
        T(curlyClose, "\\}");

        T(comma, ",");
        T(Return, "return");
        T(readOnly, "readonly");
        T(writeOnly, "writeonly");
        T(moveOnly, "moveonly");
        T(readWrite, "readwrite");
        T(readMove, "readmove");
        T(writeMove, "writemove");

        T(Export, "export");
        T(Constexpr, "constexpr");
        T(Consteval, "consteval");
        T(Nullptr, "nullptr");
        T(throws, "throws");
        T(Expect, "expect");
        T(Ensures, "ensures");

        T(Int_8, "int_8");
        T(Int_16, "int_16");
        T(Int_32, "int_32");
        T(Int_64, "int_64");

        T(Uint_8, "uint_8");
        T(Uint_16, "uint_16");
        T(Uint_32, "uint_32");
        T(Uint_64, "uint_64");

        T(char_8, "char_8");
        T(char_16, "char_16");
        T(char_32, "char_32");

        T(Float, "float");
        T(Double, "double");
        T(Byte, "byte");

        T(Equal, "=");
        T(colon, ":");

        T(identifier, "[a-zA-Z_][a-zA-Z0-9_]*");
        T(operatorOverload, "operator");

        functionDeclaration->add(function, functionDeclaration15);
        constexprCheck->add(Constexpr);
        constexprCheck->add(Consteval);
        returnType->add(returnInitialisationType, Type);
        returnType->add(squareOpen, returnList, squareClose);
        returnType->add(Type);
        name->add(identifier);
        name->add(operatorOverload);
        parameterList->add(Type, identifier, Initialisation);
        parameterList->add(parameterInitialisationType, Type, identifier, Initialisation);
        exceptionSyntax->add(throws, Type);
        contracts->add(ensureSyntax);
        contracts->add(exceptSyntax);
        returnInitialisationType->add(returnInitialisation);
        returnInitialisationType->add(squareOpen, returnInitialisation, squareClose);
        Type->add(Int_8);
        Type->add(Int_16);
        Type->add(Int_32);
        Type->add(Int_64);
        Type->add(Uint_8);
        Type->add(Uint_16);
        Type->add(Uint_32);
        Type->add(Uint_64);
        returnList->add(Type, identifier, Initialisation);
        returnList->add(returnInitialisationType, Type, identifier, Initialisation);
        rdash->add(comma, rdash6);
        returnInitialisation->add(readOnly);
        returnInitialisation->add(moveOnly);
        returnInitialisation->add(readMove);
        parameterInitialisation->add(readOnly);
        parameterInitialisation->add(moveOnly);
        parameterInitialisation->add(readMove);
        parameterInitialisation->add(writeOnly);
        parameterInitialisation->add(readWrite);
        parameterInitialisation->add(writeMove);
        pdash->add(comma, pdash3);
        parameterInitialisationType->add(parameterInitialisation);
        parameterInitialisationType->add(squareOpen, parameterInitialisation, squareClose);
        exceptionListDash->add(comma, Type);
        exceptSyntax->add(squareOpen, squareOpen, Expect, colon, squareClose, squareClose);
        ensureSyntax->add(squareOpen, squareOpen, Ensures, colon, squareClose, squareClose);
        pdash3->add(identifier, Initialisation);
        pdash3->add(Type, identifier, Initialisation);
        rdash6->add(identifier, Initialisation);
        rdash6->add(Type, identifier, Initialisation);
        functionDeclaration15->add(name, parenthesisOpen, functionDeclaration1526);
        functionDeclaration15->add(constexprCheck, functionDeclaration1516);
        functionDeclaration15->add(parenthesisOpen, functionDeclaration1523);
        functionDeclaration15->add(returnType, name, parenthesisOpen, functionDeclaration1531);
        functionDeclaration1516->add(parenthesisOpen, functionDeclaration151617);
        functionDeclaration1516->add(name, parenthesisOpen, functionDeclaration151620);
        functionDeclaration151617->add(contracts, curlyOpen, curlyClose);
        functionDeclaration151617->add(curlyOpen, curlyClose);
        functionDeclaration151617->add(parenthesisClose, functionDeclaration15161718);
        functionDeclaration151617->add(exceptionSyntax, functionDeclaration15161719);
        functionDeclaration15161718->add(contracts, curlyOpen, curlyClose);
        functionDeclaration15161718->add(curlyOpen, curlyClose);
        functionDeclaration15161718->add(curlyClose);
        functionDeclaration15161719->add(curlyOpen, curlyClose);
        functionDeclaration15161719->add(curlyClose);
        functionDeclaration151620->add(contracts, curlyOpen, curlyClose);
        functionDeclaration151620->add(curlyOpen, curlyClose);
        functionDeclaration151620->add(parenthesisClose, functionDeclaration15162021);
        functionDeclaration151620->add(exceptionSyntax, functionDeclaration15162022);
        functionDeclaration15162021->add(contracts, curlyOpen, curlyClose);
        functionDeclaration15162021->add(curlyOpen, curlyClose);
        functionDeclaration15162021->add(curlyClose);
        functionDeclaration15162022->add(curlyOpen, curlyClose);
        functionDeclaration15162022->add(curlyClose);
        functionDeclaration1523->add(contracts, curlyOpen, curlyClose);
        functionDeclaration1523->add(curlyOpen, curlyClose);
        functionDeclaration1523->add(parenthesisClose, functionDeclaration152324);
        functionDeclaration1523->add(exceptionSyntax, functionDeclaration152325);
        functionDeclaration152324->add(contracts, curlyOpen, curlyClose);
        functionDeclaration152324->add(curlyOpen, curlyClose);
        functionDeclaration152324->add(curlyClose);
        functionDeclaration152325->add(curlyOpen, curlyClose);
        functionDeclaration152325->add(curlyClose);
        functionDeclaration1526->add(contracts, curlyOpen, curlyClose);
        functionDeclaration1526->add(curlyOpen, curlyClose);
        functionDeclaration1526->add(parenthesisClose, functionDeclaration152627);
        functionDeclaration1526->add(exceptionSyntax, functionDeclaration152628);
        functionDeclaration152627->add(contracts, curlyOpen, curlyClose);
        functionDeclaration152627->add(curlyOpen, curlyClose);
        functionDeclaration152627->add(curlyClose);
        functionDeclaration152628->add(curlyOpen, curlyClose);
        functionDeclaration152628->add(curlyClose);
        functionDeclaration1531->add(contracts, curlyOpen, curlyClose);
        functionDeclaration1531->add(curlyOpen, curlyClose);
        functionDeclaration1531->add(parenthesisClose, functionDeclaration153132);
        functionDeclaration1531->add(exceptionSyntax, functionDeclaration153133);
        functionDeclaration153132->add(contracts, curlyOpen, curlyClose);
        functionDeclaration153132->add(curlyOpen, curlyClose);
        functionDeclaration153132->add(curlyClose);
        functionDeclaration153133->add(curlyOpen, curlyClose);
        functionDeclaration153133->add(curlyClose);

        Grammar<PARSERTYPE> g{
            {functionDeclaration,
             constexprCheck,
             returnType,
             name,
             parameterList,
             exceptionSyntax,
             contracts,
             returnInitialisationType,
             Type,
             returnList,
             Initialisation,
             rdash,
             returnInitialisation,
             parameterInitialisation,
             pdash,
             parameterInitialisationType,
             exceptionListDash,
             exceptSyntax,
             ensureSyntax,
             pdash3,
             rdash6,
             functionDeclaration15,
             functionDeclaration1516,
             functionDeclaration151617,
             functionDeclaration15161718,
             functionDeclaration15161719,
             functionDeclaration151620,
             functionDeclaration15162021,
             functionDeclaration15162022,
             functionDeclaration1523,
             functionDeclaration152324,
             functionDeclaration152325,
             functionDeclaration1526,
             functionDeclaration152627,
             functionDeclaration152628,
             functionDeclaration1531,
             functionDeclaration153132,
             functionDeclaration153133

            },
            {function,
             squareOpen,
             squareClose,
             ID,
             parenthesisOpen,
             parenthesisClose,
             curlyOpen,
             curlyClose,
             comma,
             Return,
             readOnly,
             writeOnly,
             moveOnly,
             readWrite,
             readMove,
             writeMove,
             Export,
             Constexpr,
             Consteval,
             Nullptr,
             throws,
             Expect,
             Ensures,
             Int_8,
             Int_16,
             Int_32,
             Int_64,
             Uint_8,
             Uint_16,
             Uint_32,
             Uint_64,
             char_8,
             char_16,
             char_32,
             Float,
             Double,
             Byte,
             Equal,
             comma,
             Return,
             identifier

            },

            functionDeclaration

        };
        PARSER p{g};
    }
    catch (FileNotFound f)
    {
        cerr << "IStudioLang : " << f << " not Found" << endl;
        return -1;
    }

    return 0;
}
