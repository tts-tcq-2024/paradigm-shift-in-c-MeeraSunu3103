#include "BatteryConditionChecker.h"

/* prints out the status of battery parameters */
void printBatteryParameterCondition(batteryConditionParameter batteryParameterList[]) {
  for(int loopCounter = 0; loopCounter < 3; ++loopCounter) {
    printf(" %s value of %f is %s ;", batteryParameterList[loopCounter].parameterName, batteryParameterList[loopCounter].currentValue, batteryParameterList[loopCounter].currentStatus);
  }
  printf("\n\n");
}
