#include <stdio.h>
#include <assert.h>

/* structure type for battery parameters with all relevant properties */
typedef struct 
{
  char *parameterName; /* name of the battery parameter */
  float currentValue; /* current value of the battery parameter */
  float absoluteLowerLimit; /* recommended absolute lower limit of the battery parameeter */
  float absoluteUpperLimit; /* recommended absolute upper limit of the battery parameeter */
  float warningLowerLimit; /* warning lower limit of the battery parameeter */
  float warningUpperLimit; /* warning upper limit of the battery parameeter */
  char *currentStatus; /* current status of the battery parameeter */
}batteryConditionParameter;

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

/* Function Name: batteryIsOk 
   Function Description: checks if the battery condition is ok by checking the condition of all battery parameters passed as arguments ; returns 1 if battery condition is OK and returns 0 if battery condition is not OK */
int batteryIsOk(float temperature, float toleranceTemperature, 
                  float soc, float toleranceStateOfCharge, 
                  float chargeRate, float toleranceChargeRate) {
  batteryConditionParameter batteryParameterList[3];  /* list of structure objects to hold the details of the 3 battery parameters */
  char batteryParameterNames[3][25] = {"Temperature","State of Charge","Charge rate"};  /* List of battery parameter names ; the order of parameters given here is to be followed everywhere */
  float batteryParameterCurrentValues[3] = {temperature,soc,chargeRate}; /* List of current values of temperature, state of charge and charge rate respectively */
  float batteryParametersAbsoluteUpperLimits[3] = {45,80,0.8}; /* List of recommended absolute lower limits of temperature, state of charge and charge rate respectively */
  float batteryParametersAbsoluteLowerLimits[3] = {0,20,0.5}; /* List of recommended absolute upper limits of temperature, state of charge and charge rate respectively */
  float batteryParameterToleranceLevels[3] = {toleranceTemperature,toleranceStateOfCharge,toleranceChargeRate}; /* List of tolerance levels for temperature, state of charge and charge rate respectively */
  /* Note: If a tolerance level is not specified for a parameter, it must be set to 0 */
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
    
    // printf("\n Warning Limits of %s: %f to %f\n",batteryParameterList[loopCounter].parameterName,batteryParameterList[loopCounter].warningLowerLimit,batteryParameterList[loopCounter].warningUpperLimit);

    isbatteryParameterWithinWarningLimits(&batteryParameterList[loopCounter]);
    noOfOKParameters += isbatteryParameterWithinAbsoluteLimits(&batteryParameterList[loopCounter]);
  }
  
  printBatteryParameterCondition(batteryParameterList);
  
  /* If all 3 parameters are within recommended limits, battery condition is OK */
  return (noOfOKParameters == 3);
}

void assignArrayToMatrixRow(float *array, float *matrix, int row) {
  int loopCounter;
  for(loopCounter = 0; loopCounter < 5; ++loopCounter) {
    *((matrix + row * 5) + loopCounter) = array[loopCounter];
  }
}

void assignMatrixRowToArray(float *array, float *matrix, int row) {
  int loopCounter;
  for(loopCounter = 0; loopCounter < 5; ++loopCounter) {
    array[loopCounter] = *((matrix + row * 5) + loopCounter);
  }
}

void setTestValues(const float toleranceTemperature, const float toleranceStateOfCharge, const float toleranceChargeRate,
                      float *testvaluesTemperature, float *testvaluesStateOfCharge, float *testvaluesChargeRate) {
  int loopCounter;
  float batteryParameterToleranceLevels[3] = {toleranceTemperature,toleranceStateOfCharge,toleranceChargeRate};
  float batteryParametersAbsoluteUpperLimits[3] = {45,80,0.8}; /* List of recommended absolute lower limits of temperature, state of charge and charge rate respectively */
  float batteryParametersAbsoluteLowerLimits[3] = {0,20,0.5}; /* List of recommended absolute upper limits of temperature, state of charge and charge rate respectively */
  float batteryParameterToleranceValues[3];
  
  float testvalues[3][5];
  assignArrayToMatrixRow(testvaluesTemperature, testvalues, 0);
  assignArrayToMatrixRow(testvaluesStateOfCharge, testvalues, 1);
  assignArrayToMatrixRow(testvaluesChargeRate, testvalues, 2);
  
  for(loopCounter = 0; loopCounter < 3; ++loopCounter) {
    batteryParameterToleranceValues[loopCounter] = batteryParametersAbsoluteUpperLimits[loopCounter] * (batteryParameterToleranceLevels[loopCounter]/100.0)/2;
    
    testvalues[loopCounter][0] = batteryParametersAbsoluteLowerLimits[loopCounter] - batteryParameterToleranceValues[loopCounter]; 
    testvalues[loopCounter][1] = batteryParametersAbsoluteLowerLimits[loopCounter] + batteryParameterToleranceValues[loopCounter];
    testvalues[loopCounter][2] = (batteryParametersAbsoluteLowerLimits[loopCounter] + batteryParametersAbsoluteUpperLimits[loopCounter])/2;
    testvalues[loopCounter][3] = batteryParametersAbsoluteUpperLimits[loopCounter] - batteryParameterToleranceValues[loopCounter];
    testvalues[loopCounter][4] = batteryParametersAbsoluteUpperLimits[loopCounter] + batteryParameterToleranceValues[loopCounter];
  }
  
  assignMatrixRowToArray(testvaluesTemperature, testvalues, 0);
  assignMatrixRowToArray(testvaluesStateOfCharge, testvalues, 1);
  assignMatrixRowToArray(testvaluesChargeRate, testvalues, 2);
}

int okIndex(i) {
  return ((i == 1) || (i == 2) || (i == 3));
}

void checkBatteryConditionWithTestValues(int i, int j, int k, float toleranceTemperature, float toleranceStateOfCharge, float toleranceChargeRate,
                          float *testvaluesTemperature, float *testvaluesStateOfCharge, float *testvaluesChargeRate) {
    int okCount = okIndex(i) + okIndex(j) + okIndex(k);
    int expectedTestResult = (okCount == 3);
    
    assert(batteryIsOk(testvaluesTemperature[i], toleranceTemperature,
                       testvaluesStateOfCharge[j], toleranceStateOfCharge,
                       testvaluesChargeRate[k], toleranceChargeRate) == expectedTestResult);
}

void runBatteryConditionTests(const float toleranceTemperature, const float toleranceStateOfCharge, const float toleranceChargeRate,
                      float *testvaluesTemperature, float *testvaluesStateOfCharge, float *testvaluesChargeRate) {
    /* Testing the battery condition with OK, low and high values of battery parameters */
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                // Call a function to handle the battery condition check
                checkBatteryConditionWithTestValues(i, j, k, toleranceTemperature, toleranceStateOfCharge, toleranceChargeRate,
                                             testvaluesTemperature, testvaluesStateOfCharge, testvaluesChargeRate);
            }
        }
    }
}

int main() {
    const float toleranceTemperature = 5;
    const float toleranceStateOfCharge = 5;
    const float toleranceChargeRate = 5;

    float testvaluesTemperature[5];
    float testvaluesStateOfCharge[5];
    float testvaluesChargeRate[5];

    setTestValues(toleranceTemperature, toleranceStateOfCharge, toleranceChargeRate,
                  testvaluesTemperature, testvaluesStateOfCharge, testvaluesChargeRate);

    runBatteryConditionTests(toleranceTemperature, toleranceStateOfCharge, toleranceChargeRate,
                  testvaluesTemperature, testvaluesStateOfCharge, testvaluesChargeRate);

    return 0;
}
