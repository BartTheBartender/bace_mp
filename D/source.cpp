//Bartosz Furmanek
#include "vectalg.h"
using namespace std;

/* Vector operator*(const Matrix& A, const Vector& x){ */
/*   assert(A.size() == x.size()); */
/*   size_t n = x.size(); */
/*   Vector y(n); */

/*   for(size_t i = 0; i < n; ++i) */
/*     assert(y[i] == 0); */

/*   for(size_t i = 0; i < n; ++i) */
/*     for(size_t j = 0; j < n; ++j) */
/*       y[i] += A(i,j) * x[j]; */
  

/*   return y; */
/* } */

Vector& operator+=(Vector& w, const Vector& v) {
  assert(w.size() == v.size());

  for(size_t i = 0; i < w.size(); ++i) {
    w[i] += v[i];
  }

  return w;
}

Vector solve_naive(Matrix A, Vector b, Vector s) {
  assert(A.size() == b.size());
  assert(s.size() == b.size());
  size_t n = A.size();


  for(size_t k = 0; k < n - 1; ++k) {

    size_t i = k;
    double max = 0, tmp = 0;

    for(size_t j = k; j < n; ++j) {
      tmp = fabs(A(j,k)) / s[j];

      if(max < tmp) {
        i = j;
        max = tmp;
      }
    }

    if(i != k) {

      std::swap(s[k], s[i]);
      std::swap(b[k], b[i]);
      for(size_t j = 0; j < n; ++j)
        std::swap(A(k,j), A(i,j));
    }

    for(size_t i = k + 1; i < n; ++i) {

      tmp = A(i,k) / A(k,k);
      A(i,k) = 0;
      b[i] -= tmp * b[k];

      for(size_t j = k + 1; j < n; ++j)
        A(i,j) -= tmp * A(k,j);
    }
  }
  

  Vector x(n);

  for(size_t i = n - 1; i < n; --i) {
    x[i] = 0;

    for(size_t j = i + 1; j < n; ++j)
      x[i] -= x[j] * A(i,j);

    x[i] += b[i];
    assert(A(i,i) != 0);
    x[i] /= A(i,i);
  }

  return x;
}

Vector solveEquations(
        const Matrix& A,
        const Vector& b,
        double eps
) {
    assert(A.size() == b.size());
    size_t n = A.size();

    Vector s(n);
    for(size_t i = 0; i < n; ++i) {
      s[i] = 0;
      for(size_t j = 0; j < n; ++j)
        if(s[i] < fabs(A(i,j)))
          s[i] = fabs(A(i,j));
    }

    Vector x = solve_naive(A,b,s),r,e;

    while(true) {

      r = residual_vector(A, b, x);

      if(r.max_norm() < eps)
        return x;

      e = solve_naive(A, r, s);
      x += e;
    }

}



