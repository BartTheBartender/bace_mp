//Bartosz Furmanek
#include "funkcja.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;
typedef double num;

class Jet {
  num v;
  num x;
  num y;
  num xx;
  num xy;
  num yy;

  Jet(const num v, const num x, const num y, const num xx, const num xy, const num yy): v(v), x(x), y(y), xx(xx), xy(xy), yy(yy) {}

  static Jet inverse(const Jet& f) {
    return Jet(
        1/f.v, -f.x/(f.v * f.v),
        -f.y/(f.v * f.v),
        (2 * f.x * f.x - f.xx * f.v)/(f.v * f.v * f.v),
        (2 * f.x * f.y - f.xy * f.v)/(f.v * f.v * f.v),
        (2 * f.y * f.y - f.yy * f.v)/(f.v * f.v * f.v)
    );
  }

public:

  Jet(): v(0), x(0), y(0), xx(0), xy(0), yy(0) {}
  Jet(const Jet& f): v(f.v), x(f.x), y(f.y), xx(f.xx), xy(f.xy), yy(f.yy) {}
  Jet& operator=(const Jet& f) {
    v = f.v; x = f.x; y = f.y; xx = f.xx; xy = f.xy; yy = f.yy;
    return *this;
  }

  static Jet from_x(num r) {
    return Jet(r,1,0,0,0,0);
  }

  static Jet from_y(num r){
    return Jet(r,0,1,0,0,0);
  }

  friend ostream& operator<<(ostream& out, const Jet& f) {
    out << f.v
        << " " << f.x
        << " " << f.y
        << " " << f.xx
        << " " << f.xy
        << " " << f.yy;
   return out;
  }

  friend Jet operator+(const Jet& f, const Jet& g) {
    return Jet(
      f.v + g.v,
      f.x + g.x,
      f.y + g.y,
      f.xx + g.xx,
      f.xy + g.xy,
      f.yy + g.yy
    );
  }

  friend Jet operator-(const Jet& f, const Jet& g) {
    return Jet(
      f.v - g.v,
      f.x - g.x,
      f.y - g.y,
      f.xx - g.xx,
      f.xy - g.xy,
      f.yy - g.yy
    );
  }

  friend Jet operator-(const Jet& g) {
    return Jet(
      - g.v,
      - g.x,
      - g.y,
      - g.xx,
      - g.xy,
      - g.yy
    );
  }

  friend Jet operator+(const Jet& f, const num r){
    return Jet(f.v + r, f.x, f.y, f.xx, f.xy, f.yy);
  }

  friend inline Jet operator+(const num r, const Jet& f) {
    return f + r;
  }

  friend Jet operator-(const Jet& f, const num r){
    return Jet(f.v - r, f.x, f.y, f.xx, f.xy, f.yy);
  }

  friend inline Jet operator-(const num r, const Jet& f) {
    return f - r;
  }

  friend Jet operator*(const Jet& f, const Jet& g) {
    return Jet(
        f.v * g.v,
        f.x * g.v + f.v * g.x,
        f.y * g.v + f.v * g.y,
        f.xx * g.v + 2 * f.x * g.x + f.v * g.xx,
        f.xy * g.v + f.x * g.y + f.y * g.x + f.v * g.xy,
        f.yy * g.v + 2 * f.y * g.y + f.v * g.yy
    );
  }

  friend Jet operator*(const Jet& f, const num r) {
    return Jet(f.v * r, f.x * r, f.y * r, f.xx * r, f.xy * r, f.yy * r);
  }

  inline friend Jet operator*(const num r, const Jet& f){
    return f*r;
  }

  inline friend Jet operator/(const Jet& f, const Jet& g) {
    return f * Jet::inverse(g);
  }

  inline friend Jet operator/(const Jet& f, const num r) {
    return f * (1/r);
  }

  inline friend Jet operator/(const num r, const Jet& f) {
    return r * Jet::inverse(f);
  }

  friend Jet sin(const Jet& f) {
    return Jet (
        sin(f.v),
        f.x * cos(f.v),
        f.y * cos(f.v),
        f.xx * cos(f.v) - f.x * f.x * sin(f.v),
        f.xy * cos(f.v) - f.x * f.y * sin(f.v),
        f.yy * cos(f.v) - f.y * f.y * sin(f.v)
    );
  }

  friend Jet cos(const Jet& f) {
    return Jet (
        cos(f.v),
        -f.x * sin(f.v),
        -f.y * sin(f.v),
        -f.xx * sin(f.v) + f.x * f.x * sin(f.v),
        -f.xy * sin(f.v) + f.x * f.y * sin(f.v),
        -f.yy * sin(f.v) + f.y * f.y * sin(f.v)
    );
  }

  friend Jet exp(const Jet& f) {
    return Jet (
        exp(f.v),
        f.x * exp(f.v),
        f.y * exp(f.v),
        f.xx * exp(f.v) + f.x * f.x * exp(f.v),
        f.xy * exp(f.v) + f.x * f.y * exp(f.v),
        f.yy * exp(f.v) + f.y * f.y * exp(f.v)
    );
  }

};


Jet eval(num x, num y){
  return funkcja(Jet::from_x(x), Jet::from_y(y));
}

int main () {
  /* cout << std::setprecision(4); */
  /* std::cout.setf(std::ios::fixed, std::ios::floatfield); */
  size_t n;
  cin >> n;
  num x,y;
  for(size_t i = 0; i < n; ++i){
    cin >> x >> y;
    cout << "x: " << x << " y: " << y << endl;
    /* cout << eval(x,y) << endl; */
  }
  return 0;
}
