// Author: Adrian Neff
// File: P_gen.h
// Synopsis: Header file containing prime generation and tests for primality of a given number.

#ifndef P_GEN_H
#define P_GEN_H

#include <gmp.h>

// Tests for primality; prime generation
bool even_test(mpz_t num);
bool MR_test(mpz_t num, int k);
void mod_exp(mpz_t base, mpz_t exp, mpz_t n);
void primes_generate(mpz_t num);

// Generates random 1024-bit prime number
// num is the prime number; k is the accuracy of the MR test
void primes_generate(mpz_t num1, mpz_t num2, int k){
  mpz_t compare;
  gmp_randstate_t r_state;
  bool prime = false;

  mpz_init(compare);
  mpz_ui_pow_ui(compare, 2, 1024);
  gmp_randinit_mt(r_state);

  while(prime == false){
    mpz_urandomb(num1, r_state, 1025);
    while((mpz_cmp(num1, compare)) < 0){
      mpz_urandomb(num1, r_state, 1025);    // Generating random 1024-bit number
    }
    if((even_test(num1)) == true){          // Checking that number is even
      continue;
    }
    if((MR_test(num1, k)) == true){         // Checking that number is prime
      prime = true;
    }
  }

  prime = false;
  
  while(prime == false){
    mpz_urandomb(num2, r_state, 1025);
    while((mpz_cmp(num2, compare)) < 0){
      mpz_urandomb(num2, r_state, 1025);    // Generating random 1024-bit number
    }
    if((even_test(num2)) == true){          // Checking that number is even
      continue;
    }
    if((MR_test(num2, k)) == true){         // Checking that number is prime
      prime = true;
    }
  }
  return;
}

// Tests and returns true if number is even
// num is the number to be tested
bool even_test(mpz_t num){
  mpz_t mod;
  mpz_init(mod);

  mpz_mod_ui(mod, num, 2);
  if((mpz_cmp_ui(mod, 0)) == 0){     // If the number mod 2 == 0, then the number is even, and true is returned
    return(true);
  }
  else{                              // Else, the number is odd, and false is returned
    mpz_clear(mod);
    return(false);
  }
}

// Tests and returns true if number is a probable prime by Miller-Rabin Test
// n is the number to be tested; k determines the accuracy of the test
bool MR_test(mpz_t n, int k){
  int count = 0;
  int s2;
  bool check;
  mpz_t a, t, s, b, temp, num;                                            
  gmp_randstate_t r_state;
  mpz_inits(a, t, s, b, temp, num, NULL);
  mpz_set_ui(s, 0);
  gmp_randinit_mt(r_state);
  
  // Write the number as n = 1 + (2^s)*t by factoring powers of 2 to find s and t; t is odd
  mpz_sub_ui(num, n, 1);             // n - 1
  mpz_mod_ui(temp, num, 2);          // temp = (n - 1) mod 2
  // While loop to find s
  while((mpz_cmp_ui(temp, 0)) == 0){
    mpz_add_ui(s, s, 1);             // s = s + 1 (increment to find the power of 2)
    mpz_div_ui(num, num, 2);         // Divide (n - 1) by 2 to reduce one factor of 2
    mpz_mod_ui(temp, num, 2);
  }
  mpz_set(t, num);                   // t is the odd number left in the num variable
  mpz_sub_ui(num, n, 1);             // n - 1 (for random number range)
  s2 = mpz_get_ui(s);

  // For loop to test primality
  for(int i = 1; i <= k; i++){
    check = false;
    mpz_urandomm(a, r_state, num);   // Generating random integer, a, to test with
    while((mpz_cmp_ui(a, 2)) < 0){   // a must be in the range [2, n - 2]
      mpz_urandomm(a, r_state, num);
    }
    mpz_powm(b, a, t, n);            // b = (a ^ t) mod n
    if(((mpz_cmp_ui(b, 1)) == 0) || ((mpz_cmp(b, num)) == 0)){     // if b = 1 or b = n - 1
      continue;
    }
    for(int j = 1; j < s2; j++){
      mpz_powm_ui(b, b, 2, n);       // b = (b ^ 2) mod n
      if((mpz_cmp(b, num)) == 0){    // if b = n - 1
        check = true;
	break;
      }
      else if((mpz_cmp_ui(b, 1)) == 0){     // if b = 1
        return(false);
      }
    }
    if(check == true){
      continue;
    }
    return(false);
  }
  return(true);
}



  /*if((mpz_probab_prime_p(n, k)) >= 1){
    return(true);
  }
  else if((mpz_probab_prime_p(n, k)) == 0){
    return(false);
  }
  }*/



// Performs modular exponentiation by repeated squaring
// base is the number being raised to an exponent; exp is the exponent; n is the modulus
/*void mod_exp(mpz_t base, mpz_t exp, mpz_t n){
  mpz_t odd_count, num;                     // Counts the number of times the exponent is odd
  mpz_inits(odd_count, num, NULL);
  mpz_set_ui(odd_count, 0);
  mpz_set(num, base);

  // Loop to repeatedly square until the answer
  while((mpz_cmp_ui(exp, 1)) != 0){
    if((even_test(exp)) == true){      // Even branch
      mpz_div_ui(exp, exp, 2);         // Divide exponent by 2
      mpz_powm_ui(base, base, 2, n);   // (Base ^ 2) mod n
    }
    else if((even_test(exp)) == false){   // Odd branch
      mpz_sub_ui(exp, exp, 1);            // Subtract 1 from exponent
      mpz_div_ui(exp, exp, 2);            // Divide exponent by 2
      //mpz_
      mpz_powm_ui(base, base, 2, n);      // (Base ^ 2) mod n
    }
  }

    mpz_mul(base, base, odd_count);
    mpz_mod(base, base, n);
    
    return;
}
*/
#endif
