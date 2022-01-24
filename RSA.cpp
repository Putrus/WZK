#include "RSA.h"

#include "Tools.h"

void RSA::calculate() {
   int p = 31;
   std::cout << "p = " << p << std::endl;
   int q = 19;
   std::cout << "q = " << q << std::endl;
   int n = p * q;
   std::cout << "n = " << n << std::endl;
   int phi = (p - 1) * (q - 1);
   std::cout << "phi = " << phi << std::endl;
   int e = 7;
   std::cout << "e = " << e << std::endl;
   int d = 463;
   int m = 27;
   std::cout << "m = " << m << std::endl;
   int c = (int)pow(double(m), double(e)) % n;
   std::cout << "Encode: m: " << m << " c: " << c << std::endl;
   m = (int)pow(double(c), double(d)) % n;
   std::cout << "Decode: m: " << m << " c: " << c << std::endl;
}