#include "Newton.h"
#include <iomanip>

Newton::Newton(int nn) :n(nn){
    Timetag = 0;
    
} ;

void Newton::Construct_Stage1(){
    Nodes1.push_back(new Constant<float>("0|Nodes1",1.0f));
    Nodes1.push_back(new Placeholder<float>("x")) ;
    x = Nodes1[1] ;
    if(n <= 1) return ;
    for(int i = 2; i <= n ; i++){
        std::vector<Node<float>*>temp ;
        temp.push_back(Nodes1[1]) ;
        temp.push_back(Nodes1[i-1]) ;
        Nodes1.push_back(new MultipleOperator<float>(std::to_string(i)+"Nodes1",temp)) ;
    }
}

void Newton::Construct_Stage2(){
    for(int i = 0 ; i <= n ; i++ ){
        float temp ;
        std::cin >> temp ;
        Parameter.push_back(new Constant<float>(std::to_string(n-i)+"Parameter",temp)) ;
    }
}

void Newton::Construct_Stage3(){
    for(int i = 0 ; i <= n ; i++ ){
        std::vector<Node<float>*>temp ;
        temp.push_back(Parameter[n-i]) ;
        temp.push_back(Nodes1[i]) ;
        Nodes2.push_back(new MultipleOperator<float>(std::to_string(i)+"Nodes2",temp)) ;
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
        Nodes3.push_back(new PlusOperator<float>(std::to_string(i)+"Nodes3",temp)) ;
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
        
        float result = res->Calc(Timetag, ErrorSignal,&Order_of_Derive);//计算fxo
        if (ErrorSignal.size()) {
            std::cout << ErrorSignal << "\n";//如果建图有问题（在计算中显现）
            //感觉这里其实不会出现Error的情况，但仍然使用ErrorSignal进行了处理
            return;
        }
        res->SetGradi(1);
        for(int i = Order_of_Derive.size()-1;i>=0;i--)
        {
            Order_of_Derive[i]->Backward(Order_of_Derive[i]->GetGradi(), ErrorSignal);
        }
        x->GetGradi();
        Order_of_Derive.clear();
        temp = x0 - res->GetValue() / x->GetGradi();
        std::cout <<std::fixed<<std::setprecision(4)<<temp << " ";
        x0 = temp;
        ErrorSignal.clear();
        
    }
    std::cout << "\n";
    
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

void Newton::Delete() {
    for (auto i : Nodes1) {
        delete i;
    }
    for (auto i : Parameter) {
        delete i;
    }
    for (auto i : Nodes2) {
        delete i;
    }
    for (auto i : Nodes3) {
        delete i;
    }
}

Newton::~Newton() {
    x = nullptr;
    res = nullptr;
}
