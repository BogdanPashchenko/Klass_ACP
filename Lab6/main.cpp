#include "adc1registers.hpp" //for ADC1
#include "adccommonregisters.hpp" //for ADCCommon
#include "gpioaregisters.hpp"  //for Gpioa
#include "gpiocregisters.hpp"  //for Gpioc
#include "rccregisters.hpp"    //for RCC
#include "tim2registers.hpp"   //for TIM2
#include <iostream>

using namespace std;

class ACP
{
  private:
    {
    void VoltageSet ()
   {
   RCC::AHB1ENR::GPIOAEN::Enable::Set();
   RCC::AHB1ENR::GPIOAEN::Enable::Set() ; //vkl port A
   GPIOA::MODER::MODER0::Analog::Set();
   ADC1::CR2::CONT::SingleConversion::Set(); // cont porkl
   ADC1::CR2::EOCS::SingleConversion::Set(); //eosk vklichen
   ADC1::CR1::RES::Bits12::Set(); //ystanovka 12bitov
   }
   void TemperatureSet()
   {
   ADC_Common::CCR::TSVREFE::Enable::Set(); //temperat. senser  
   ADC1::CR2::CONT::SingleConversion::Set(); // cont porkl
   ADC1::CR2::EOCS::SingleConversion::Set(); //eosk vklichen
   ADC1::CR1::RES::Bits12::Set(); //ystanovka 12bitov
   }
    };
  public:
   void SettingACP ()
   {
  RCC::CR::HSEON::On::Set(); //podkluchili vneshnii istrochnik
  while (!RCC::CR::HSERDY::Ready::IsSet() )
  {
  };
  RCC::CFGR::SW::Hse::Set();
  while ( !RCC::CFGR::SWS::Hse::IsSet( ))
  { 
  };
  RCC::APB2ENR::ADC1EN::Enable::Set(); //acp k istochiky tactirovaniya
  ADC1::CR2::ADON::Enable::Set();
   }
  void Voltage ()
  {
   ADC1::SQR1::L::Conversions2::Set(); // kolvo izmerenii 
   ADC1::SQR3::SQ1::Channel0::Set(); //podkluchili datchik na kanal 18
   ADC1::SMPR2::SMP0::Cycles480::Set(); //speed diskretizacii
   constexpr float B1 = 0; // see datacheet (page 226) and calculate B coeficient here ; - napryagenie
   constexpr float K1 = 3.3F/4096.0F; // see datcheet ((page 226)) and calculate K coeficient here ;  - napryagenie
   std::uint32_t data2 = 0U ;
   float voltage = 0.0F ;
   ADC1::CR2::SWSTART::On::Set();
   while (ADC1::SR::EOC::ConversionNotComplete::IsSet( )) 
   { 
   };
   data2 = ADC1::DR::Get();//Get data from ADC; 
   voltage = data2 * K1 + B1 ; //Convert ADC counts to temperature
   std::cout << "Count: " << data2 << " voltage: " << voltage << std::endl ;
  }
  
  void Temperature ()
  {
   ADC1::SQR1::L::Conversions2::Set(); // kolvo izmerenii
   ADC1::SQR3::SQ1::Channel18::Set(); //podkluchili datchik na kanal 18
   ADC1::SMPR1::SMP18::Cycles480::Set(); //speed diskretizacii
   constexpr float B2 = (25.0F-0.76F/0.0025F); // see datacheet (page 226) and calculate B coeficient here ; -tempa
   constexpr float K2 = ((3.3F/4096.0F)/0.0025F); // see datcheet ((page 226)) and calculate K coeficient here ; -tempa
   std::uint32_t data1 = 0U ;
   float temperature = 0.0F ;
   ADC1::CR2::SWSTART::On::Set();
   while (ADC1::SR::EOC::ConversionNotComplete::IsSet( )) 
     { 
     };
   data1 = ADC1::DR::Get();//Get data from ADC;
   temperature = data1* K2+B2; // tempa
   std::cout << "Count: " << data1 << " Temperature: " << temperature << std::endl ;
  }
};
int main()
{
  ACP ADC1;
  ADC1. SettingACP();
  ADC1. Voltage();
  ADC1. Temperature();
  return 0;
}  
