#ifndef _FLOW_CONTROL_HPP_
#define _FLOW_CONTROL_HPP_

#ifndef _TYPES_HPP_
#include<types.hpp>
#endif

#ifndef _DAG_HPP_
#include<DAG.hpp>
#endif

class FlowControlNode{
  private:
    bool boolean=false;
    vector<Token<FlowControlNode>> buffer;
    DAG dag;
  public:
    FlowControlNode()=default;
    FlowControlNode(const FlowControlNode& f):
          boolean{f.getBoolean()},
          dag{f.getDAG()}
          {
              for(auto T:f.getBuffer())
                buffer.push_back(T);
          }
    
    FlowControlNode(FlowControlNode&& f):
          boolean{f.boolean},
          buffer{move(f.buffer)},
          dag{move(f.dag)}
          {}
    
    FlowControlNode& operator=(const FlowControlNode& f){
      boolean=f.getBoolean();
      for (auto T : f.getBuffer())
        buffer.push_back(T);
      dag=f.getDAG();
      return *this;
    }
    FlowControlNode &operator=(FlowControlNode &&f)
    {
      boolean = f.getBoolean();
      buffer= move(f.buffer);
      dag = move(f.dag);
      return *this;
    }
    ~FlowControlNode()=default;

    FlowControlNode(bool b) : boolean{b} {}
    FlowControlNode(vector<Token<FlowControlNode>> b)
    {
      for(auto T:b)
        buffer.push_back(T);
    }
    FlowControlNode(DAG b) : dag{b} {}

    void setBoolean(bool b){
      boolean=b;
    }
    
    void setDAG(DAG b){
      dag = b;
    }

    void setBuffer(vector<Token<FlowControlNode>> b){
      buffer.clear();
      for(auto T:b)
        buffer.push_back(T);
    }

    const bool& getBoolean()const{
      return boolean;
    }

    const vector<Token<FlowControlNode>>& getBuffer()const{
      return buffer;
    }

    const DAG& getDAG()const{
      return dag;
    }
};

#endif
