//Krzysztof Golebiowski

#include <iostream>
#include <cmath>

double sieczne(double& a, double& b, double& fa, double& fb){
    return a - fa*( (a-b) / (fa - fb) );
}

double findZero(
    double (*f)(double),  // funkcja której zera szukamy w [a, b] 
    double a,             // lewy koniec przedziału
    double b,             // prawy koniec przedziału
    int M,                // maksymalna dozwolona liczba wywołań funkcji f
    double eps,           // spodziewana dokładność zera
    double delta          // wystarczający błąd bezwzględny wyniku
){
    int licznik = 2;
    double fa = f(a), fb = f(b);
    double temp, ftemp;

    if(fabs(fa) < eps) return a;
    if(fabs(fb) < eps) return b;

    while( (fa*fb > 0) and licznik < M and (fabs(fa) >= eps) and (fabs(fb) >= eps) and (fabs(a-b) >= delta)){ //Sieczne, aż znajdziemy wartości o przeciwnych znakach
        
        temp = sieczne(a,b,fa,fb);
        a = b; fa = fb;
        b = temp; fb = f(b);

        if(fabs(fb) < eps) return b;

        ++licznik;
    }

    while( licznik < M and (fabs(fa) >= eps) and (fabs(fb) >= eps) and (fabs(a-b) >= delta)){
        if(fabs(a-b) >= 0.01){ // Bisekcja
            temp = (a+b)/2;
            ftemp = f(temp);
            ++licznik;

            if(fabs(ftemp) < eps) return temp;

            if(fa*ftemp < 0){b=temp;fb=ftemp;}
            else{a=temp;fa=ftemp;}

        } else { // Sieczne
            temp = sieczne(a,b,fa,fb);
            a = b; fa = fb;
            b = temp; fb = f(b);

            if(fabs(fb) < eps) return b;

            ++licznik;
        }
    }

    if(fabs(fa) <= eps) return a;
    return b;
}