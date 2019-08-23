#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>

unsigned long long pow_mod_exc_mult(unsigned long long mult, unsigned long long mod, unsigned long long MAX_NUM) {
	unsigned long long k = 0, rem_m = 0, count = 0;
	
	//printf("ddddddddd\n");
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


unsigned long long pow_mod_exc_prod(unsigned long long mult, unsigned long long prod, unsigned long long mod, unsigned long long MAX_NUM) {
	
	unsigned long long k1 = 0, k2 = 0, rem_p = 0, rem_m = 0, count = 0;	

	rem_p = prod;
	rem_m = mult;

	//printf("cccccccc\n");

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

unsigned long long pow_mod (unsigned long long n, unsigned long long k, unsigned long long m) {
	unsigned long long mult = n % m;
	unsigned long long prod = 1;
	unsigned long long MAX_NUM = sqrt(ULLONG_MAX) - 2;
	while(k > 0) {
		//printf("bbbbbbb\n");
		if ((k % 2) == 1) {
			if (prod != 0 && round((ULLONG_MAX - 1)/prod) < mult) {
				prod = pow_mod_exc_prod(mult, prod, m, MAX_NUM);
			}

			else {
				//printf("ggggggggggg\n");
				prod = (prod * mult) % m;
			}

			//printf("mult = %llu  prod = %llu  k = %llu\n", mult, prod, k);
			k--;
		}

		else {

			if(mult != 0 && round((ULLONG_MAX - 1)/mult) < mult) {

				mult = pow_mod_exc_mult(mult, m, MAX_NUM);
			}

			else {
				//printf("hhhhhhhhhhhh\n");
				mult = (mult * mult) % m;
			}
			
			//printf("mult = %llu  prod = %llu  k = %llu\n", mult, prod, k);
			k = k/2;
		}
	}
	return prod;

}

int is_prime(unsigned long long num) {
	int r = 0, code_cyc = 0;
	unsigned long long d = 0, i = 0, limit = 0, x = 0, j = 0;
	double dlimit = 0;

	if(num % 2 == 0)
		return 0;

	for (i = num  - 1; i > 1; i = i/2) {
		if(i % 2 != 0) 
			break;
		r++;
	}

	d = (num - 1) / pow(2, r);

	//printf("r = %d   d = %llu\n", r, d);

	dlimit = 2*log(num)*log(num);
	limit = round(dlimit);
	if (dlimit < limit) 
		limit = limit - 1;

	if(limit > num - 2)
		limit = num - 2;

	for(i = 2; i <= limit; i++) {
		code_cyc = 0;
		x = pow_mod(i, d, num);
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



int main() {
	unsigned long long p = 0;
	scanf("%llu", &p);
	if(is_prime(p) == 1) printf("Num is simple\n");\
	else printf("Num is composite\n");
	return 0;
}
