class Voltage
{
private:
  float B2 = 0.0F; 
  float K2 = (3.3F/4096.0F); 
  float value = 0.0F ;
public:
  Voltage ()
  {
  };
  Voltage (float K, float B): K2(K), B2(B)
  {
  }
   ;
  void CalculationV (std::uint32_t data2)
  {
    value = data2 * K2 + B2;
  }
  
  float GetValueV() 
  {
    return value ;
  }
};