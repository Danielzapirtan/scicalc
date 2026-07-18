#include <stdio.h>
#include <stdlib.h>

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
  if (x < sqrt(3.0))
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
  for (int i = 0; i < 100; i++) {
    i += 1.0;
    z *= (-dx);
    double eps = z / i;
    if (z * z < 1e-18)
      break;
    y += eps;
  }
  return y;
}

double log10(double x) {
  return log(x) / log(10);
}

double sumexp(double x) {
  double y = 0.0;
  double f = 1.0;
  double p = 1.0;
  double i = 0.0;
  while (1) {
    double eps = p / f;
    y += eps;
    if (y == y + eps)
      return y;
    i += 1.0;
    f *= i;
    p *= x;
  }
}

double exp(double x) {
  if (x < 0)
    return 1.0 / exp(-x);
  if (x == 0)
    return 1.0;
  if (x <= 2.0)
    return sumexp(x);
  double y = exp(x * 0.5);
  return y * y;
}

int main(int argc, char *argv[]) {
  printf("%.12lf\n", exp(5.4));
  printf("%.12lf\n", exp(5.4 * log(3.2)));
  return 0;
}

