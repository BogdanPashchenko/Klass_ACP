#include "IVariable.hpp"

class Voltage : public IVariable
{
public:
  Voltage(float B, float K): IVariable(B, K, "Voltage") {} ;
};