class Temperature
{
private:
  float B1 = (25.0F-0.76F/0.0025F); 
  float K1 = ((3.3F/4096.0F)/0.0025F); 
  float value = 0.0F ;
public:
  Temperature ()
  {
  };
  Temperature (float K, float B): K1(K), B1(B)
  {
  }
   ;
  void Calculation (std::uint32_t data1)
  {
    value = data1* K1 + B1;
  }
  
  float GetValue() 
  {
    return value ;
  }
};

