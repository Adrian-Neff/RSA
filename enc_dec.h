// Author: Adrian Neff
// File: enc_dec.h
// Synopsis: Header file containing functions for encrypting and decrypting messages for use in the RSA algorithm.

#ifndef ENC_DEC_H
#define ENC_DEC_H

#include <gmp.h>

void encryption(mpz_t C, mpz_t e, mpz_t N, mpz_t message);
void decryption(mpz_t C, mpz_t d, mpz_t N, mpz_t message);

// Encrypts the message for use in the RSA algorithm
void encryption(mpz_t C, mpz_t e, mpz_t N, mpz_t message){
  mpz_powm(C, message, e, N);          // C = ((message) ^ e) mod N

  return;
}

// Decrypts the message used in the RSA algorithm
void decryption(mpz_t C, mpz_t d, mpz_t N, mpz_t message){
  mpz_powm(message, C, d, N);          // message  = (C ^ d) mod N
  
  return;
}

#endif
