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

void printBatteryParameterCondition(batteryConditionParameter batteryParameterList[]);
int isbatteryParameterWithinAbsoluteLimits(batteryConditionParameter *parameterToBeChecked);
void isbatteryParameterWithinWarningLimits(batteryConditionParameter *parameterToBeChecked);
int batteryIsOk(float temperature, float toleranceTemperature, float soc, float toleranceStateOfCharge, float chargeRate, float toleranceChargeRate);
void assignArrayToMatrixRow(float *array, float *matrix, int row);
void assignMatrixRowToArray(float *array, float *matrix, int row);
void setTestValues(const float toleranceTemperature, const float toleranceStateOfCharge, const float toleranceChargeRate,
                      float *testvaluesTemperature, float *testvaluesStateOfCharge, float *testvaluesChargeRate);
void checkBatteryConditionWithTestValues(int i, int j, float toleranceTemperature, float toleranceStateOfCharge, float toleranceChargeRate,
                          float *testvaluesTemperature, float *testvaluesStateOfCharge, float *testvaluesChargeRate);
void runBatteryConditionTests(const float toleranceTemperature, const float toleranceStateOfCharge, const float toleranceChargeRate,
                      float *testvaluesTemperature, float *testvaluesStateOfCharge, float *testvaluesChargeRate);
