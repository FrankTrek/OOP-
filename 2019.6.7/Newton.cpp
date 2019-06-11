#include "Newton.h"

Newton::Newton(int nn) :n(nn){
    Timetag = 0;
} ;

void Newton::Construct_Stage1(){
    Nodes1.push_back(new Constant("0|Nodes1",1.0f));
    Nodes1.push_back(new Placeholder("x")) ;
    x = Nodes1[1] ;
    if(n <= 1) return ;
    for(int i = 2; i <= n ; i++){
        std::vector<Node<float>*>temp ;
        temp.push_back(Nodes1[1]) ;
        temp.push_back(Nodes1[i-1]) ;
        Nodes1.push_back(new MultipleOperator(std::to_string(i)+"Nodes1",temp)) ;
    }
}

void Newton::Construct_Stage2(){
    for(int i = 0 ; i <= n ; i++ ){
        float temp ;
        std::cin >> temp ;
        Parameter.push_back(new Constant(std::to_string(n-i)+"Parameter",temp)) ;
    }
}

void Newton::Construct_Stage3(){
    for(int i = 0 ; i <= n ; i++ ){
        std::vector<Node<float>*>temp ;
        temp.push_back(Parameter[n-i]) ;
        temp.push_back(Nodes1[i]) ;
        Nodes2.push_back(new MultipleOperator(std::to_string(i)+"Nodes2",temp)) ;
    }
    
}

void Newton::Construct_Stage4(){
    for(int i = 0 ; i <= n ; i++ ){
        if(i == 0 ){
            Nodes3.push_back(Nodes2[0]) ;
            continue ;
        }
        std::vector<Node<float>*>temp ;
        temp.push_back(Nodes2[i]) ;
        temp.push_back(Nodes3[i-1]) ;
        Nodes3.push_back(new PlusOperator(std::to_string(i)+"Nodes3",temp)) ;
    }
    res = Nodes3[n] ;
}

void Newton::Method()
{
    float x0;
    std::cin >> x0;
    for (int i = 1; i <= 5; i++) {
        float temp;
        Timetag++;//TimeTag的更新
        x->SetValue(x0, Timetag);//为变量赋值
        
        float result = res->Calc(Timetag, ErrorSignal);//计算fxo
        if (ErrorSignal.size()) {
            std::cout << ErrorSignal << "\n";//如果建图有问题（在计算中显现）
            //感觉这里其实不会出现Error的情况，但仍然使用ErrorSignal进行了处理
            return;
        }
        res->Backward(1, ErrorSignal);
        x->GetGradi();
        temp = x0 - res->GetValue() / x->GetGradi();
        std::cout << temp << " ";
        x0 = temp;
        ErrorSignal.clear();
        
    }
    
}


float Newton::debug_Cal(){
    Construct_Stage1() ;
    Construct_Stage2() ;
    Construct_Stage3() ;
    Construct_Stage4() ;
    float temp ;
    std::cin>>temp ;
    Nodes1[1]->SetValue(temp,1) ;
    float result ;
    std::string E ;
    result = res->Calc(1,E) ;
    return result ;
    
}

Newton::~Newton() {
    x = nullptr;
    res = nullptr;
}
/*
 void Newton::NewtonMethond(){
 float Init ;
 std::cin>>Init ;
 */
