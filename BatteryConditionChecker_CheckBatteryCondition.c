#include "BatteryConditionChecker.h"

/* Function Name: printBatteryCondition 
   Function Description: prints out the status of battery parameters */
void printBatteryParameterCondition(batteryConditionParameter batteryParameterList[]) {
  int loopCounter;
  for(loopCounter = 0; loopCounter < 3; ++loopCounter) {
    printf(" %s value of %f is %s ;", batteryParameterList[loopCounter].parameterName, batteryParameterList[loopCounter].currentValue, batteryParameterList[loopCounter].currentStatus);
  }
  printf("\n\n");
}

/* Function Name: isbatteryParameterWithinAbsoluteLimits 
   Function Description: checks if the battery parameter passed as the argument is within its recommended limits and specifies the breach type, if any; returns 1 if it is within limits and returns 0 if it is out of limits */
int isbatteryParameterWithinAbsoluteLimits(batteryConditionParameter *parameterToBeChecked) {
  if(parameterToBeChecked->currentValue < parameterToBeChecked->absoluteLowerLimit) {
    parameterToBeChecked->currentStatus = "too low";
  } else if(parameterToBeChecked->currentValue > parameterToBeChecked->absoluteUpperLimit) {
    parameterToBeChecked->currentStatus = "too high";
  } else {
    return 1;
  }
  return 0;
}

/* Function Name: isbatteryParameterWithinWarningLimits 
   Function Description: checks if the battery parameter passed as the argument is within its recommended limits and specifies the breach type, if any; returns 1 if it is within limits and returns 0 if it is out of limits */
void isbatteryParameterWithinWarningLimits(batteryConditionParameter *parameterToBeChecked) {
  if(parameterToBeChecked->currentValue < parameterToBeChecked->warningLowerLimit) {
    parameterToBeChecked->currentStatus = "OK but approaching lower limit";
  } else if(parameterToBeChecked->currentValue > parameterToBeChecked->warningUpperLimit) {
    parameterToBeChecked->currentStatus = "OK but approaching upper limit";
  } else {
    /* do nothing */;
  }
}

/* checks if the battery condition is ok by checking the condition of all battery parameters passed as arguments ; returns 1 if battery condition is OK and returns 0 if battery condition is not OK */
int batteryIsOk(float temperature, float toleranceTemperature, 
                  float soc, float toleranceStateOfCharge, 
                  float chargeRate, float toleranceChargeRate) {
  batteryConditionParameter batteryParameterList[3];  /* list of structure objects to hold the details of the 3 battery parameters */
  char batteryParameterNames[3][25] = {"Temperature","State of Charge","Charge rate"};  /* List of battery parameter names ; the order of parameters given here is to be followed everywhere */
  float batteryParameterCurrentValues[3] = {temperature,soc,chargeRate}; /* List of current values of temperature, state of charge and charge rate respectively */
  float batteryParametersAbsoluteUpperLimits[3] = {45,80,0.8}; /* List of recommended absolute lower limits of temperature, state of charge and charge rate respectively */
  float batteryParametersAbsoluteLowerLimits[3] = {0,20,0.5}; /* List of recommended absolute upper limits of temperature, state of charge and charge rate respectively */
  float batteryParameterToleranceLevels[3] = {toleranceTemperature,toleranceStateOfCharge,toleranceChargeRate}; /* List of tolerance levels for temperature, state of charge and charge rate respectively */
  int noOfOKParameters = 0;  /* counter to count the no. of battery parameters that are within recommended limits */
  int loopCounter; /* simple loop counter */
  
  for(loopCounter = 0; loopCounter < 3; ++loopCounter) {
    /* initializing the structure object list with values corresponding to each battery parameter */
    /* index 0: temperature */
    /* index 1: state of charge */
    /* index 2: charge rate */
    batteryParameterList[loopCounter].parameterName = batteryParameterNames[loopCounter];
    batteryParameterList[loopCounter].currentValue = batteryParameterCurrentValues[loopCounter];
    batteryParameterList[loopCounter].absoluteLowerLimit = batteryParametersAbsoluteLowerLimits[loopCounter];
    batteryParameterList[loopCounter].absoluteUpperLimit = batteryParametersAbsoluteUpperLimits[loopCounter];
    batteryParameterList[loopCounter].warningLowerLimit = batteryParametersAbsoluteLowerLimits[loopCounter] + (batteryParametersAbsoluteUpperLimits[loopCounter] * (batteryParameterToleranceLevels[loopCounter]/100.0));
    batteryParameterList[loopCounter].warningUpperLimit = batteryParametersAbsoluteUpperLimits[loopCounter] - (batteryParametersAbsoluteUpperLimits[loopCounter] * (batteryParameterToleranceLevels[loopCounter]/100.0));
    batteryParameterList[loopCounter].currentStatus = "OK"; 
    
    isbatteryParameterWithinWarningLimits(&batteryParameterList[loopCounter]);
    noOfOKParameters += isbatteryParameterWithinAbsoluteLimits(&batteryParameterList[loopCounter]);
  }
  
  printBatteryParameterCondition(batteryParameterList);
  
  /* If all 3 parameters are within recommended limits, battery condition is OK */
  return (noOfOKParameters == 3);
}
