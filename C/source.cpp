//Bartosz Furmanek
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
using namespace std;

typedef void (*FuncPointer)(const double* x, double* y, double* Df);

int findCurve(FuncPointer f, const double* x, unsigned k, double h) {  
  cout << std::setprecision(17);

  double y[2];
  double Df[2*3];
  double u[3];
  double d00, d01, d10, d11;


  for(unsigned i = 1; i <= k; ++i) {
    u[0] = x[0] + i*h;
    u[1] = x[1] + i*h;
    u[2] = x[2] + i*h;

    
    for(unsigned _ = 0; _ < 100000; ++_) {
      f(u,y,Df);

      d00 = Df[0];
      d01 = Df[1];
      d10 = Df[3];
      d11 = Df[4];

      if(d00 * d11 - d01 * d10 == 0){
        return i;
      }

      u[0] -= (d11 * y[0] - d01 * y[1])/(d11 * d00 - d10 * d01);
      u[1] -= (-d10 * y[0] + d00 * y[1])/(d11 * d00 - d10 * d01);

      if(fabs(y[0]) < 10e-14 && fabs(y[1]) < 10e-14)
        break;
    }

      if(fabs(y[0]) < 10e-14 && fabs(y[1]) < 10e-14){
        cout << u[0] << " " << u[1] << " " << u[2] << endl;
      } else {
        return i;
      }
  }

  return 0;
}

int findSurface(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2) {
  assert(false);
}
int findFixedPoints(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2) {
  assert(false);
}

