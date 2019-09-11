#pragma once

#include<math.h>
#include<limits.h>

extern unsigned long long MAX_NUM;

int is_prime(unsigned long long num);
unsigned long long pow_mod(unsigned long long n, unsigned long long k, unsigned long long m);
unsigned long long pow_mod_exc_prod(unsigned long long mult, unsigned long long prod, unsigned long long mod);
unsigned long long pow_mod_exc_mult(unsigned long long mult, unsigned long long mod);
