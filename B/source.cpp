//Bartosz Furmanek
#include <cassert>
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

void d(){cout << "here" << endl;}
void d(const string& s){cout << s << endl;}
double findZero (
    double (*f)(double),  // funkcja której zera szukamy w [a, b] 
    double a,             // lewy koniec przedziału
    double b,             // prawy koniec przedziału
    int M,                // maksymalna dozwolona liczba wywołań funkcji f
    double eps,           // spodziewana dokładność zera
    double delta          // wystarczający błąd bezwzględny wyniku
) {
  int i = 2;
  double fa = f(a);
  double fb = f(b);

  if (fabs(fa) < eps)
    return a;
  if (fabs(fb) < eps)
    return b;

  double c = 0, fc = 0;

  while (i < M && fa * fb > 0) {
    //Secant method
    c = a - fa * ((a-b)/(fa - fb));
    fc = f(c);
    ++i;

    if (fabs(fc) < eps) {
      return c;
    } 

    a = b;
    fa = fb;
    b = c;
    fb = fc;

  }

  assert(fa * fb < 0);
  if(a >= b) {
    c = a;
    a = b;
    b = c;

    fc = fa;
    fa = fb;
    fb = fc;
  }
  assert(a < b);
  double delta1 = 0.01;
  while(i < M && fabs(a-b) >= delta && fabs(fa) >= eps && fabs(fb) >= eps) {
    
    if(fabs(a-b) >= delta1) {
      //Bisection method
      /* d("bisection"); */
      c = (a+b)/2;
      fc = f(c);
      ++i;
  
      if(fabs(fc) < eps)
        return c;
      
      if(fa * fc < 0){
        b = c;
        fb = fc;
      } else {
        a = c;
        fa = fc;
      }
      assert(fa * fb < 0);
    } else {
      /* d("secant"); */
      //Secant method again
      c = a - fa * ((a-b)/(fa - fb));
      fc = f(c);
      ++i;

      if (fabs(fc) < eps) {
        return c;
      } 

      a = b;
      fa = fb;
      b = c;
      fb = fc;
    }
  }

  /* assert(i < M); */
  
  if(fabs(fa) < eps)
    a = b;
  return b;
  
}


