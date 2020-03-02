#ifndef IVARIABLE_HPP
#define IVARIABLE_HPP

class IVariable
{
private:
  const float B1= 0.0F;
  const float K1 = 0.0F;
  float Value = 0.0F;  

  const char* Name = "Variable       " ; 
public:
  IVariable(float B, float K, const char* str): B1(B), K1(K), Name(str) 
  {
  };
   
  float GetValue()
  {
    return Value ;
  }
  
  virtual void Calculate(uint32_t code)
  {
     Value = code * B1 + K1 ;
  }
  
  const char* GetName()
  {
     return Name;
  }
  
};

#endif