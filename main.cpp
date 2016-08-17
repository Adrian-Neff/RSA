// Author: Adrian Neff
// File: main.cpp
// Synopsis: Main file for RSA program.

#include <iostream>
#include <cstring>
#include <gmp.h>
#include "P_gen.h"
#include "Ex_Euc.h"
using namespace std;

void totient(mpz_t p, mpz_t q, mpz_t phi);

// Main function for the RSA program
int main(){
  int k = 65;                               // Used for accuracy of MR test
  mpz_t p, q, N, phi, e, d, C;              // Used for encryption and decryption
  mpz_inits(p, q, N, phi, e, d, C, NULL);

  // Generate two random 1024-bit primes--p and q
  primes_generate(p, q, k);

  // Compute N = p * q
  mpz_mul(N, p, q);

  // Compute totient
  totient(p, q, phi);

  // Choose e; 65537 is used as the industry standard; e is coprime to phi and N and 1 < e < phi
  mpz_set_ui(e, 65537);

  // Find the value of d using the Extended Euclidean algorithm; d is the modular inverse of e mod phi
  EEA(phi, e, d);

  mpz_out_str(stdout, 10, p);
  cout << endl << endl;
  mpz_out_str(stdout, 10, q);
  cout << endl << endl;
  mpz_out_str(stdout, 10, N);
  cout << endl << endl;
  mpz_out_str(stdout, 10, phi);
  cout << endl << endl;
  mpz_out_str(stdout, 10, e);
  cout << endl << endl;
  mpz_out_str(stdout, 10, d);

  mpz_clears(p, q, N, phi, e, d, C, NULL);
  
  return(0);
}

// Computes the totient of N: phi = (p - 1)(q - 1)
void totient(mpz_t p, mpz_t q, mpz_t phi){
  mpz_t p2, q2;
  mpz_inits(p2, q2, NULL);

  // Compute totient
  mpz_sub_ui(p2, p, 1);        // p - 1
  mpz_sub_ui(q2, q, 1);        // q - 1
  mpz_mul(phi, p2, q2);        // phi = (p - 1)(q - 1)

  return;
}
