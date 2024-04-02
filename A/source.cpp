//Bartosz Furmanek
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <cmath>
using namespace std;

bool equal(float p, float q){
  return fabs((p-q)/q) < 1e-6 || fabs((p-q)) < 1e-25;
}

float cube_root(float a) {
    assert(a != 0);
    float x = ((a > 0) - (a < 0)) * pow(fabs(a),1.0/3.0);
    return x;
}

int main () {

  cout.setf(std::ios_base::scientific, std::ios_base::floatfield);
  cout << std::setprecision(10);

  size_t n;
  cin >> n;

  for (size_t i = 0; i < n; ++i) {
    float p, s;
    cin >> p >> s;
    if (p == 0) {
      cout << 0.f << " " << 0.f << " " << 0.f << endl;
    } else {
      float b = cube_root(p);
      assert(equal(b*b*b,p));

      float q = s/b - 1;
      assert(!isinf(q) && !isnan(q));

      if (q < 2 && q > -2) {
        cout << 0.f << " " << 0.f << " " << 0.f << endl;
      } else {
        float r = (q + sqrt(q*q-4))/2;

        assert(!isinf(r) && !isnan(r));
        assert(q != 0);
        if(r == 0) {
          r = (q - sqrt(q*q-4))/2;
        }

        assert(!isinf(r) && !isnan(r));
        assert(r != 0);
        float a = b*r, c = b/r;

        //let a be the greater one;
        if (a < c) {
          float temp = a;
          a = c;
          c = temp;
        }

        assert(a >= c);
        assert(equal(a+b+c,s));
        assert(equal(a*b*c,p));
        cout << a << " " << b << " " << c << endl;
      }
    }
    
  }

}

