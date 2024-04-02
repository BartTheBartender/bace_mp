//Bartosz Furmanek
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <cmath>
using namespace std;

void d(){cout << "TU" << endl;}

bool equal(float p, float q){
  return fabs((p-q)/q) < 1e-6 || fabs((p-q)) < 1e-25;
}

float cube_root(float a) {
    assert(a != 0);
    float x = ((a > 0) - (a < 0)) * pow(fabs(a),1.0/3.0);
    /* float precision = 10e-4; */
    float y;
    size_t i = 0;

    do {
        /* cout << i++ << " " << x << endl; */
        y = x;
        x = (2 * x + a / (x * x)) / 3.0; 
    } while (!equal((y-x),0.f) && i < 1e6);

    return x;
}

int main () {

  cout.setf(std::ios_base::scientific, std::ios_base::floatfield);
  cout << std::setprecision(10);
  /* cout << std::setprecision(2); */

  size_t n;
  cin >> n;

  for (size_t i = 0; i < n; ++i) {
    float p, s;
    cin >> p >> s;
    /* cout << "new set: p: " << p << " s: " << s << endl; */

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
        /* float u = s - b; */
        /* float v = p/b; */
        float r = (q + sqrt(q*q-4))/2;

        assert(!isinf(r) && !isnan(r));
        assert(q != 0);
        if(r == 0) {
          r = (q - sqrt(q*q-4))/2;
        }

        assert(!isinf(r) && !isnan(r));
        assert(r != 0);

        /* cout << "r: " << r << endl; */
        
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

/* int main() { */
/*   cout.setf(std::ios_base::scientific, std::ios_base::floatfield); */
/*   cout << std::setprecision(10); */
/*   for(size_t i = 0; i < 9; ++i){ */
/*     float x; */
/*     cin >> x; */
/*     cout << cube_root(x) << endl; */
/*   } */
/* } */

