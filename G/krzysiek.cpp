#include <iostream>
using namespace std;
typedef double d;

int M, N; 
d *X, *Y, *T, *W;

d silnia(int i){
    int r=1;
    for(int j=2; j<=i; ++j) r*=j;
    return r;
}

d deriv(d x, int k){
    int i=0;
    while(X[i]!=x) ++i;
    /* printf("i: %d\n", i); */
    return Y[i+k];
}

d diff(int k, int l){
    if(X[k] == X[l]) return deriv(X[k],l-k)/silnia(l-k);
    return ( diff(k+1,l)-diff(k,l-1) ) / ( X[l]-X[k] );
}

int main(){
    scanf("%d%d",&M,&N);
    
    X = new d[M];
    Y = new d[M];
    W = new d[M];
    T = new d[N];
    for (int i=0; i<M; ++i) scanf("%lf",X+i);
    for (int i=0; i<M; ++i) scanf("%lf",Y+i);
    for (int i=0; i<N; ++i) scanf("%lf",T+i);

    for (int i=0; i<M; ++i){
        W[i] = diff(0,i);
    }

    for (int i=0; i<M; ++i) printf("%.17lf ",W[i]);
    printf("\n");

    d F, mult;

    for (int i=0; i<N; ++i){
        F=0;
        mult=1;

        for (int j=0; j<M-1; ++j){
            F+=W[j]*mult;
            mult*=(T[i]-X[j]);
        }
        F+=W[M-1]*mult;

        printf("%.17lf ",F);
    }

    printf("\n");

    delete[] X;
    delete[] Y;
    delete[] T;

    return 0;
}
