#include <iostream>
#include "funkcja.h"
#include <cmath>
#include <iomanip>

using namespace std;

typedef double d;

struct FAD{
    d dzet[6]; // (f, fx, fy, fxx, fxy, fyy)

    d& operator()(int i) {return dzet[i];}
    d operator()(int i) const {return dzet[i];}

    FAD() {for(int i=0; i<6; ++i) dzet[i]=0;}

    FAD(const FAD& f) {for(int i=0; i<6; ++i) dzet[i]=f(i);}

    FAD(d arg){
        *dzet = arg;
        for(int i=1; i<6; ++i) dzet[i]=0;
    }

    FAD(d arg, char c){
        *dzet = arg;
        for(int i=1; i<6; ++i) dzet[i]=0;

        if(c=='x') dzet[1] = 1;
        else if(c=='y') dzet[2] = 1;
    }

    FAD& operator=(const FAD& f) {for(int i=0; i<6; ++i) dzet[i]=f(i); return *this;}
};


FAD operator+(const FAD& a, const FAD& b){
    FAD res;
    for(int i=0; i<6; ++i) res(i)=a(i) + b(i);
    return res;
}

FAD operator+(const FAD& a, const d& b){
    FAD res;
    res(0) = a(0) + b;
    for(int i=1; i<6; ++i) res(i)=a(i);
    return res;
}

FAD operator-(const FAD& a, const FAD& b){
    FAD res;
    for(int i=0; i<6; ++i) res(i)=a(i) - b(i);
    return res;
}

FAD operator-(const FAD& a, const d& b){
    FAD res;
    res(0) = a(0) - b;
    for(int i=1; i<6; ++i) res(i)=a(i) - b;
    return res;
}

FAD operator-(const FAD& a){
    FAD res;
    for(int i=0; i<6; ++i) res(i)= -a(i);
    return res;
}

FAD operator*(const FAD& a, const FAD& b){
    FAD res;
    res(0) = a(0) * b(0);
    res(1) = a(1) * b(0) + a(0) * b(1);
    res(2) = a(2) * b(0) + a(0) * b(2);
    res(3) = a(3) * b(0) + 2 * a(1) * b(1) + a(0) * b(3);
    res(4) = a(4) * b(0) + a(1) * b(2) + a(2) * b(1) + a(0) * b(4);
    res(5) = a(5) * b(0) + 2 * a(2) * b(2) + a(0) * b(5);
    return res;
}

FAD operator*(const FAD& a, const d& b){
    FAD res;
    for(int i=0; i<6; ++i) res(i)=a(i) * b;
    return res;
}

FAD odwr(const FAD& a){
    FAD res;
    d dwa = (a(0) * a(0));
    d trzy = dwa * a(0);
    res(0) = 1/a(0);
    res(1) = -a(1) / dwa;
    res(2) = -a(2) / dwa;
    res(3) = 2 * a(1) * a(1) / trzy - a(3) / dwa;
    res(4) = 2 * a(1) * a(2) / trzy - a(4) / dwa;
    res(5) = 2 * a(2) * a(2) / trzy - a(5) / dwa;
    return res;
}

FAD operator/(const FAD& a, const FAD& b){
    FAD res;
    d dwa = (b(0) * b(0));
    d trzy = dwa * b(0);
    res(0) = a(0)/b(0);
    res(1) = ( a(1) * b(0) - a(0) * b(1) ) / dwa;
    res(2) = ( a(2) * b(0) - a(0) * b(2) ) / dwa;

    res(3) = a(3) / b(0) - 2 * a(1) * b(1) / dwa -                     a(0) * b(3) / dwa + 2 * a(0) * b(1) * b(1) / trzy;

    res(4) = a(4) / b(0) -     a(1) * b(2) / dwa - a(2) * b(1) / dwa - a(0) * b(4) / dwa + 2 * a(0) * b(1) * b(2) / trzy;

    res(5) = a(5) / b(0) - 2 * a(2) * b(2) / dwa -                     a(0) * b(5) / dwa + 2 * a(0) * b(2) * b(2) / trzy;
    return res;
    // return a * odwr(b);
}

FAD operator/(const FAD& a, const d& b){
    FAD res;
    for(int i=0; i<6; ++i) res(i)=a(i) / b;
    return res;
}

FAD sin(const FAD& a){
    FAD res;
    d sinus   = sin(a(0));
    d cosinus = cos(a(0));
    res(0) = sinus;
    res(1) = cosinus * a(1);
    res(2) = cosinus * a(2);
    res(3) = -sinus * a(1) * a(1) + cosinus * a(3);
    res(4) = -sinus * a(1) * a(2) + cosinus * a(4);
    res(5) = -sinus * a(2) * a(2) + cosinus * a(5);
    return res;
}

FAD cos(const FAD& a){
    FAD res;
    d sinus   = sin(a(0));
    d cosinus = cos(a(0));
    res(0) = cosinus;
    res(1) = -sinus * a(1);
    res(2) = -sinus * a(2);
    res(3) = -cosinus * a(1) * a(1) - sinus * a(3);
    res(4) = -cosinus * a(1) * a(2) - sinus * a(4);
    res(5) = -cosinus * a(2) * a(2) - sinus * a(5);
    return res;
}

FAD exp(const FAD& a){
    FAD res;
    d help = exp(a(0));
    res(0) = help;
    res(1) = help * a(1);
    res(2) = help * a(2);
    res(3) = help * (a(1) * a(1) + a(3));
    res(4) = help * (a(1) * a(2) + a(4));
    res(5) = help * (a(2) * a(2) + a(5));
    return res;
}

void show(FAD f){
    for(int i=0; i<6; ++i) cout << f(i) << " ";
    cout << "\n";
}

int main(){
    int M; cin >> M;
    double x,y;

    cout << fixed << setprecision(15);

    for(int i=0; i<M; ++i){
        cin >> x; cin >> y;

        show(funkcja(FAD(x,'x'),FAD(y,'y')));
    }

    return 0;
}
