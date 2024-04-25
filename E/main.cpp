//Bartosz Furmanek
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "funkcja.h"
using namespace std;

typedef long double num;

class Jet {
    num v, x, y, xx, xy, yy;
    explicit Jet(const num v, const num x, const num y,
        const num xx, const num xy, const num yy):
        v(v), x(x), y(y), xx(xx), xy(xy), yy(yy) {}
    explicit Jet(const num c) : Jet(c,0,0,0,0,0) {}
public:
    Jet(): Jet(0, 0, 0, 0, 0, 0) {}

    Jet(const Jet& f): Jet(f.v, f.x, f.y, f.xx, f.xy, f.yy) {}

    Jet& operator=(const Jet&f){
        v = f.v; x = f.x; y = f.y;
        xx = f.xx; xy = f.xy; yy = f.yy;
        return *this;
    }

    static Jet from_x(const num x) {
        return Jet(x, 1, 0, 0, 0, 0);
    }

    static Jet from_y(const num y) {
        return Jet(y, 0, 1, 0, 0, 0);
    }


    friend ostream& operator<<(ostream& out, const Jet& f) {
        out << "f.v: " << f.v << " f.x: " << f.x << " f.y: " << f.y << " f.xx: "
            << f.xx << " f.xy: " << f.xy << " f.yy: " << f.yy;
        /* out << f.v << " " << f.x << " " << f.y << " " */
        /*     << f.xx << " " << f.xy << " " << f.yy; */
        return out;
    }
  


    friend inline Jet operator+(const Jet& f, const Jet& g) {
      return Jet(f.v + g.v, f.x + g.x, f.y + g.y,
                f.xx + g.xx, f.xy + g.xy, f.yy + g.yy);
    }

    friend inline Jet operator-(const Jet& f, const Jet& g) {
      return Jet(f.v - g.v, f.x - g.x, f.y - g.y,
                f.xx - g.xx, f.xy - g.xy, f.yy - g.yy);
    }

    friend inline Jet operator-(const Jet& f) {
      return (-1) * f;
    }

    friend inline Jet operator+(const Jet& f, const num c) {
      return f + Jet(c);
    }

    friend inline Jet operator-(const num c, const Jet& f) {
      return c + (-f);
    }

    friend inline Jet operator-(const Jet& f, const num c) {
      return f + (-c);
    }

    friend inline Jet operator+(const num c, const Jet& f) {
      return f + c;
    }


    friend inline Jet operator*(const Jet& f, const Jet& g) {
      return Jet(f.v * g.v,
                f.x * g.v + f.v * g.x,
                f.y * g.v + f.v * g.y,
                f.xx * g.v + 2 * (f.x * g.x) + f.v * g.xx,
                f.xy * g.v + f.x * g.y + f.y * g.x + f.v * g.xy,
                f.yy * g.v + 2 * (f.y * g.y) + f.v * g.yy);
    }
    
    friend inline Jet operator*(const Jet& f, const num c) {
      return Jet(f.v * c, f.x * c, f.y * c,
              f.xx * c, f.xy * c, f.yy * c);
    }

    friend inline Jet operator*(const num c, const Jet& f) {
      return f * c;
    }

    friend inline Jet operator/(const Jet& f, const num c) {
        assert(false);
      assert(c != 0);
      return f * (1/c);
    }

    friend inline Jet operator/(const num c, const Jet& f) {
      assert(f.v != 0);
      return Jet(c)/f;
    }

    friend inline Jet operator/(const Jet& f, const Jet& g) {
      assert(g.v != 0);
      num inv_v = 1 / g.v;
      num inv_v_squared = inv_v * inv_v;
      num inv_v_cubed = inv_v_squared * inv_v;
      return Jet(f.v * inv_v,
                (f.x - f.v * g.x * inv_v) * inv_v,
                (f.y - f.v * g.y * inv_v) * inv_v,
                (f.xx - (2 * f.x * g.x + f.v * g.xx) * inv_v_squared + 2 * f.v * g.x * g.x * inv_v_cubed),
                (f.xy - (f.x * g.y + f.y * g.x + f.v * g.xy) * inv_v_squared + f.v * g.x * g.y * inv_v_cubed + f.v * g.y * g.x * inv_v_cubed),
                (f.yy - (2 * f.y * g.y + f.v * g.yy) * inv_v_squared + 2 * f.v * g.y * g.y * inv_v_cubed));
    }



    friend inline Jet sin(const Jet& f) {
        return Jet(sin(f.v),
                   f.x * cos(f.v),
                   f.y * cos(f.v),
                   f.xx * cos(f.v) - f.x * sin(f.v),
                   f.xy * cos(f.v) - f.y * sin(f.v),
                   f.yy * cos(f.v));
    }

    friend inline Jet cos(const Jet& f) {
        return Jet(cos(f.v),
                   -f.x * sin(f.v),
                   -f.y * sin(f.v),
                   -f.xx * sin(f.v) - f.x * cos(f.v),
                   -f.xy * sin(f.v) - f.y * cos(f.v),
                   -f.yy * sin(f.v));
    }

    friend inline Jet exp(const Jet& f) {
        num exp_v = exp(f.v);
        return Jet(exp_v,
                   f.x * exp_v,
                   f.y * exp_v,
                   f.xx * exp_v,
                   f.xy * exp_v,
                   f.yy * exp_v);
    }
    
};

Jet eval(const num x, const num y) {
    return funkcja(Jet::from_x(x), Jet::from_y(y));
}

int main(){
   /* cout << fixed << setprecision(15); */
   cout << fixed << setprecision(3);
  size_t n;
  cin >> n;
  num x,y;
  for(size_t _ = 0; _ < n; ++_){
    cin >> x >> y;
    cout << eval(x,y) << endl;
  }
}

