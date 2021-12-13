#include "Shamir.h"

#include <iostream>
#include <algorithm>

shamir::Encoder::Encoder(int t, int n, int s) : t(t), n(n), s(s), p(0){}

void shamir::Encoder::encode() {
   pairs.clear();
   p = tools::primeNumber(std::max(s, n), 2 * std::max(s, n));
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

int shamir::Decoder::decode(std::vector<int> pairs, int p, int t) {
   int sum = 0;
   for (size_t i = 1; i <= t; ++i) {
      auto f = lagrangeConstant(i, t);
      int c = f.n * pairs[i - 1] / f.d;
      sum += c % p;
   }

   if (sum < 0) {
      sum += p;
   }
   if (sum > p) {
      sum = sum % p;
   }
   return sum;
}

tools::Fraction shamir::Decoder::lagrangeConstant(int x, int t) {
   int numerator = 1;
   int denominator = 1;
   for (int i = 1; i <= t; ++i) {
      if (i != x) {
         numerator *= (-i);
         denominator *= (x - i);
      }
   }
   return { numerator, denominator };
}