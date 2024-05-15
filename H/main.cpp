#include <iostream>
/* #include <vector> */
#include "source.h"

using namespace std;
int main() {
   
   /* cout.precision(15); */
   /* cout << fixed; */
  
   int size = 6; 
   double X[] = {0, 0.2, 0.4, 0.6, 0.8, 1};
   double Y[] = {-3,-2.56,-2.04,-1.44,-0.76,0};

   /* for(int i = 0; i < size; ++i) */
   /*   cout << X[i] << " "; */
   /* cout << endl; */

   spline s(size);
   s.set_points(X, Y);    
   /* s.debug_print(); */
   for(int i=0; i < size - 1; i++) {
     std::cout << s(X[i]) << "  " << s(X[i]+0.02) << "  "<< s(X[i]+0.07) <<  std::endl;
   }
    
   return 0;
}
