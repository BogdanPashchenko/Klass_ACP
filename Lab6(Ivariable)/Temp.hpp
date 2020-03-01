#include "IVariable.hpp"

class Temperature : public IVariable
{
  public:
  Temperature(float B, float K): IVariable(B, K, "Temperature") {} ;

};