#include<grammar.hpp>
#include<flowControl.hpp>
#include<terminal.cpp>

#include<nttype.hpp>

int main(int ,char**){


    try{

        N(functionDeclaration)
        N(exportCheck)
        N(constexprCheck)
        N(returnType)
        N(name)
        N(parameterList)
        N(exceptionSyntax)
        N(contracts)
        N(statements)
        N(statement)
        N(returnInitialisationType)
        N(returnInitialisationList)
        N(Type)
        N(returnList)
        N(Initialisation)
        N(rdash)
        N(returnInitialisation)
        N(parameterInitialisation)
        N(pdash)
        N(parameterInitialisationType)
        N(parameterInitialisationList)
        N(exceptionList)
        N(exceptionListDash)
        N(exceptSyntax)
        N(ensureSyntax)


        T(function, "function")
        T(squareOpen, "\\[")
        T(squareClose, "\\]")
        T(ID, "[_a-zA-Z][_a-zA-Z0-9]*")

        T(parenthesisOpen, "\\(")
        T(parenthesisClose, "\\)")

        T(curlyOpen, "\\{")
        T(curlyClose, "\\}")

        T(comma, ",")
        T(Return, "return")
        T(readOnly, "readonly")
        T(writeOnly, "writeonly")
        T(moveOnly, "moveonly")
        T(readWrite, "readwrite")
        T(readMove, "readmove")
        T(writeMove, "writemove")

        T(Export, "export")
        T(Constexpr, "constexpr")
        T(Consteval, "consteval")
        T(Nullptr, "nullptr")
        T(throws, "throws")
        T(Expect, "expect")
        T(Ensures, "ensures")

        T(Int_8, "int_8")
        T(Int_16, "int_16")
        T(Int_32, "int_32")
        T(Int_64, "int_64")

        T(Uint_8, "uint_8")
        T(Uint_16, "uint_16")
        T(Uint_32, "uint_32")
        T(Uint_64, "uint_64")

        T(char_8, "char_8")
        T(char_16, "char_16")
        T(char_32, "char_32")

        T(Float, "float")
        T(Double, "double")
        T(Byte, "byte")

        T(Equal, "=")
        T(colan, ":")

        T(identifier, "[a-zA-Z_][a-zA-Z0-9_]*")

        T(operatorOverload, "operatorOverload")

        functionDeclaration->add(function, exportCheck,constexprCheck,returnType,
                                name,parenthesisOpen,parameterList,parenthesisClose,
                                exceptionSyntax,contracts,curlyOpen,statements,curlyClose
                                );
        exportCheck->add()
                    |add(Export)
                    ;

        constexprCheck->add()
                        |add(Constexpr)
                        |add(Consteval)
                        ;
        
        returnType->add()
                    |add(returnInitialisationType,Type)
                    |add(squareOpen,returnList,squareClose)
                    ;
        
        returnList->add(returnInitialisationType,Type,identifier,Initialisation,rdash);

        rdash->add()
              |add(comma,returnInitialisationType,Type,identifier,Initialisation,rdash)
              ;
        
        name->add(identifier)
             |add(operatorOverload)
             ;
    
        returnInitialisationType->add()
                                 |add(returnInitialisation)
                                 |add(squareOpen,returnInitialisationList,squareClose)
                                 ;
        
        returnInitialisation->add(readOnly)
                             |add(moveOnly)
                             |add(readMove)
                             ;

        returnInitialisationList->add(returnInitialisation)
                                 |add(returnInitialisation,returnInitialisationList)
                                 ;

        parameterList->add()
                      |add(parameterInitialisationType,Type,identifier,Initialisation,pdash)
                      ;
        
        pdash->add()
              |add(comma,parameterInitialisationType,Type,identifier,Initialisation,pdash)
              ;

        parameterInitialisationType->add()
                                    |add(parameterInitialisation)
                                    |add(squareOpen,parameterInitialisationList,squareClose)
                                    ;

        parameterInitialisation->add(readOnly)
                                |add(moveOnly)
                                |add(readMove)
                                |add(writeOnly)
                                |add(readWrite)
                                |add(writeMove)
                                ;
        
        parameterInitialisationList->add(parameterInitialisation)
                                    |add(parameterInitialisation, parameterInitialisationList)
                                    ;
        
        exceptionSyntax->add()
                        |add(throws,exceptionList)
                        ;
        
        exceptionList->add(Type,exceptionListDash);
        exceptionListDash->add()
                          |add(comma,Type,exceptionListDash)
                          ;
        
        contracts->add()
                  |add(exceptSyntax,ensureSyntax)
                  |add(exceptSyntax)
                  |add(ensureSyntax)
                  ;

        exceptSyntax->add(squareOpen, squareOpen, Expect, colan, statement, squareClose, squareClose);
        ensureSyntax->add(squareOpen, squareOpen, Ensures, colan, statement, squareClose, squareClose);

        statements->add();
        statement->add();

        Type->add(Int_8)
             |add(Int_16)
             |add(Int_32)
             |add(Int_64)
             |add(Uint_8)
             |add(Uint_16)
             |add(Uint_32)
             |add(Uint_64)
             ;

        Grammar<PARSERTYPE>
            g{
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
                    identifier
                },
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
                    ensureSyntax
                },
                functionDeclaration
            };

        //g.removeLeftRecursion();

        Grammar x=g.reduce();
        
        //x.removeRedundant();
        
        cout<<x<<endl;
    }
    catch (FileNotFound f)
    {
        cerr << "IStudioLang : "<<f<<" not Found" << endl;
        return -1;
    }
    catch (HelpOption)
    {
        cout << "IStudioLang (1.0.1)" << endl;
        cout << "It is a compiler that works for IStudio language" << endl
             << endl;
        cout << "Command : IStudioLang [options] filename" << endl
             << endl;
        cout << "Options" << endl;
        cout << "\t[-g][-gdb]\t\tDebug options" << endl;
        cout << "\t[-h][-help]\t\tShow this help" << endl;
        cout << "\t[-I][-input]\t\tInput options" << endl;
        cout << "\t[-o][-output]\t\tOutput file options" << endl;
        cout << "\t[-l][-logger]\t\tLogger file options" << endl
             << endl;
        return 0;
    }

    return 0;
}