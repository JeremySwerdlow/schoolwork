/*
    funcs.h - header file for part2.c
      describes 5 functions which can be used for testing the
      trapezoidal rule in part2.c
    author - Jeremy Swerdlow
*/

/* linear function - y = x */
double func1(double x) {
  return x;
}

/* constant function - y = 2 */
double func2(double x) {
  return 2;
}

/* quadratic function - y = x^2 */
double func3(double x) {
  return x * x;
}

/* linear with constant - y = x + 2 */
double func4(double x) {
  return x + 2;
}

/* polynomial function - y = x^2 + x */
double func5(double x) {
  return x * x * x + x;
}
