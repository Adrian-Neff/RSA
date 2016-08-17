// Author: Adrian Neff
// File: main.cpp
// Synopsis: Main file for RSA program.

#include <iostream>
#include <cstring>
#include <fstream>
#include <gmp.h>
#include "P_gen.h"
#include "Ex_Euc.h"
#include "Enc_Dec.h"
using namespace std;
 
void totient(mpz_t p, mpz_t q, mpz_t phi);

// Main function for the RSA program
int main(){
  int k = 65;                                   // Used for accuracy of MR test
  string S;
  mpz_t p, q, N, phi, e, d;                     // Used for encryption and decryption
  mpz_inits(p, q, N, phi, e, d, NULL);

  cout << "Enter message: ";
  getline(cin, S);                              // Input message 
  
  char cha[S.length()];
  int array[S.length()];
  mpz_t *arr = new mpz_t[S.length()];           // Initialize all arrays to the length of the message
  for(int x = 0; x < S.length(); x++){
    mpz_init(arr[x]);
  }
  
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

  // Convert characters in the string into ASCII values in the integer array
  for(int i = 0; i < S.length(); i++){
    array[i] = S[i];
  }

  // Encrypt each character of the message 
  for(int j = 0; j < S.length(); j++){
    mpz_set_ui(arr[j], array[j]);
    encryption(arr[j], e, N, arr[j]);
  }

  // Open file for writing the message to
  ofstream myfile;
  myfile.open("message.txt");
  if(myfile.is_open()){
    
    // Decrypt each character of the message and write to file
    for(int i2 = 0; i2 < S.length(); i2++){
      decryption(arr[i2], d, N, arr[i2]);
      cha[i2] = mpz_get_ui(arr[i2]);
      myfile << cha[i2];
    }
  }
  myfile.close();

  // Clear all mpz variables
  mpz_clears(p, q, N, phi, e, d, NULL);
  for(int x2 = 0; x2 < S.length(); x2++){
    mpz_clear(arr[x2]);
  }
  
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
