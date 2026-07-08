#include <stdio.h>

extern double sqrt(double x);
extern double sumlog(double x);
extern double log10(double x);
extern double log(double x);
double log(double x) {
  if (x < 0.0)
    return log(-x);
  if (x == 0.0)
    return 0.0;
  if (x < 1.0)
    return -log(1.0 / x);
  if (x < sqrt(2.0))
    return sumlog(x);
  return 2.0 * log(sqrt(x));
}

double sqrt(double x) {
  if (x < 0.0)
    return sqrt(-x);
  if (x == 0.0)
    return 0.0;
  if (x < 1.0)
    return 1.0 / sqrt(1.0 / x);
  double y = 2.0;
  while (y != x / y) {
    y = (y * y - x) / (2 * y);
  }
  return y;
}

double sumlog(double x) {
  double y = 0.0;
  double i = 0.0;
  double dx = x - 1.0;
  double z = -1.0;
  while (1) {
    i += 1.0;
    z *= (-dx);
    double eps = z / i;
    if (z == 0)
      break;
    y += eps;
  }
  return y;
}

double log10(double x) {
  return log(x) / log(10);
}

int main(void) {
  printf("%lf\n", sqrt(2.0));
  printf("%lf\n", log10(2.0));
  return 0;
}

