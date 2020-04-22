#ifndef _FLOW_CONTROL_HPP_
#define _FLOW_CONTROL_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif

#ifndef _DAG_HPP_
#include<DAG.hpp>
#endif

class FlowControl{
    struct Node{
        vector<DAG> dag;
        Node* next=nullptr;
    };
    Node* root=nullptr;
  public:
    FlowControl(){}
    FlowControl(const FlowControl& f){
      if(f.root!=nullptr){
        auto t=f.root;
        root=new Node{};
        auto z=root;
        while(t!=nullptr){
          for(auto d:t->dag)
            z->dag.push_back(d);
          t=t->next;
          if(t!=nullptr){
            z->next=new Node{};
            z=z->next;
          }
        }
      }
    }
    FlowControl(FlowControl&& f):root{f.root}{
      f.root=nullptr;
    }
    FlowControl& operator=(const FlowControl& f){
      while(root!=nullptr){
        auto t=root;
        root=root->next;
        delete t;
      }
      if(f.root!=nullptr){
        auto t=f.root;
        root=new Node{};
        auto z=root;
        while(t!=nullptr){
          for(auto d:t->dag)
            z->dag.push_back(d);
          t=t->next;
          if(t!=nullptr){
            z->next=new Node{};
            z=z->next;
          }
        }
      }
      return *this;
    }
    FlowControl& operator=(FlowControl&& f){
      while(root!=nullptr){
        auto t=root;
        root=root->next;
        delete t;
      }
      root=f.root;
      f.root=nullptr;
      return *this;
    }
    ~FlowControl(){
      while(root!=nullptr){
        auto t=root;
        root=root->next;
        delete t;
      }
    }
};

#endif
