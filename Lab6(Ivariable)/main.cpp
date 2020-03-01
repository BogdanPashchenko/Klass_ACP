#include "adc1registers.hpp" //for ADC1
#include "adccommonregisters.hpp" //for ADCCommon
#include "gpioaregisters.hpp"  //for Gpioa
#include "gpiocregisters.hpp"  //for Gpioc
#include "rccregisters.hpp"    //for RCC
#include "tim2registers.hpp"   //for TIM2
#include <iostream>
#include "ADC.hpp"
#include "Temp.hpp"
#include "Voltage.hpp"
#include "IVariable.hpp"

extern "C"
{
int __low_level_init(void)
{
  RCC::APB2ENR::ADC1EN::Enable::Set(); //acp k istochiky tactirovaniya
  ADC_Common::CCR::TSVREFE::Enable::Set(); //temperat. senser
  ADC1::CR2::CONT::SingleConversion::Set(); // cont porkl
  ADC1::CR2::EOCS::SingleConversion::Set(); //eosk vklichen
  
  ADC1::SQR1::L::Conversions2::Set(); // kolvo izmerenii
  
  ADC1::SMPR2::SMP0::Cycles480::Set(); //speed diskretizacii
  RCC::AHB1ENR::GPIOAEN::Enable::Set() ;
  GPIOA::MODER::MODER0::Analog::Set();
  
  return 1;
}
}  

//constexpr float B2 = (25.0F-0.76F/0.0025F); // see datacheet (page 226) and calculate B coeficient here ; -tempa
//constexpr float K2 = ((3.3F/4096.0F)/0.0025F); // see datcheet ((page 226)) and calculate K coeficient here ; -tempa
//constexpr float B1 = 0; // see datacheet (page 226) and calculate B coeficient here ; - napryagenie
//constexpr float K1 = 3.3F/4096.0F; // see datcheet ((page 226)) and calculate K coeficient here ;  - napryagenie

using MyADC = ADC<ADC1>;


int main ()
{
  MyADC::On ();
  MyADC::Config(Resolution::Bits12);
  MyADC::ConfigChannel(18, 0);
  Temperature Temp(((3.3F/4096.0F)/0.0025F),(25.0F-0.76F/0.0025F));         
  Voltage Voltag((3.3F/4096.0F) , 0);
  
  for (;;)
  {
  MyADC::Start ();
  IVariable* Variables[2] = {&Temp, &Voltag} ;
  for (auto it: Variables)
    {
    while (!MyADC::IsReady())
      {
      }
  std::uint32_t data = MyADC::Get();
  it->Calculate(data);
  std::cout << it->GetName() << ": " << it->GetValue() <<  std::endl ;
    }
  }
}
;
