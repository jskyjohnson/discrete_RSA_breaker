

#include <gmp.h>
#include <stdio.h>
#include <assert.h>

using namespace std;
void brutefactor(mpz_t n, mpz_t k);
int main(){

  char inputStr[1024];
  /*
     mpz_t is the type defined for GMP integers.
     It is a pointer to the internals of the GMP integer data structure
   */
  mpz_t n;
  int flag;

  printf ("Enter your number: ");
  scanf("%1023s" , inputStr); /* NOTE: never every write a call scanf ("%s", inputStr);
                                  You are leaving a security hole in your code. */

  /* 1. Initialize the number */
  mpz_init(n);
  mpz_set_ui(n,0);

  /* 2. Parse the input string as a base 10 number */
  flag = mpz_set_str(n,inputStr, 10);
  assert (flag == 0); /* If flag is not 0 then the operation failed */

  /* Print n */
  printf ("n = ");
  mpz_out_str(stdout,10,n);
  printf ("\n");

  mpz_t  k;
  mpz_init(k);
  mpz_set_ui(k,0);

  brutefactor(n, k);
  printf("First Prime Factor = ");
  mpz_out_str(stdout, 10, k);
  printf("\n");
  //mpz_out_str(stdout, 10, n);;


  /* 6. Clean up the mpz_t handles or else we will leak memory */
  mpz_clear(n);
  mpz_clear(k);
}
void brutefactor(mpz_t n, mpz_t k){
  mpz_t n_sqrt;
  mpz_init(n_sqrt);
  mpz_set_ui(n_sqrt, 0);
  mpz_sqrt(n_sqrt, n);
  
  mpz_t index;
  mpz_init(index);
  mpz_set_ui(index, 2);
  
  mpz_t modval;
  mpz_init(modval);
  mpz_set_ui(modval, 100);

  bool looping = true;
  while(mpz_cmp(index, n_sqrt) < 0 && looping){
    
    mpz_mod(modval, n, index);
    if(mpz_cmp_si(modval, 0) == 0) {
      mpz_set(k, index);
      looping = false;
    }
    mpz_add_ui(index, index, 1);
  }
}
