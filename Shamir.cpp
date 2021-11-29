#include "Shamir.h"

#include <iostream>
#include <algorithm>

shamir::Encoder::Encoder(int t, int n, int s) : t(t), n(n), s(s), p(0){}

void shamir::Encoder::encode() {
   srand(static_cast<unsigned int>(time(NULL)));
   pairs.clear();
   p = tools::primeNumber(std::max(s, n), 3000);
   std::vector<int> a;
   for (int i = 0; i < t - 1; ++i) {
      a.push_back(tools::randomInt(1, s));
   }
   //i = 1,2,...n si = s + sum(ajx^i) mod p
   //remember that in a is 0,1,2...
   for (int i = 1; i <= n; ++i) {
      int si = s;
      for (int j = 0; j < t - 1; ++j) {
         si += a[j] * pow(i, j + 1);
      }
      pairs.push_back(si % p);
   }
}

std::vector<int> shamir::Encoder::getPairs() {
   return pairs;
}

int shamir::Encoder::getP() {
   return p;
}

int shamir::Decoder::decode(std::vector<int> pairs, int p) {
   int sum = 0;
   for (size_t i = 1; i <= 3; ++i) {
      auto f = lagrangeConstant(i, pairs.size());
      int c = f.n * pairs[i - 1] / f.d;
      bool negative = c < 0;
      while (c < 0) {
         c += p;
      }
      sum += (negative) ? (c - p) : (c % p);
   }
   return sum;
}

tools::Fraction shamir::Decoder::lagrangeConstant(int x, int t) {
   int numerator = 1;
   int denominator = 1;
   for (int i = 1; i <= 3; ++i) {
      if (i != x) {
         numerator *= (-i);
         denominator *= (x - i);
      }
   }
   return { numerator, denominator };
}