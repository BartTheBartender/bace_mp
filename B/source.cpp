//Bartosz Furmanek
#include <cassert>
#include <iostream>
using namespace std;


double findZero (
    double (*f)(double),  // funkcja której zera szukamy w [a, b] 
    double a,             // lewy koniec przedziału
    double b,             // prawy koniec przedziału
    int M,                // maksymalna dozwolona liczba wywołań funkcji f
    double eps,           // spodziewana dokładność zera
    double delta          // wystarczający błąd bezwzględny wyniku
) {
  int i = 0;
  double fa = f(a);
  double fb = f(b);

  if (fabs(fa) < eps)
    return a;
  if (fabs(fb) < eps)
    return b;

  double c = 0, fc = 0;

  while (i < M && fa * fb > 0) {
    //Secant method
    c = a - fa * (a-b)/(fa - fb);
    fc = f(c);
    ++i;

    /* cout << "a: " << a << " b: " << b << " c: " << c << endl; */

    if (fabs(fc) < eps) {
      return c;
    } else if (fa * fc < 0) {
      b = c;
      fb = fc;
    } else if (fb * fc < 0) {
      a = c;
      fa = fc;
    } else if (fabs(a-c) < fabs(b-c)) {
      b = c;
      fb = fc;
    } else {
      a = c;
      fa = fc;
    }
  }
  /* cout << i << "/" << M << endl; */
  assert(fa * fb < 0);

  double delta1 = 10e12*delta;
  /* cout << delta1 << endl; */

  while (i < M && fabs(a-b) >= delta1) {
    //Bisection method
    /* cout << "a: " << a << " b: " << b << endl; */
    c = (a+b)/2;
    fc = f(c);
    ++i;

    if (fabs(fc) < eps) {
      return c;
    } else if (fc * fa < 0) {
      b = c;
      fb = fc;
    } else if (fc * fb < 0) {
      a = c;
      fa = fc;
    } else {
      assert(!"Not possible in bisection method");
    }
  }
  cout << i << "/" << M << endl;

  while(i < M && fabs(a-b) >= delta) {
    //Secant method
    c = a - fa * (a-b)/(fa - fb);
    fc = f(c);
    ++i;

    cout << "a: " << a << " b: " << b << " c: " << c << endl;

    if (fabs(fc) < eps) {
      return c;
    } else if (fa * fc < 0) {
      b = c;
      fb = fc;
    } else if (fb * fc < 0) {
      a = c;
      fa = fc;
    } else {
      assert(!"Not possible in secant method");
    }
  }
  cout << i << "/" << M << endl;

  return NAN;
}


