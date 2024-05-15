//Bartosz Furmanek
#include <math.h>
#include <cassert>
#include <stdint.h>
#include <iostream>
#include <iomanip>
using namespace std;
using num = double;
using smol = uint_fast16_t;
using integer = uint_fast16_t;

smol m;
integer n;
num x[100];
num y[100];
num w[100];
num t[100000];
smol min_idx[100];
num value, acc;

num derivative(smol x_idx, smol k) {
  return y[min_idx[x_idx] + k];
}

integer factorial[8] = {1, 1, 2, 6, 24, 120, 720, 5040};

//f[xi...xj]
num difference_quotient(smol i, smol j) {
  if(min_idx[i] == min_idx[j]) {
    return derivative(i, j - i)/ factorial[j - i];
  } else {
    return (difference_quotient(i + 1, j) - difference_quotient(i, j - 1))/(x[j] - x[i]);
  }
}

int main(){
  cout << fixed << setprecision(17);
  cin >> m >> n;

  num prev = nan("it should be different than x0"), curr;
  smol min;

  for(smol i = 0; i < m; ++i){
    cin >> curr;
    if(prev != curr){
      min = i;
    }
    min_idx[i] = min;
    x[i] = curr;
    prev = curr;
  }
  for(smol i = 0; i < m; ++i)
    cin >> y[i];
  for(smol i = 0; i < m; ++i){
    /* cout << "i: " << i << endl; */
    w[i] = difference_quotient(0, i);
  }

  for(integer i = 0; i < n; ++i)
    cin >> t[i];

  for(smol i = 0; i < m; ++i)
    cout << w[i] << " ";
  cout << endl;

  for(integer i = 0; i < n; ++i) {
    value = 0;
    acc = 1;

    for(integer j = 0; j < m - 1; ++j) {
      value += w[j] * acc;
      acc *= t[i] - x[j];
    }

    value += w[m - 1] * acc;
    cout << value << " ";
  }

  cout << endl;
  return 0;
}

