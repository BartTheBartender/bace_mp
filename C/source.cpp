//Bartosz Furmanek
#include <cstdio>
#include <cmath>
#include <cassert>
using namespace std;

void print_vector(const double* x, unsigned N){
  for(unsigned i=0;i<N;++i)
    printf("%17.17f ",x[i]);
  printf("\n");
}


typedef void (*FuncPointer)(const double* x, double* y, double* Df);

bool is_correct(double* y, size_t n) {
  for(size_t i = 0; i < n; ++i)
    if(isnan(y[i]) || isinf(y[i]))
        return false;

  return true;
}

int findCurve(FuncPointer f, const double* x, unsigned k, double h) {  


  double y[2];
  double Df[2*3];
  double u[3];
  u[2] = x[2];
  double d00, d01, d10, d11, det;


  for(unsigned i = 1; i <= k; ++i) {

    u[0] = x[0];
    u[1] = x[1];
    u[2] += h;
    
    for(unsigned _ = 0; _ < 1000; ++_) {

      f(u,y,Df);


      if(fabs(y[0]) < 1e-14 && fabs(y[1]) < 1e-14)
        break;

      d00 = Df[0];
      d01 = Df[1];
      d10 = Df[3];
      d11 = Df[4];
      det = d00 * d11 - d01 * d10;

      if(det == 0 || !is_correct(y,2))
        return i;

      u[0] -=  (d11 * y[0] - d01 * y[1]) / det;
      u[1] -= (-d10 * y[0] + d00 * y[1]) / det;
      

    }

      if(fabs(y[0]) < 1e-14 && fabs(y[1]) < 1e-14)
        print_vector(u,3);
      else
        return i;
  }

  return 0;
}

int findSurface(FuncPointer f,
    double* x, unsigned k1, unsigned k2, double h1, double h2) {
  
  double y[1];
  double Df[1*3];
  double u[3];
  double df;
  
  u[1] = x[1];

  for(unsigned i1 = 1; i1 <= k1; ++i1) {

    u[1] += h1;
    u[2] = x[2];

    for(unsigned i2 = 1; i2 <= k2; ++i2) {

      u[2] += h2;
      u[0] = x[0];

      for(unsigned _ = 0; _ < 10000; ++_) {
          
        f(u,y,Df);
        df = Df[0];

        if(!is_correct(y,1) || df == 0)
          return i1*k1+i2;

        if(fabs(y[0]) < 1e-14)
          break;

        u[0] -= y[0]/df;

      }

      if(fabs(y[0]) < 1e-14)
        print_vector(u,3);
      else
        return i1*k1+i2;
    }
  }
  
  return 0;
}

int findFixedPoints(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2) {

  double y[1];
  double Df[1*3];
  double u[4];
  double df;

  /* for(unsigned i1 = ; i1 */
  
}

