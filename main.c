int main() {
    /* Change tolerance values as required for tuning */
    const float toleranceTemperature = 5;
    const float toleranceStateOfCharge = 5;
    const float toleranceChargeRate = 5;

    float testvaluesTemperature[5];
    float testvaluesStateOfCharge[5];
    float testvaluesChargeRate[5];

    /* creates test input values based on lower limit, upper limit and given tolerance */
    setTestValues(toleranceTemperature, toleranceStateOfCharge, toleranceChargeRate,
                  testvaluesTemperature, testvaluesStateOfCharge, testvaluesChargeRate);

    runBatteryConditionTests(toleranceTemperature, toleranceStateOfCharge, toleranceChargeRate,
                  testvaluesTemperature, testvaluesStateOfCharge, testvaluesChargeRate);

    return 0;
}
