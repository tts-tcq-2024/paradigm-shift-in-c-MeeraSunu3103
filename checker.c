#include <stdio.h>
#include <assert.h>

char parameter[3][25] = {"Temperature","State of Charge","Charge rate"};
float high[3] = {45,80,0.8};
float low[3] = {0,20,0};
int first[3] = {0,0,0};
char breach[3][4] = {".","low","high"};
int i;

void printResult() {
  int ix;
  for(i = 0; i < 3; ++i)
  {
      if(first[i] > 0) {
          ix = i;
          break;
      } else {
          continue;
      }
  }
  printf("%s is too %s!\n", parameter[ix], breach[first[ix]]);
}

int parameterIsOk(float value, int index) {
  if(value < low[index]) {
    first[index] = 1;
  } else if(value > high[index]) {
    first[index] = 2;
  } else {
    return 1;
  }
  return 0;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
  if(((parameterIsOk(temperature, 0)) + (parameterIsOk(soc, 1)) + (parameterIsOk(chargeRate, 2))) == 3) {
    return 1;
  } else {
    printResult();
    for(i = 0; i < 3; ++i)
    {
      first[i] = 0;
    }
    return 0;
  }
}

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
