#include "Graph.h"
#include "Node.h"
#include "Operator.h"
#include <iostream>
#include <iomanip>

//初始化placeholder
void Graph::iniplaceholder(std::string a){
    graph[a] = new Placeholder(a, this);
    nodes.push_back(graph[a]);
}

//初始化constant
void Graph::iniconstant(std::string a, float b){
    graph[a] = new Constant(a, b, this);
    nodes.push_back(graph[a]);
}

//初始化variable
void Graph::inivariable(std::string a, float b){
    graph[a] = new Variable(a, b, this);
    nodes.push_back(graph[a]);
}

//v型SETCONSTANT操作
void Graph::setconstant(std::string a, float b){
    graph[a]->value = b;
}

//v型SETANSWER操作
void Graph::setanswer(std::string a, int b){
    graph[a]->value = answers[b - 1];
}

//eval操作
float Graph::eval(std::string a, std::vector<std::pair<std::string, float>> b){
    //当没有修改时
    if(b.size() == 0){
        float res = graph[a]->eval();       //调用Node的eval()
        if(haserror){
            std::cout << error << std::endl;
        }
        else {
            std::cout << std::fixed << std::setprecision(4) << graph[a]->value<<std::endl;
        }
        //计算结束后重写初始化化变量状态
        for(auto i : caleds){
            if(i->notconst()){
                i->caled = false;
                i->setvalue(NAN);
            }
        }
        haserror = false;
        caleds.clear();
        return res;
    }
    //当有修改时，修改值
    for(auto i : b){
        graph[i.first]->setvalue(i.second);
    }
    float res = graph[a]->eval();           //调用Node的eval()
    if(haserror){
        std::cout << error << std::endl;
    }
    else {
        std::cout << std::fixed << std::setprecision(4) << graph[a]->value << std::endl;
    }
    
    //计算结束后重写初始化化变量状态
    for(auto i:caleds){
        if(i->notconst()){
            i->caled = false;
            i->setvalue(NAN);
        }
    }
    //清空caleds
    haserror = false;
    caleds.clear();
    return res;
}

void Graph::errorthrow(std::string a){
    if(haserror) return;
    error = a;
    haserror = true;
}

//增加answer
void Graph::addanswers(float a){
    answers.push_back(a);
}

//返回map
std::map<std::string,Node*>& Graph::getmap(){
    return graph;
}