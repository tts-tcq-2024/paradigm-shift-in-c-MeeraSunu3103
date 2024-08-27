#include <stdio.h>
#include <assert.h>

int batteryIsOk(float temperature, float soc, float chargeRate) {
  if(temperature < 0) {
    printf("Temperature is too low!\n");
  } else if(temperature > 45) {
    printf("Temperature is too high!\n");
  } else if(soc < 20) {
    printf("State of Charge is too low!\n");
  } else if(soc > 80) {
    printf("State of Charge is too high!\n");
  } else if(chargeRate > 0.8) {
    printf("Charge Rate is too high!\n");
  } else {
    return 1;
  }
  return 0;
}

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
