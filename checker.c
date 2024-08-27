#include <stdio.h>
#include <assert.h>

char parameter[3][25] = {"Temperature","State of Charge","Charge rate"};
float high[3] = {45,80,0.8};
float low[3] = {0,20,0};
int i;

void printResult(int index) {
  printf("%s is out of range!\n", parameter[index]);
}

int parameterIsOk(float temperature, float soc, float chargeRate) {
    float values[3] = {temperature,soc,chargeRate};
  int count = 4;
  for(i = 0; i < 3; ++i){
    if((values[i] < low[i]) || (values[i] > high[i])) {
        count = i;
        break;
    } else {
        continue;
    }
  }
  return count;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
  int count = parameterIsOk(temperature,soc,chargeRate);
  if(count == 4) {
    return 1;
  } else {
    printResult(count);
    return 0;
  }
}

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
