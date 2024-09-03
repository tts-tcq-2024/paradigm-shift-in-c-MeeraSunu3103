#include <stdio.h>
#include <assert.h>

/* structure type for battery parameters with all relevant properties */
typedef struct 
{
  char *parameterName; /* name of the battery parameter */
  float currentValue; /* current value of the battery parameter */
  float lowerLimit; /* recommended lower limit of the pattery parameeter */
  float upperLimit; /* recommended lower limit of the pattery parameeter */
  char *currentStatus; /* current status of the pattery parameeter */
}batteryConditionParameter;

/* Function Name: printBatteryCondition 
   Function Description: prints out the status of battery parameters */
void printBatteryParameterCondition(batteryConditionParameter batteryParameterList[]) {
  int i;
  for(i = 0; i < 3; ++i) {
    printf(" %s value of %f is %s ;", batteryParameterList[i].parameterName, batteryParameterList[i].currentValue, batteryParameterList[i].currentStatus);
  }
  printf("\n\n");
}

/* Function Name: batteryParameterIsOk 
   Function Description: checks if the battery parameter passed as the argument is within its recommended limits and specifies the breach type, if any; returns 1 if it is within limits and returns 0 if it is out of limits */
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

/* Function Name: batteryIsOk 
   Function Description: checks if the battery condition is ok by checking the condition of all battery parameters passed as arguments ; returns 1 if battery condition is OK and returns 0 if battery condition is not OK */
int batteryIsOk(float temperature, float soc, float chargeRate) {
  batteryConditionParameter batteryParameterList[3];  /* list of structure objects to hold the details of the 3 battery parameters */
  char batteryParameterNames[3][25] = {"Temperature","State of Charge","Charge rate"};  /* List of battery parameter names ; the order of parameters given here is to be followed everywhere */
  float batteryParameterCurrentValues[3] = {temperature,soc,chargeRate}; /* List of current values of temperature, state of charge and charge rate respectively */
  float batteryParametersUpperLimits[3] = {45,80,0.8}; /* List of recommended lower limits of temperature, state of charge and charge rate respectively */
  float batteryParametersLowerLimits[3] = {0,20,0.5}; /* List of recommended upper limits of temperature, state of charge and charge rate respectively */
  int noOfOKParameters = 0;  /* counter to count the no. of battery parameters that are within recommended limits */
  int i; /* simple loop counter */
  
  for(i = 0; i < 3; ++i) {
    /* initializing the structure object list with values corresponding to each battery parameter */
    /* index 0: temperature */
    /* index 1: state of charge */
    /* index 2: charge rate */
    batteryParameterList[i].parameterName = batteryParameterNames[i];
    batteryParameterList[i].currentValue = batteryParameterCurrentValues[i];
    batteryParameterList[i].lowerLimit = batteryParametersLowerLimits[i];
    batteryParameterList[i].upperLimit = batteryParametersUpperLimits[i];
    batteryParameterList[i].currentStatus = "OK"; 
    
    /* If the battery parameter that is currently being checked is within the recommended limits, increment the counter of no. of parameter that are OK */
    if(batteryParameterIsOk(&batteryParameterList[i])) {
        ++noOfOKParameters;
    }
  }
  
  printBatteryParameterCondition(batteryParameterList);
  
  /* If all 3 parameters are within recommended limits, battery condition is OK */
  return (noOfOKParameters == 3);
}

/* Function Name:  
   Function Description:  
   Return Value: */
void testBatteryCondition(float *parameter1ValuesList, float *parameter2ValuesList, float *parameter3ValuesList) {
  int i,j,k; /* simple loop counters */
  
  /* Testing the battery condition with OK, low and high values of battery parameters by looping through them */
  for(i = 0; i < 3; ++i) {
    for(j = 0; j < 3; ++j) {
      for(k = 0; k < 3; ++k) {
        if((i+j+k) == 0) {
          assert(batteryIsOk(parameter1ValuesList[i], parameter2ValuesList[j], parameter3ValuesList[k]));      
        } else {
          assert(!batteryIsOk(parameter1ValuesList[i], parameter2ValuesList[j], parameter3ValuesList[k]));      
        }  
      }    
    }  
  }
}

int main() {
  /* list of OK, low and high values of battery parameters */
  float valuesTemperature[3] = {25,-5,60};
  float valuesStateOfCharge[3] = {50,10,100};
  float valuesChargeRate[3] = {0.6,0.1,1};
  
  testBatteryCondition(valuesTemperature, valuesStateOfCharge, valuesChargeRate);
}
