#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>
#include<assert.h>
#include"Rabin_Miller.h"

unsigned long long MAX_NUM = sqrt(ULLONG_MAX) - 2;


/*if mult*mult more MAX_NUM function divide mult on terms by MAX_NUM and then multplies terms*/
unsigned long long pow_mod_exc_mult(unsigned long long mult, unsigned long long mod) {
	unsigned long long k = 0, rem_m = 0, count = 0;
	
	rem_m = mult;
	mult = 0;

	while(rem_m > MAX_NUM) {
		k++;
		rem_m = rem_m - MAX_NUM;
	}

	count = k*k;

	while(count > 0) {
		mult = (mult + (MAX_NUM * MAX_NUM) % mod) % mod;
		count--;
	}

	count = 2*k;

	while(count > 0) {
		count--;	
		mult = (mult + (MAX_NUM * rem_m) % mod) % mod;
	}

	mult = (mult + (rem_m * rem_m) % mod) % mod;
	return mult;
}

/*if prod*mult more MAX_NUM function divide mult and prod on terms by MAX_NUM and then multplies terms*/
unsigned long long pow_mod_exc_prod(unsigned long long mult, unsigned long long prod, unsigned long long mod) {
	
	unsigned long long k1 = 0, k2 = 0, rem_p = 0, rem_m = 0, count = 0;	

	rem_p = prod;
	rem_m = mult;

	if(prod > MAX_NUM) {
		while (rem_p > MAX_NUM) {
			k1++;
			rem_p = rem_p - MAX_NUM;
		}
	}

	if(mult > MAX_NUM) {
		while (rem_m > MAX_NUM) {
			k2++;
			rem_m = rem_m - MAX_NUM;
		}
	}
				
	count = k1*k2;
	prod = 0;

	while (count > 0) {
		prod = (prod + (MAX_NUM * MAX_NUM) % mod) % mod;
		count--;
	}

	count = k1;

	while (count > 0) {
		prod = (prod + (rem_m * MAX_NUM) % mod) % mod;
		count--;
	}

	count = k2;

	while (count > 0) {
		prod = (prod + (rem_p * MAX_NUM) % mod) % mod;
		count--;
	}

	prod = (prod + (rem_p * rem_m) % mod) % mod;
	return prod;
}

unsigned long long mult_mod(unsigned long long mult, unsigned long long m) {
	if(mult != 0 && round((ULLONG_MAX - 1)/mult) < mult) {
		mult = pow_mod_exc_mult(mult, m);
	}

	else mult = (mult * mult) % m;

	return mult;
}

unsigned long long prod_mod(unsigned long long prod, unsigned long long mult, unsigned long long m) {
	if(prod != 0 && round((ULLONG_MAX - 1)/prod) < mult) prod = pow_mod_exc_prod(mult, prod, m);

	else prod = (prod * mult) % m;

	return prod;
}

unsigned long long pow_mod (unsigned long long n, unsigned long long k, unsigned long long m) {
	unsigned long long mult = n % m;
	unsigned long long prod = 1;
	unsigned long long MAX_NUM = sqrt(ULLONG_MAX) - 2;
	while(k > 0) {
		if ((k % 2) == 1) {
			prod = prod_mod(prod, mult, m);
			//printf("mult = %llu  prod = %llu  k = %llu\n", mult, prod, k);
			k--;
		}

		else {
			mult = mult_mod(mult, m);
			//printf("mult = %llu  prod = %llu  k = %llu\n", mult, prod, k);
			k = k/2;
		}
	}
	return prod;

}

int rabin_miller(unsigned long long num, int a_for_test[15], unsigned long long d, int r, int max_idx) {
	int i = 0, code_cyc = 0;
	unsigned long long x = 0, j = 0;


	for(i = 0; i <= max_idx; i++) {

		if(num == a_for_test[i]){
			return 1;
		}
		
		code_cyc = 0;
		x = pow_mod(a_for_test[i], d, num);
		if((x == 1) || x == num - 1) 
			continue;
		
		for (j = 0; j < r-1; j++) {
			x = pow_mod(x, 2, num);
			if(x == num - 1) {
				code_cyc = 1;
				break;
			}
		}

		if(code_cyc == 1) 
			continue;
		
		return 0;		
	}

	return 1;
}

int is_prime(unsigned long long num) {
	int r = 0, code_cyc = 0;
	unsigned long long d = 0, i = 0, x = 0, j = 0;
	int a_for_test[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 61, 73, 1662803};
	
	if(num == 2 || num == 3) return 1;

	if(num < 2) return 0;

	if((num % 2 == 0) || (num % 3 == 0) || (num % 5 == 0)) return 0;

	for (i = num  - 1; i > 1; i = i/2) {
		if(i % 2 != 0) 
			break;
		r++;
	}

	d = (num - 1) / pow(2, r);

	if(num < 4759123141) {
		a_for_test[1] = 7;
		a_for_test[2] = 61;

		return rabin_miller(num, a_for_test, d, r, 2);
	}

	if(num >= 4759123141 && num < 3474749660383) {
		return rabin_miller(num, a_for_test, d, r, 5);
	}

	if(num >= 3474749660383 && num < 3825123056546413051) {
		return rabin_miller(num, a_for_test, d, r, 8);
	}

	//printf("r = %d   d = %llu\n", r, d);
	
	if(num >= 3825123056546413051) {
		return rabin_miller(num, a_for_test, d, r, 11);
	}
}


#if 0 
int main() {
	unsigned long long p = 0, code_input = 0;
	code_input = scanf("%llu", &p);
	assert(code_input == 1);
	if(is_prime(p) == 1) printf("Num is simple\n");\
	else printf("Num is composite\n");
	return 0;
}
#endif
