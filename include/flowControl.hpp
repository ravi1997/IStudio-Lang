#ifndef _FLOW_CONTROL_HPP_
#define _FLOW_CONTROL_HPP_

class FlowControl{
    struct Node{
        vector<DAG> dags;
        Node* next=nullptr;
    };
    Node* root=nullptr;
    
};

#endif