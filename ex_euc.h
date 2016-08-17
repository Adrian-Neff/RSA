// Author: Adrian Neff
// File: Ex_Euc.h
// Synopsis: Header file containing the Extended Euclidean algorithm to solve for d.

#ifndef EX_EUC_H
#define EX_EUC_H

#include <gmp.h>

void EEA(mpz_t x, mpz_t y, mpz_t d);

// Finds the value of d (modular inverse of e) using the Extended Euclidean algorithm
void EEA(mpz_t phi, mpz_t e, mpz_t d){
  mpz_t a, b, g, u, v, w, q, temp1, temp2, temp3, temp4;
  mpz_inits(a, b, g, u, v, w, q, temp1, temp2, temp3, temp4, NULL);
  mpz_set_ui(a, 1);
  mpz_set_ui(b, 0);
  mpz_set(g, phi);
  mpz_set_ui(u, 0);
  mpz_set_ui(v, 1);
  mpz_set(w, e);

  // Loop to find the modular inverse using the algortithm
  while((mpz_cmp_ui(w, 0)) > 0){
    mpz_fdiv_q(q, g, w);                   // Floor(g / w)
    mpz_set(temp1, a);
    mpz_set(a, u);                         // a = u
    mpz_set(temp2, b);
    mpz_set(b, v);                         // b = v
    mpz_set(temp3, g);
    mpz_set(g, w);                         // g = w
    mpz_mul(temp4, q, u);
    mpz_sub(u, temp1, temp4);              // u = a - (q * u)
    mpz_mul(temp4, q, v);
    mpz_sub(v, temp2, temp4);              // v = b - (q * v)
    mpz_mul(temp4, q, w);
    mpz_sub(w, temp3, temp4);              // w = g - (q * w)
  }

  mpz_set(d, b);
  
  return;
}

#endif
