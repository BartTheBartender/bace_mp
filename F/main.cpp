//Bartosz Furmanek
#include <iostream>
#include <iomanip>
#include <memory>
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;
typedef double num;

class Vector {
private:
    size_t n;
    std::unique_ptr<num[]> data = nullptr;
public:

    explicit Vector(size_t n = 0) : n(n) {
        data.reset(new num[n]);
    }

    Vector(const Vector &m) : n(m.n), data(new num[m.n]) {
        std::copy(m.data.get(), m.data.get() + n, data.get());
    }

    Vector(Vector &&m) noexcept : n(m.n), data(std::move(m.data)) {
        m.n = 0;
    }

    Vector(const std::initializer_list<num> &list) : n(list.size()) {
        data.reset(new num[n]);
        std::copy(list.begin(), list.end(), data.get());
    }

    Vector &operator=(const Vector &m) {
        if (this != &m) {
            if (n != m.n) {
                data.reset(new num[m.n]);
                n = m.n;
            }
            std::copy(m.data.get(), m.data.get() + n, data.get());
        }
        return *this;
    }

    Vector &operator=(Vector &&m) noexcept {
        data = std::move(m.data);
        n = m.n;
        return *this;
    }

    inline size_t size() const {
        return n;
    }


    num operator[](size_t index) const {
        assert(index < n);
        return data[index];
    }

    num &operator[](size_t index) {
        assert(index < n);
        return data[index];
    }

    num max_norm() const {
        num norm = 0;
        for (num x: *this) {
            norm = std::max(norm, std::abs(x));
        }
        return norm;
    }

    typedef num *iterator;

    iterator begin() {
        return data.get();
    }

    iterator end() {
        return data.get() + n;
    }

    typedef const num *const_iterator;

    const_iterator begin() const {
        return data.get();
    }

    const_iterator end() const {
        return data.get() + n;
    }

    friend inline std::ostream &operator<<(std::ostream &out, const Vector &m) {
      for (auto x : m) {
          out << x << endl;
      }
      return out;
    }


    friend inline std::istream &operator>>(std::istream &in, Vector &m) {
      for (auto &x : m) {
          in >> x;
      } 
      return in;
    }
};

class Matrix {
private:
  size_t n,m;
  unique_ptr<unique_ptr<num[]>[]> buf;
public:
  
  Matrix(std::istream& in) {
    in >> n >> m;

    buf.reset(new unique_ptr<num[]>[m+1]);

    for(size_t i = m; i <= m; --i) {
      buf[i].reset(new num[n-i]);
      for(size_t j = 0; j < n-i; ++j) {
        in >> buf[i][j];
      }

    }
  }

  inline size_t size() const {
    return n;
  }
  inline size_t nof_strips() const {
      return m;
  }

  void debug_print() const {
    for(size_t i = 0; i <= m; ++i) {
      for(size_t j = 0; j < n - i; ++j)
        cout << buf[i][j] << " ";
      cout << endl;
    }
  }

  num operator()(size_t i, size_t j) const {
    assert(i < n);
    assert(j < n);

    if (i > j)
      swap(i,j);

    return (j-i > m)? 0: buf[j-i][i];

  }

  friend inline std::ostream &operator<<(std::ostream &out, const Matrix &a) {
    for(size_t i = 0; i < a.size(); ++i) {
      for(size_t j = 0; j < a.size(); ++j) {
        out << a(i,j) << " ";
      }
      out << endl;
    }
    return out;
  }
};


Vector sor(const Matrix& a, const Vector& b, const num omega, const Vector& x) {
    size_t n = a.size();
    assert(n == b.size());
    assert(n == x.size());

    Vector y(n);


    for (size_t i = 0; i < n; ++i) {
        size_t beg = (a.nof_strips() > i) ? 0 : (i - a.nof_strips());
        size_t end = min(a.size() - 1, i + a.nof_strips());
        y[i] = b[i];

        for (size_t j = beg; j < i; ++j) {
            y[i] -= a(i, j) * y[j];
        }

        for (size_t j = i + 1; j <= end; ++j) {
            y[i] -= a(i, j) * x[j];
        }

        y[i] = y[i] * omega / a(i, i) + (1 - omega) * x[i];
    }

    return y;
}

int main(){
  std::cout << std::scientific << std::setprecision(16);
  Matrix a(std::cin);
  Vector b(a.size()), x(a.size()); cin >> b >> x;
  num omega; cin >> omega;
  size_t l; cin >> l;

  /* cout << "a:" << endl << a << "b:" << endl << b << endl << "x:" << endl << x << endl << "omega: " << omega << " l: " << l << endl; */

  for(size_t i = 0; i < l; ++i)
    x = sor(a,b,omega,x);
  cout << x << endl;

}
