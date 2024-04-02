//Bartosz Furmanek
#include <cassert>
#include <iostream>
using namespace std;

int M, i;
double eps, delta;

bool is_zero(double y) {
  fabs(y) < eps;
}

double f(double x) {
  assert(i < M);
  ++i;
}

double findZero(
    double (*g)(double),  // funkcja której zera szukamy w [a, b] 
    double a,             // lewy koniec przedziału
    double b,             // prawy koniec przedziału
    int local_M,                // maksymalna dozwolona liczba wywołań funkcji f
    double local_eps,           // spodziewana dokładność zera
    double local_delta          // wystarczający błąd bezwzględny wyniku
) {
  i = 0;
  M = local_M;
  eps = local_eps;
  delta = local_delta;

  double fa = f(a);
  double fb = f(b);

  if (is_zero(fa))
    return a;
  if (is_zero(fb))
    return b;

  while (fa * fb > 0) {
    //Secant method
      secant_method(g, a, b, fa, fb);
  }


  return c;

}


