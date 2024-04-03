// Krzysztof Golebiowski
#include "vectalg.h"

Vector iteracja(const Matrix & A0, const Vector & b){
    
    int n = b.size();

    Matrix A = A0;
    Vector nb = b; //nowe b

    // Liczymy skale wierszy
    Vector s(n);
    for(int i=0; i<n; ++i){
        s[i] = 0;
        for(int j = 0; j<n; ++j){
            if(s[i] < fabs(A(i,j))) s[i] = fabs(A(i,j));
        }
    }

    int g;
    double maks, temp;

    // Guassujemy macierz
    for(int k=0; k<n-1; ++k){
        // Znajdujemy element główny
        maks = 0;
        g = k;
        for(int i=k; i<n; ++i){
            temp = fabs(A(i,k))/s[i];
            if(maks < temp){
                g = i;
                maks = temp;
            }
        }

        // Ustawiamy element główny na przekątnej
        if(g!=k){
            //Trzeba dokonać zamiany k-tego i g-tego wiersza
            for(int i=k; i<n; ++i){
                temp = A(k,i);
                A(k,i) = A(g,i);
                A(g,i) = temp;
            }

            temp=s[k];
            s[k] = s[g];
            s[g] = temp;

            temp=nb[k];
            nb[k] = nb[g];
            nb[g] = temp;
        }

        // Dokonujemy eliminacji
        for(int i=k+1; i<n; ++i){
            temp = A(i,k)/A(k,k);
            A(i,k)=0;
            for(int j = k+1; j<n; ++j){
                A(i,j) -= temp*A(k,j);
            }
            nb[i] -= temp*nb[k];
        }
    }
    
    // Podstawienia wstecz
    Vector x(n);

    for(int i=n-1; i>=0; --i){
        x[i] = 0;
        for(int j = i+1; j<n; ++j){
            x[i] -= x[j]*A(i,j);
        }
        x[i] += nb[i];
        x[i] /= A(i,i);
    }

    return x;
}

Vector solveEquations(const Matrix & A0, const Vector & b, double eps){
    int n = b.size();

    Vector x = iteracja(A0,b);
    Vector r = residual_vector(A0,b,x);
    Vector e;

    while(! (r.max_norm() < eps)){
        e = iteracja(A0,r);
        for(int i=0; i<n; ++i){
            x[i] += e[i];
        }
        r = residual_vector(A0,b,x);
    }

    return x;
}