#ifndef _DAG_HPP_
#define _DAG_HPP_

#ifndef _TYPES_HPP_
#include <types.hpp>
#endif

class DAG{
private:
    struct Node{
        Token<DAG> data;
        Node *left=nullptr, *right=nullptr, *current=nullptr, *result=nullptr;
        Node(Token<DAG>&d):data{d}{}
    };
    Node* root=nullptr;

public:
    void setData(Token<DAG>&d){
        root=new Node{d};
    }
    void setLeft(DAG& d){
        d.root->result=root;
        root->left=d.root;
    }
    void setRight(DAG& d){
        d.root->result=root;
        root->right=d.root;
    }

};

#endif
