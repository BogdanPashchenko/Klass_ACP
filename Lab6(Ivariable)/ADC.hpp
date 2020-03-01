enum class Resolution 
{
  Bits12,
  Bits10,
  Bits8,
  Bits6,
};
template <class Adc>
class ADC
{
public: 
  static void On()
  { 
    Adc::CR2::ADON::Enable::Set(); 
  }
 static void Off()
 {
    Adc::CR2::ADON::Disable::Set();
 }
 static void Start()
{
   Adc::CR2::SWSTART::On::Set(); 
 }
 static bool IsReady()
 {
   return  Adc::SR::EOC::ConversionComplete::IsSet(); //preobr zakoncheno
 }
 static uint32_t Get()
 {
   return Adc::DR::Get() ;
 }
 static void Config(Resolution resolution)
 {
   switch (resolution)
   {
     case Resolution::Bits12:
       Adc::CR1::RES::Bits12::Set();
       break;
     case Resolution::Bits10:
       Adc::CR1::RES::Bits10::Set();
       break;
     case Resolution::Bits8:
       Adc::CR1::RES::Bits8::Set();
       break;
     case Resolution::Bits6:
       Adc::CR1::RES::Bits6::Set();
       break;
       default:
       Adc::CR1::RES::Bits12::Set();
       break;
   }
 }
 static void ConfigChannel (std::uint32_t NumChannel,std::uint32_t NumChannel1) //izmerenia
   {
     ScanConfig() ;
     Adc::SQR1::L::Conversions2::Set();
     assert(NumChannel < 19);
     Adc::SQR3::SQ1::Set(NumChannel); // kanal 
     assert(NumChannel1 < 19);
     Adc::SQR3::SQ2::Set(NumChannel1); // kanal 
   }
  
  static void ScanConfig()
  {
    Adc::CR1::SCAN::Enable::Set();
    Adc::CR2::CONT::SingleConversion::Set(); 
    Adc::CR2::EOCS::SingleConversion::Set(); 
  }
} ;