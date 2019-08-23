#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>
#include<time.h>

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
	unsigned long long a = 0, powmod = 0;
	int i = 0, res = 1;
	srand(time(NULL));
	if(num == 0) 
		return 0;
	if(num == 1) 
		return 0;

	if(num % 2 == 0) 
		return 0;

	if(num % 3 == 0)
		return 0;

	if(num % 5 == 0) 
		return 0;	
	
	for(i = 0; i <= 25; i++) {
		//printf("eeeeeeee\n");
		a = rand() % 1000 + 1;
		if (a % num == 0) {
			i--;
			continue;
		}
		//printf("a = %llu   powmod = %llu\n", a, powmod);
		powmod = pow_mod(a, num - 1, num);
		if((powmod) != 1) {
			res = 0;
			break;
		}
	}

	return res;
}

unsigned long long fiblike_check(unsigned long long num, int k, int n) {
	unsigned long long first = 0ull, second = 1ull, buf = 0, max = 0;
	if(num == 0) 
		return 0ull;
	if(num == 1) 
		return 1ull;

	while(second < num) {
		buf = second;
		second = k*second + n*first;
		first = buf;
		/*if(idx%1000 == 0)*/ printf("idx = %llu\n", second);
		if(is_prime(second) == 1) 
			max = second;
	}

	return max;
}

int main() {
	int n = 0, k = 0;
	unsigned long long max = 0;
	scanf("%d %d", &k, &n);
	max = fiblike_check(round(pow(2, 60)) - 1, k, n);
	printf("%llu\n", max);
}
