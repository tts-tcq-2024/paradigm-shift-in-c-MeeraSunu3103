#include "BatteryConditionChecker.h"

int isTestValueOKAtIndex(int index) {
  return ((index == 1) || (index == 2) || (index == 3));
}

void checkBatteryConditionWithTestValues(int index1, int index2, float toleranceTemperature, float toleranceStateOfCharge, float toleranceChargeRate,
                          float *testvaluesTemperature, float *testvaluesStateOfCharge, float *testvaluesChargeRate) {
    int expectedTestResult = 0;
    for (int loopCounter = 0; loopCounter < 5; ++loopCounter) {
      expectedTestResult = (isTestValueOKAtIndex(index1) + isTestValueOKAtIndex(index2) + isTestValueOKAtIndex(loopCounter) == 3);
      assert(batteryIsOk(testvaluesTemperature[index1], toleranceTemperature,
                       testvaluesStateOfCharge[index2], toleranceStateOfCharge,
                       testvaluesChargeRate[loopCounter], toleranceChargeRate) == expectedTestResult);
    }
}

void runBatteryConditionTests(float toleranceTemperature, float toleranceStateOfCharge, float toleranceChargeRate,
                      float *testvaluesTemperature, float *testvaluesStateOfCharge, float *testvaluesChargeRate) {
    /* Testing the battery condition with OK, low and high values of battery parameters */
    for (int outerLoopCounter = 0; outerLoopCounter < 5; ++outerLoopCounter) {
        for (int innerLoopCounter = 0; innerLoopCounter < 5; ++innerLoopCounter) {
            checkBatteryConditionWithTestValues(outerLoopCounter, innerLoopCounter, toleranceTemperature, toleranceStateOfCharge, toleranceChargeRate,
                                             testvaluesTemperature, testvaluesStateOfCharge, testvaluesChargeRate);
        }
    }
}
