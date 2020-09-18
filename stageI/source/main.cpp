// #define DEBUG 1

#include <grammar.hpp>

#include <rule.cpp>
#include <rules.cpp>
#include <shared_ptr.cpp>
int main()
{
    try
    {
        N(functionDeclaration);
        N(exportCheck);
        N(constexprCheck);
        N(returnType);
        N(name);
        N(parameterList);
        N(exceptionSyntax);
        N(contracts);
        N(statements);
        N(statement);
        N(returnInitialisationType);
        N(returnInitialisationList);
        N(Type);
        N(returnList);
        N(Initialisation);
        N(rdash);
        N(returnInitialisation);
        N(parameterInitialisation);
        N(pdash);
        N(parameterInitialisationType);
        N(parameterInitialisationList);
        N(exceptionList);
        N(exceptionListDash);
        N(exceptSyntax);
        N(ensureSyntax);

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

        T(operatorOverload, "operatorOverload");

        statements->add();
        functionDeclaration->add(function, exportCheck, constexprCheck, returnType,
                                 name, parenthesisOpen, parameterList, parenthesisClose,
                                 exceptionSyntax, contracts, curlyOpen, statements, curlyClose);
        exportCheck->add() | add(Export);

        constexprCheck->add() | add(Constexpr) | add(Consteval);

        returnType->add() | add(returnInitialisationType, Type) | add(squareOpen, returnList, squareClose);

        returnList->add(returnInitialisationType, Type, identifier, Initialisation, rdash);

        rdash->add() | add(comma, returnInitialisationType, Type, identifier, Initialisation, rdash);

        name->add(identifier) | add(operatorOverload);

        returnInitialisationType->add() | add(returnInitialisation) | add(squareOpen, returnInitialisationList, squareClose);

        returnInitialisation->add(readOnly) | add(moveOnly) | add(readMove);

        returnInitialisationList->add(returnInitialisation) | add(returnInitialisation, returnInitialisationList);

        parameterList->add() | add(parameterInitialisationType, Type, identifier, Initialisation, pdash);

        pdash->add() | add(comma, parameterInitialisationType, Type, identifier, Initialisation, pdash);

        parameterInitialisationType->add() | add(parameterInitialisation) | add(squareOpen, parameterInitialisationList, squareClose);

        parameterInitialisation->add(readOnly) | add(moveOnly) | add(readMove) | add(writeOnly) | add(readWrite) | add(writeMove);

        parameterInitialisationList->add(parameterInitialisation) | add(parameterInitialisation, parameterInitialisationList);

        exceptionSyntax->add() | add(throws, exceptionList);

        exceptionList->add(Type, exceptionListDash);
        exceptionListDash->add() | add(comma, Type, exceptionListDash);

        contracts->add() | add(exceptSyntax, ensureSyntax) | add(exceptSyntax) | add(ensureSyntax);

        exceptSyntax->add(squareOpen, squareOpen, Expect, colon, statement, squareClose, squareClose);
        ensureSyntax->add(squareOpen, squareOpen, Ensures, colon, statement, squareClose, squareClose);

        statement->add();

        Type->add(Int_8) | add(Int_16) | add(Int_32) | add(Int_64) | add(Uint_8) | add(Uint_16) | add(Uint_32) | add(Uint_64);

        Grammar<PARSERTYPE>
            g{
                {
                    functionDeclaration,
                    exportCheck,
                    constexprCheck,
                    returnType,
                    name,
                    parameterList,
                    exceptionSyntax,
                    contracts,
                    statements,
                    statement,
                    returnInitialisationType,
                    returnInitialisationList,
                    Type,
                    returnList,
                    Initialisation,
                    rdash,
                    returnInitialisation,
                    parameterInitialisation,
                    pdash,
                    parameterInitialisationType,
                    parameterInitialisationList,
                    exceptionList,
                    exceptionListDash,
                    exceptSyntax,
                    ensureSyntax,

                },
                {
                    function,
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
                    identifier,

                },

                functionDeclaration

            };

        Grammar x = g.reduce();

        ofstream ntFile{"output/nonTerminal.txt", ios::out};

        for (auto nts : x.getNonTerminals())
            ntFile << nts << endl;

        ntFile.close();

        ofstream tFile{"output/terminal.txt", ios::out};

        for (auto nts : x.getTerminals())
            tFile << nts << endl;

        tFile.close();

        ofstream rFile{"output/rules.txt", ios::out};

        for (auto nts : x.getNonTerminals())
        {
            for (auto rts : nts.getRules())
                rFile << rts << endl;
        }
        rFile.close();
    }
    catch (FileNotFound f)
    {
        cerr << "IStudioLang : " << f << " not Found" << endl;
        return -1;
    }

    return 0;
}
