#include "BatteryConditionChecker.h"

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
  float batteryParameterToleranceLevels[3] = {toleranceTemperature,toleranceStateOfCharge,toleranceChargeRate}; /* List of given tolerances for temperature, state of charge and charge rate respectively */
  float batteryParametersAbsoluteUpperLimits[3] = {45,80,0.8}; /* List of recommended absolute lower limits of temperature, state of charge and charge rate respectively */
  float batteryParametersAbsoluteLowerLimits[3] = {0,20,0.5}; /* List of recommended absolute upper limits of temperature, state of charge and charge rate respectively */
  float batteryParameterToleranceValues[3];
  
  float testvalues[3][5];
  assignArrayToMatrixRow(testvaluesTemperature, testvalues, 0);
  assignArrayToMatrixRow(testvaluesStateOfCharge, testvalues, 1);
  assignArrayToMatrixRow(testvaluesChargeRate, testvalues, 2);
  
  for(loopCounter = 0; loopCounter < 3; ++loopCounter) {
    /* calculating half of the tolerance value */
    batteryParameterToleranceValues[loopCounter] = batteryParametersAbsoluteUpperLimits[loopCounter] * (batteryParameterToleranceLevels[loopCounter]/100.0)/2;
    
    testvalues[loopCounter][0] = batteryParametersAbsoluteLowerLimits[loopCounter] - batteryParameterToleranceValues[loopCounter];            /* value less than absolute lower limit */ 
    testvalues[loopCounter][1] = batteryParametersAbsoluteLowerLimits[loopCounter] + batteryParameterToleranceValues[loopCounter];            /* value more than absolute lower limit but less than lower warning limit */
    testvalues[loopCounter][2] = (batteryParametersAbsoluteLowerLimits[loopCounter] + batteryParametersAbsoluteUpperLimits[loopCounter])/2;   /* value within both upper and lower warning limits i.e., OK value */
    testvalues[loopCounter][3] = batteryParametersAbsoluteUpperLimits[loopCounter] - batteryParameterToleranceValues[loopCounter];            /* value less than absolute upper limit but more than upper warning limit */
    testvalues[loopCounter][4] = batteryParametersAbsoluteUpperLimits[loopCounter] + batteryParameterToleranceValues[loopCounter];            /* value more than absolute upper limit */
  }
  
  assignMatrixRowToArray(testvaluesTemperature, testvalues, 0);
  assignMatrixRowToArray(testvaluesStateOfCharge, testvalues, 1);
  assignMatrixRowToArray(testvaluesChargeRate, testvalues, 2);
}
