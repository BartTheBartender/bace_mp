//Bartosz Furmanek
#include "source.h"
#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;
//////////////////
spline::spline(integer size):
  n(size - 1)
  /* t(new num[n + 1]), */
  /* h(new num[n]), */
  /* y(new num[n + 1]), */
  /* z(new num[n + 1]) */
  {}
spline::~spline() {
  /* delete[] t; */
  delete[] h;
  /* delete[] y; */
  delete[] z;
}

void spline::set_points(double x[], double y[]) {
  integer n = this-> n;

  num* h = new num[n];
  for(integer i = 0; i <= n - 1; ++i)
    h[i] = x[i + 1] - x[i];
  /* for(integer i = 0; i <= n - 1; ++i) */
  /*   cout << h[i] << " "; */
  /* cout << endl; */

  num* b = new num[n];
  for(integer i = 0; i <= n - 1; ++i)
    b[i] = (y[i + 1] - y[i]) / h[i];
  /* for(integer i = 0; i <= n - 1; ++i) */
  /*   cout << b[i] << " "; */
  /* cout << endl; */

  num* v = new num[n];
  /* v[0] = nan("uninitialized on purpouse"); */
  for(integer i = 1; i <= n - 1; ++i)
    v[i] = 2 * (h[i - 1] + h[i]);
  /* for(integer i = 0; i <= n - 1; ++i) */
  /*   cout << v[i] << " "; */
  /* cout << endl; */

  num* u = new num[n];
  /* u[0] = nan("uninitialized on purpouse"); */
  for(integer i = 1; i <= n - 1; ++i)
    u[i] = 6 * (b[i] - b[i - 1]);
  /* for(integer i = 0; i <= n - 1; ++i) */
  /*   cout << u[i] << " "; */
  /* cout << endl; */

  //Begin

  for(integer i = 1; i <= n - 2; ++i) {
    v[i + 1] -= h[i] * h[i] / v[i];
    u[i + 1] -= u[i] * h[i] / v[i];
  }

  for(integer i = n - 1; i >= 2; --i)
    u[i - 1] -= u[i] * h[i - 1] / v[i];

  num* z = new num[n+1];
  for(integer i = 1; i <= n - 1; ++i)
    z[i] = u[i] / v[i];
  
  z[0] = z[n] = 0;

  ///END

  this->t=x;
  this->y=y;
  this->h=h;
  this->z=z;

}

void spline::debug_print() const {
  for(integer i = 0; i <= this-> n; ++i)
    cout << this->t[i] << " ";
  cout << endl;

  for(integer i = 0; i <= this-> n - 1; ++i)
    cout << this->h[i] << " ";
  cout << endl;

  for(integer i = 0; i <= this-> n; ++i)
    cout << this->y[i] << " ";
  cout << endl;

  for(integer i = 0; i <= this-> n; ++i)
    cout << this->z[i] << " ";
  cout << endl;
}

num exp3(const num y) {
  return y * y * y;
}

double spline::operator() (double x) const {
  auto t = this->t;
  auto h = this->h;
  auto y = this->y;
  auto z = this->z;
  integer i = 0;
  for(i = 0; i < n; ++i){
    if(x >= t[i] && x < t[i + 1])
      break;
  }
  assert(x >= t[i]);
  assert(x < t[i + 1]);

  return  (z[i + 1] /(6 * h[i])) 
        * exp3(x - t[i])
        + (z[i] / (6 * h[i]))
        * exp3(t[i + 1] - x)
        + (y[i + 1] / h[i] - z[i + 1] * h[i] / 6)
        * (x - t[i])
        + (y[i] / h[i] - h[i] * z[i] / 6)
        * (t[i + 1] - x);

}


