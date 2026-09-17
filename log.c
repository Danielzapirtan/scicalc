#include <stdio.h>
#include <stdlib.h>

#define zeps 1.0e-14

extern double zsqrt(double x);
extern double sumzlog(double x);
extern double zlog10(double x);
extern double zlog(double x);

double zabs(double x) {
  if (x >= 0)
    return x;
  return -x;
}

double zlog(double x) {
  if (x <= 0.0)
    exit(1);
  if (x < 1.0)
    return -zlog(1.0 / x);
  if (x < 1.1)
    return sumzlog(x);
  return 2.0 * zlog(zsqrt(x));
}

double zsqrt(double x) {
  if (x < 0.0)
    exit(1);
  if (x == 0.0)
    return 0.0;
  if (x < 1.0)
    return 1.0 / zsqrt(1.0 / x);
  double y = 2.0;
  while (zabs(y - x / y) >= zeps) {
    y -= (y * y - x) / (2.0 * y);
  }
  return y;
}

double sumzlog(double x) {
  double y = 0.0;
  double i = 0.0;
  double dx = x - 1.0;
  double z = -1.0;
  while (1) {
    i += 1.0;
    z *= (-dx);
    double eps = z / i;
    if (zabs(eps) < zeps)
      break;
    y += eps;
  }
  return y;
}

double zlog10(double x) {
  return zlog(x) / zlog(10.0);
}

double sumzexp(double x) {
  double y = 0.0;
  double f = 1.0;
  double p = 1.0;
  double i = 0.0;
  while (1) {
    double eps = p / f;
    y += eps;
    if (eps < zeps)
      return y;
    i += 1.0;
    f *= i;
    p *= x;
  }
}

double zexp(double x) {
  if (x < 0)
    return 1.0 / zexp(-x);
  if (x == 0)
    return 1.0;
  if (x <= 2.0)
    return sumzexp(x);
  double y = zexp(x * 0.5);
  return y * y;
}

double zpow(double x, double y) {
  return zexp(y * zlog(x));
}

int main(int argc, char *argv[]) {
  printf("%.7le\n", zsqrt(2.0));
  printf("%.7le\n", zpow(3.2, 5.4));
  for (double i = 1.0; i < 10.0; i += 0.1) {
     printf("%.1lf %.7le\n", i, zlog10(i));
     fflush(stdout);
  }
  return 0;
}

