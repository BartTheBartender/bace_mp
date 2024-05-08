#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdio>

const unsigned maxit = 10000;

typedef void (*FuncPointer)(const double* x, double* y, double* Df);

void B(){std::cout << "TU!" << std::endl;}

void printVector(const double* x, unsigned N){
  for(unsigned i=0;i<N;++i)
    printf("%17.3f ",x[i]);
  printf("\n");
}

bool fuj(const double* y, unsigned N){
    for(unsigned i=0;i<N;++i)
        if(std::isnan(y[i]) or std::isinf(y[i])) return true;
    return false;
}

int findCurve(FuncPointer f, double* x, unsigned k, double h){
    double a[3],y[2],Df[6];
    a[2] = x[2]; // c
    double& det = Df[5];
    // double& temp = Df[2];

    for(unsigned i=1; i<=k; ++i){
        a[0] = x[0];
        a[1] = x[1];
        a[2] += h;
        f(a,y,Df);

        for(unsigned iteracja=0; iteracja <= maxit; ++iteracja){
            // Interesują nas pola 0,1,3,4 tablicy Df, 2 i 5 służą za temp
            // Obliczamy wyznacznik różniczki f_c w punkcie a
            det = Df[0]*Df[4] - Df[1]*Df[3];
            if(det==0) return i;

            // Przybliżone miejsce zerowe to L^(-1)(-y) + a, gdzie L to wspomniana różniczka
            a[0] -= (y[0]*Df[4] - y[1]*Df[1])/det;
            a[1] -= (-y[0]*Df[3] + y[1]*Df[0])/det;

            f(a,y,Df);

            if(fuj(y,2)) return i;
            if(fabs(y[0]) < 1e-14 and fabs(y[1]) < 1e-14) break;
        }

        if(fabs(y[0]) < 1e-14 and fabs(y[1]) < 1e-14) printVector(a,3);
        else return i;
    }
    return 0;
}

int findSurface(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2){
    double a[3],y[1],Df[3];
    a[1] = x[1];

    for(unsigned i=1; i<=k1; ++i){
        a[1] += h1;
        a[2] = x[2];
        for(unsigned j=1; j<=k2; ++j){
            a[0] = x[0];
            a[2] += h2;
            f(a,y,Df);

            for(unsigned iteracja=0; iteracja <= maxit; ++iteracja){
                if(Df[0]==0) return (i-1)*k2+j;
                
                a[0] -= y[0]/Df[0];

                f(a,y,Df);

                if(fuj(y,1)) return (i-1)*k2+j;
                if(fabs(y[0]) < 1e-14) break;
            }

            if(fabs(y[0]) < 1e-14) printVector(a,3);
            else return (i-1)*k2+j;
        }
    }
    return 0;
}

int findFixedPoints(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2){
    double a[4],y[2],Df[8];
    a[2] = x[2];
    double& det = Df[3];

    for(unsigned i=1; i<=k1; ++i){
        a[2] += h1;
        a[3] = x[3];
        for(unsigned j=1; j<=k2; ++j){
            a[0] = x[0];
            a[1] = x[1];
            a[3] += h2;

            f(a,y,Df);

            // Tak naprawdę mamy do czynienia z g = f - id
            // Zamieńmy zatem y na y-a oraz Df na Df - 1

            y[0] -= a[0];
            y[1] -= a[1];
            Df[0] -= 1;
            Df[5] -= 1;

            for(unsigned iteracja=0; iteracja <= maxit; ++iteracja){
                det = Df[0]*Df[5] - Df[1]*Df[4];
                if(det==0) return (i-1)*k2+j;

                a[0] -= (y[0]*Df[5] - y[1]*Df[1])/det;
                a[1] -= (-y[0]*Df[4] + y[1]*Df[0])/det;

                f(a,y,Df);

                y[0] -= a[0];
                y[1] -= a[1];
                Df[0] -= 1;
                Df[4] -= 1;

                if(fuj(y,2)) return (i-1)*k2+j;
                if(fabs(y[0]) < 1e-14 and fabs(y[1]) < 1e-14) break;

                printVector(a,4);
            }
            if(fabs(y[0]) < 1e-14 and fabs(y[1]) < 1e-14) printVector(a,4);
            else return (i-1)*k2+j;
        }
    }
    return 0;
}
