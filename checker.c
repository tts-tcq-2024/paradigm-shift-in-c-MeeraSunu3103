#include <stdio.h>
#include <assert.h>

char parameter[3][25] = {"Temperature","State of Charge","Charge rate"};
int high[3] = {45,80,0.8};
int low[3] = {0,20,0};

void printResult(int index) {
  printf("%s is out of range!\n", parameter[index]);
}

int parameterIsOk(float value, int index) {
  if(value < low[index] || value > high[index]) {
    printResult(index);
    return 0;
  } else {
    return 1;
  }
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
  if(((parameterIsOk(temperature, 0)) + (parameterIsOk(soc, 1)) + (parameterIsOk(chargeRate, 2))) == 3) {
    return 1;
  } else {
    return 0;
  }
}

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
