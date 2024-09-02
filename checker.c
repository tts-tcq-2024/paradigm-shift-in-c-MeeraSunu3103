#include <stdio.h>
#include <assert.h>

/* structure type for battery parameters and all related values */
typedef struct 
{
  char *parameterName;
  float currentValue;
  float lowerLimit;
  float upperLimit;
  char *currentStatus;
}batteryConditionParameter;

void printBatteryCondition(batteryConditionParameter batteryParameterList[]) {
  int i;
  for(i = 0; i < 3; ++i) {
    printf(" %s value of %f is %s ;", batteryParameterList[i].parameterName, batteryParameterList[i].currentValue, batteryParameterList[i].currentStatus);
  }
  printf("\n\n");
}

int batteryParameterIsOk(batteryConditionParameter *parameterToBeChecked) {
  if(parameterToBeChecked->currentValue < parameterToBeChecked->lowerLimit) {
    parameterToBeChecked->currentStatus = "too low";
  } else if(parameterToBeChecked->currentValue > parameterToBeChecked->upperLimit) {
    parameterToBeChecked->currentStatus = "too high";
  } else {
    return 1;
  }
  return 0;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
  batteryConditionParameter batteryParameterList[3];
  char batteryParameterNames[3][25] = {"Temperature","State of Charge","Charge rate"};
  float batteryParameterCurrentValues[3] = {temperature,soc,chargeRate};
  float batteryParametersUpperLimits[3] = {45,80,0.8};
  float batteryParametersLowerLimits[3] = {0,20,0.5};
  int noOfOKParameters = 0;
  int i;
  
  for(i = 0; i < 3; ++i) {
    batteryParameterList[i].parameterName = batteryParameterNames[i];
    batteryParameterList[i].currentValue = batteryParameterCurrentValues[i];
    batteryParameterList[i].lowerLimit = batteryParametersLowerLimits[i];
    batteryParameterList[i].upperLimit = batteryParametersUpperLimits[i];
    batteryParameterList[i].currentStatus = "OK"; 
    
    if(batteryParameterIsOk(&batteryParameterList[i])) {
        ++noOfOKParameters;
    }
  }
  
  printBatteryCondition(batteryParameterList);
  return (noOfOKParameters == 3);
}

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));

  assert(batteryIsOk(25, 50, 0.5));
  assert(!batteryIsOk(25, 50, 0.1));
  assert(!batteryIsOk(25, 50, 1));
  assert(!batteryIsOk(25, 10, 0.5));
  assert(!batteryIsOk(25, 10, 0.1));
  assert(!batteryIsOk(25, 10, 1));
  assert(!batteryIsOk(25, 100, 0.5));
  assert(!batteryIsOk(25, 100, 0.1));
  assert(!batteryIsOk(25, 100, 1));
  assert(!batteryIsOk(-5, 50, 0.5));
  assert(!batteryIsOk(-5, 50, 0.1));
  assert(!batteryIsOk(-5, 50, 1));
  assert(!batteryIsOk(-5, 10, 0.5));
  assert(!batteryIsOk(-5, 10, 0.1));
  assert(!batteryIsOk(-5, 10, 1));
  assert(!batteryIsOk(-5, 100, 0.5));
  assert(!batteryIsOk(-5, 100, 0.1));
  assert(!batteryIsOk(-5, 100, 1));
  assert(!batteryIsOk(60, 50, 0.5));
  assert(!batteryIsOk(60, 50, 0.1));
  assert(!batteryIsOk(60, 50, 1));
  assert(!batteryIsOk(60, 10, 0.5));
  assert(!batteryIsOk(60, 10, 0.1));
  assert(!batteryIsOk(60, 10, 1));
  assert(!batteryIsOk(60, 100, 0.5));
  assert(!batteryIsOk(60, 100, 0.1));
  assert(!batteryIsOk(60, 100, 1));

}
