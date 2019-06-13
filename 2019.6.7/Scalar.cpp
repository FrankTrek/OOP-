#include "Scalar.h"


template <>
void Placeholder<float>::Backward(float gradient, std::string & ErrorSignal)
{
    //SetGradi(GetGradi()+gradient);
    
}
template <>
void Constant<float>::Backward(float gradient, std::string & ErrorSignal)
{
    //SetGradi(GetGradi()+gradient);
}
template <>
void Variable<float>::Backward(float gradient, std::string & ErrorSignal)
{
    //SetGradi(GetGradi()+gradient);
    
}
