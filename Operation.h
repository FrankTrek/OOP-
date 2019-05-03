
//  Operation.h
//  OOP Computation Graph
//
//  Created by 鐜嬩竴璇?on 2019/4/13.
//  Copyright ? 2019 鐜嬩竴璇? All rights reserved.
//

//
//  Operation.h
//  鐪熸鐨勫ぇ浣滀笟
//
//  Created by 钄?on 2019/4/8.
//  Copyright ? 2019骞?钄? All rights reserved.
//
//4.12 灏唎peration绫荤殑鏋勯€犲嚱鏁扮敱浼犲紩鐢ㄦ敼涓轰紶鎸囬拡
//4.13 琛ュ厖浜嗘墍鏈変簩鍏冨嚱鏁颁互鍙奀OND鍑芥暟
#ifndef Operation_h
#define Operation_h
#include "BaseNode.h"
#include "Node.h"
#include <cmath>


namespace  Computational_Graph{
    
   
    class Addition : public Operation<float>{//鍔犲彿
        
    public:
        
        Addition(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Addition(const string& a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        
        float Forward() override{
            if(flag==false)                           //涓婁竴娆¤绠楀緱鍒扮殑缁撴灉涓嶅悎娉?
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){      //涓婁竴娆¤绠楀緱鍒扮粨鏋滀笖鍚堟硶
                return value;
            }
            
            else {                                     //绗竴娆¤闂繖涓妭鐐?
                SPointer temp1(input_nodes[0]);        //灏哤pointer杞寲涓篠pointer
                float a = temp1->Forward();     //寰楀埌鍏朵腑涓€涓弬鏁版暟鍊?
                if(fabs(a-Minus_Max)<eps){              //涓€涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);        //灏哤pointer杞寲涓篠pointer
                float b=temp2->Forward();      //寰楀埌绗簩涓弬鏁?
                if(fabs(b-Minus_Max)<eps){               //绗簩涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                value=a+b;
                if(value> - Minus_Max + eps||value < Minus_Max - eps)      //鑰冭檻缁撴灉瓒呰繃涓婁笅鐣?
                {
                    std::cerr<<"Numeric Limit Exceeded\n";
                    flag = false;
                    return Minus_Max;
                }
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Multiply: public Operation<float>{//涔樺彿
        
    public:
        
        Multiply(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Multiply(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        
        float Forward() override{
            if(flag==false)                         //涓婁竴娆¤绠楃粨鏋滀笉鍚堟硶
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){      //涓婃璁＄畻缁撴灉鍚堟硶
                return value;
            }
        
            else {                                   //绗竴娆¤闂繖涓妭鐐?
                SPointer temp1(input_nodes[0]);      //灏哤pointer杞寲涓篠pointer
                float a = temp1->Forward();   //寰楀埌绗竴涓弬鏁?
                if(fabs(a-Minus_Max)<eps){            //绗竴涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);     //灏哤pointer杞寲涓篠pointer
                float b = temp2->Forward();         //寰楀埌绗簩涓弬鏁?
                if(fabs(b-Minus_Max)<eps){           //绗簩涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                value=a*b;
                if(value> - Minus_Max + eps||value < Minus_Max - eps)      //鑰冭檻缁撴灉瓒呰繃涓婁笅鐣?
                {
                    std::cerr<<"Numeric Limit Exceeded\n";
                    flag = false;
                    return Minus_Max;
                }
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Minus: public Operation<float>{//鍑忓彿
        
    public:
        
        Minus(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Minus(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        
        float Forward() override{
            if(flag==false)                          //涓婃璁＄畻缁撴灉涓嶅悎娉?
                return Minus_Max;
            else if(fabs(value-Minus_Max>eps)){       //涓婁竴娆¤绠楃粨鏋滃悎娉?
                return value;
            }
            
            else {                                    //绗竴娆¤闂繖涓妭鐐?
                SPointer temp1(input_nodes[0]);         //灏哤pointer杞寲涓篠pointer
                float a = temp1->Forward();    //寰楀埌绗竴涓弬鏁?
                if(fabs(a-Minus_Max)<eps){             //绗竴涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);       //灏哤pointer杞寲涓篠pointer
                float b=temp2->Forward();            //寰楀埌绗簩涓弬鏁?
                if(fabs(b-Minus_Max)<eps){              //绗簩涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                value=a-b;
                if(value> - Minus_Max + eps||value < Minus_Max - eps)      //鑰冭檻缁撴灉瓒呰繃涓婁笅鐣?
                {
                    std::cerr<<"Numeric Limit Exceeded\n";
                    flag = false;
                    return Minus_Max;
                }
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    
    
    class Division: public Operation<float>{//闄ゅ彿
        
    public:
        
        Division(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Division(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        
        float Forward() override{
            if(flag==false)                              //涓婁竴娆¤闂粨鏋滀笉鍚堟硶
                return Minus_Max;
            else if(fabs(value-Minus_Max>eps)){           //涓婁竴娆璁块棶缁撴灉鍚堟硶
                return value;
            }
            
            else {                                       //绗竴娆¤闂繖涓妭鐐?
                SPointer temp1(input_nodes[1]);          //灏哤pointer杞寲涓篠pointer
                float b = temp1->Forward(); 
                if(fabs(b-Minus_Max)<eps){                //绗竴涓弬鏁颁笉鍚堟硶
                    flag=false;
                   cout <<"!!!";           
                    return Minus_Max;
                }
              
                else if(fabs(b-0.0)<eps){                 //鍒嗘瘝涓?鐨勭壒娈婃儏鍐?
                    flag=false;
                    std::cout<<"ERROR: Division by zero"<<endl;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[0]);          //灏哤pointer杞寲涓篠pointer
                float a = temp2->Forward();    
		        //寰楀埌绗簩涓弬鏁?
                if(fabs(a-Minus_Max<eps)){                 //绗簩涓弬鏁癰涓嶅悎娉?
                    flag=false;
                    return Minus_Max;
                }
        
                
                value=a/b;
                if(value> - Minus_Max + eps||value < Minus_Max - eps)      //鑰冭檻缁撴灉瓒呰繃涓婁笅鐣?
                {
                    std::cerr<<"Numeric Limit Exceeded\n";
                    flag = false;
                    return Minus_Max;
                }
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    //-------------------------------------------------------------------
    //
    class Xiaoyu: public Operation<float>{//灏忎簬
    public:
        Xiaoyu(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Xiaoyu(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                             //涓婁竴娆¤闂粨鏋滀笉鍚堟硶
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){          //涓婁竴娆¤闂粨鏋滃悎娉?
                return value;
            }
            
            else {                                       //绗竴娆¤闂繖涓妭鐐?
                SPointer temp1(input_nodes[0]);          //灏哤pointer杞寲涓篠pointer
                float a = temp1->Forward();       //寰楀埌绗竴涓弬鏁?
                if(fabs(a-Minus_Max)<eps){                //绗竴涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);          //灏哤pointer杞寲涓篠pointer
                float b = temp2->Forward();        //寰楀埌绗簩涓弬鏁?
                if(fabs(b-Minus_Max)<eps){                 //绗簩涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                value=(a<b? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Xiaodeng: public Operation<float>{//灏忎簬绛変簬
    public:
        Xiaodeng(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Xiaodeng(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                             //涓婁竴娆¤闂粨鏋滀笉鍚堟硶
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){          //涓婁竴娆¤闂粨鏋滃悎娉?
                return value;
            }
            
            else {                                       //绗竴娆¤闂繖涓妭鐐?
                SPointer temp1(input_nodes[0]);          //灏哤pointer杞寲涓篠pointer
                float a = temp1->Forward();       //寰楀埌绗竴涓弬鏁?
                if(fabs(a-Minus_Max)<eps){                //绗竴涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);          //灏哤pointer杞寲涓篠pointer
                float b = temp2->Forward();        //寰楀埌绗簩涓弬鏁?
                if(fabs(b-Minus_Max)<eps){                 //绗簩涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                value=(a<=b? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Dayu: public Operation<float>{//澶т簬
    public:
        Dayu(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Dayu(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                             //涓婁竴娆¤闂粨鏋滀笉鍚堟硶
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){          //涓婁竴娆¤闂粨鏋滃悎娉?
                return value;
            }
            
            else {                                       //绗竴娆¤闂繖涓妭鐐?
                SPointer temp1(input_nodes[0]);          //灏哤pointer杞寲涓篠pointer
                float a = temp1->Forward();       //寰楀埌绗竴涓弬鏁?
                if(fabs(a-Minus_Max)<eps){                //绗竴涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);          //灏哤pointer杞寲涓篠pointer
                float b = temp2->Forward();        //寰楀埌绗簩涓弬鏁?
                if(fabs(b-Minus_Max)<eps){                 //绗簩涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                value=(a>b? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Dadeng: public Operation<float>{//澶т簬绛変簬
    public:
        Dadeng(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Dadeng(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                             //涓婁竴娆¤闂粨鏋滀笉鍚堟硶
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){          //涓婁竴娆¤闂粨鏋滃悎娉?
                return value;
            }
            
            else {                                       //绗竴娆¤闂繖涓妭鐐?
                SPointer temp1(input_nodes[0]);          //灏哤pointer杞寲涓篠pointer
                float a = temp1->Forward();       //寰楀埌绗竴涓弬鏁?
                if(fabs(a-Minus_Max)<eps){                //绗竴涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);          //灏哤pointer杞寲涓篠pointer
                float b = temp2->Forward();        //寰楀埌绗簩涓弬鏁?
                if(fabs(b-Minus_Max)<eps){                 //绗簩涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                value=(a>=b? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Dengyu: public Operation<float>{//绛変簬鍙?
    public:
        Dengyu(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Dengyu(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                             //涓婁竴娆¤闂粨鏋滀笉鍚堟硶
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){          //涓婁竴娆¤闂粨鏋滃悎娉?
                return value;
            }
            
            else {                                       //绗竴娆¤闂繖涓妭鐐?
                SPointer temp1(input_nodes[0]);          //灏哤pointer杞寲涓篠pointer
                float a = temp1->Forward();       //寰楀埌绗竴涓弬鏁?
                if(fabs(a-Minus_Max)<eps){                //绗竴涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);          //灏哤pointer杞寲涓篠pointer
                float b = temp2->Forward();        //寰楀埌绗簩涓弬鏁?
                if(fabs(b-Minus_Max)<eps){                 //绗簩涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                value=(a==b? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Budeng: public Operation<float>{//涓嶇瓑浜庡彿
    public:
        Budeng(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Budeng(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                             //涓婁竴娆¤闂粨鏋滀笉鍚堟硶
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){          //涓婁竴娆¤闂粨鏋滃悎娉?
                return value;
            }
            
            else {                                       //绗竴娆¤闂繖涓妭鐐?
                SPointer temp1(input_nodes[0]);          //灏哤pointer杞寲涓篠pointer
                float a = temp1->Forward();       //寰楀埌绗竴涓弬鏁?
                if(fabs(a-Minus_Max)<eps){                //绗竴涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);          //灏哤pointer杞寲涓篠pointer
                float b = temp2->Forward();        //寰楀埌绗簩涓弬鏁?
                if(fabs(b-Minus_Max)<eps){                 //绗簩涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                value=(a!=b? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    
    class COND: public Operation<float>{
    public:
        COND(SPointer Node1, SPointer Node2, SPointer Node3): Operation(Node1,Node2,Node3){}
        COND(const string a, SPointer Node1, SPointer Node2, SPointer Node3) : Operation(a, Node1,Node2, Node3){}
        float Forward() override{
            if(flag==false)                             //涓婁竴娆¤闂粨鏋滀笉鍚堟硶
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){          //涓婁竴娆璁块棶缁撴灉鍚堟硶
                return value;
            }
            
            else {                                      //绗竴娆¤闂繖涓妭鐐?
                bool flag_t = true;
                SPointer temp1(input_nodes[0]);  //灏哤pointer杞寲涓篠pointer
                float c = temp1->Forward();      //寰楀埌绗竴涓弬鏁?
                if(fabs(c-Minus_Max)<eps){           //寰楀埌绗竴涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                if(c > eps) flag_t=true;
                else if(c <= eps ) flag_t=false;
                SPointer temp2(input_nodes[1]);  //灏哤pointer杞寲涓篠pointer
                float a = temp2->Forward();    //寰楀埌绗?涓弬鏁?
                if(fabs(a-Minus_Max)<eps){             //寰楀埌绗?涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp3(input_nodes[2]);  //灏哤pointer杞寲涓篠pointer
                float b = temp3->Forward();     //寰楀埌绗?涓弬鏁?
                //      cout << b ;
                if(fabs(b-Minus_Max)<eps){              //寰楀埌绗?涓弬鏁颁笉鍚堟硶
                    flag=false;
                    return Minus_Max;
                }
                value=(flag_t? a:b);
                //        std::cout << " a" << a << " b" << b << " value" << value <<"\n" ;
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    
    
    
}
#endif /* Operation_h */
