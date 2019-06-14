#ifndef NODE_H
#define NODE_H

#include<vector>
#include<string>

const float Epsi = 1e-7;

template <typename T>
class Node {
private:
	int Time;
	std::string Name;
	T Value;
    //add by Cai on 6.6
    T gradi=0;
    //
protected:
	std::vector<Node*> Pre;		//Pre: º∆À„ƒ≥Ω·µ„µƒValue“¿¿µµƒ«∞–ÚΩ·µ„
public:
    Node(){
        Name = "";
        Value = 0;
        Time = 0;
        Pre.clear();
    }
	Node(const std::string& InitName, const T& InitValue, const int& InitTime)
    {
        Name = InitName;
        Value = InitValue;
        Time = InitTime;
        Pre.clear();
    }
    T Calc(const int& CurTime, std::string& ErrorSignal, std::vector<Node<T>*>* Order_of_Derive = nullptr)
    {
        SetGradi(0);
        if (Time == CurTime)                    //    »ÙΩ·µ„∂‘”¶µƒ ±º‰µ»”⁄µ±«∞ ±º‰£¨ø…“‘÷±Ω”∑µªÿValue;
        {
            return Value;
        }
        
        Time = CurTime;
        Value = this->Solve(ErrorSignal,Order_of_Derive);//    ∑Ò‘Ú£¨÷ÿ–¬º∆À„
        if(Order_of_Derive)
        {
            Order_of_Derive->push_back(this);
        }
        return Value;
    }//	º∆À„ƒ≥“ªΩ·µ„µƒ÷µ
    void SetValue(const T& Input, const int& CurTime){
        Value = Input;
        Time = CurTime;
    }						//	Œ™Ω·µ„∏≥÷µ
    std::string GetName(){
        return Name;
    }														//	ªÒµ√Ω·µ„√˚
    T GetValue(){
        return Value;
    }																//	ªÒµ√Ω·µ„÷µ
    //
    T GetGradi (){
        return gradi;
    }
    void SetGradi (T G){
        gradi= G;
    }
    //
    
    int GetTime(){
        return Time;
    }																	//	ªÒµ√Ω·µ„µƒ ±º‰±Íº«
	virtual T Solve(std::string&ErrorSignal, std::vector<Node<T>*>*  Order_of_Derive = nullptr) = 0;									//	¥ø–È∫Ø ˝£¨±„”⁄≈……˙¿‡÷–÷ÿ–¥∏≤∏«: Ω¯––≤ªÕ¨÷÷¿‡‘ÀÀ„∑˚µƒº∆À„
    
    //add by Cai on 6.6
    virtual void Backward(T ,std::string&ErrorSignal){
	    std::cout << "BackWard Defined ERROR"<<std::endl ;
    }
    //
    virtual ~Node() {}															//	¥ø–ÈŒˆππ∫Ø ˝
};

#endif
