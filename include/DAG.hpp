#ifndef _DAG_HPP_
#define _DAG_HPP_

class DAG{
private:
    struct Node{
        Token data;
        shared_ptr<Node> left, right, current, result;
        Node(Token&t):data{t}{}
    };
    shared_ptr<Node> root;

public:
    void setData(Token&t){
        root->data=t;
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
