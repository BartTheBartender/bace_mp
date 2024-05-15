//Bartosz Furmanek
using integer = unsigned;
using num = double;
class spline{
  integer n;
  num* t;
  num* h;
  num* y;
  num* z;
public:
    void debug_print() const;
    spline(integer);
    void set_points(double x[], double y[]);
    double operator() (double z) const;
    ~spline();
};

