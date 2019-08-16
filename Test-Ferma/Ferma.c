#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

unsigned long long pow_mod (unsigned long long n, unsigned long long k, unsigned long long m) {
	unsigned long long mult = n % m;
	unsigned long long prod = 1;
	unsigned long long k1 = 0, rem_p = 0, k2 = 0, rem_m = 0, count = 0;
	unsigned long long MAX_NUM = 2000000000;
	while(k > 0) {
		k1 = 0;
		k2 = 0;

		if ((k % 2) == 1) {
			if (prod > MAX_NUM || mult > MAX_NUM) {
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
					prod = (prod + (MAX_NUM * MAX_NUM) % m) % m;
					count--;
				}

				count = k1;

				while (count > 0) {
					prod = (prod + (rem_m * MAX_NUM) % m) % m;
					count--;
				}

				count = k2;

				while (count > 0) {
					prod = (prod + (rem_p * MAX_NUM) % m) % m;
					count--;
				}

				prod = (prod + (rem_p * rem_m) % m) % m;
			}

			else {
				prod = (prod * mult) % m;
			}

			//printf("mult = %llu  prod = %llu  k = %llu\n", mult, prod, k);
			k--;
		}

		else {

			if(mult > MAX_NUM) {
				rem_m = mult;
				mult = 0;

				while(rem_m > MAX_NUM) {
					k2++;
					rem_m = rem_m - MAX_NUM;
				}

				count = k2*k2;

				while(count > 0) {
					mult = (mult + (MAX_NUM * MAX_NUM) % m) % m;
					count--;
				}

				count = 2*k2;

				while(count > 0) {
					count--;	
					mult = (mult + (MAX_NUM * rem_m) % m) % m;
				}

				mult = (mult + (rem_m * rem_m) % m) % m;
			}

			else {
				mult = (mult * mult) % m;
			}
			
			//printf("mult = %llu  prod = %llu  k = %llu\n", mult, prod, k);
			k = k/2;
		}
	}
	return prod;

}



int main() {
	unsigned long long a = 0, p = 0, powmod = 0;
	int i = 0, res = 1;
	srand(time(NULL));
	
	scanf("%llu", &p);
	
	for(i = 0; i <= 25; i++) {
		a = rand() % 1000 + 1;
		if (a % p == 0) {
			i--;
			continue;
		}
		powmod = pow_mod(a, p - 1, p);
		//printf("a = %llu   powmod = %llu\n", a, powmod);
		if((powmod) != 1) res = 0;
	}

	printf("%d\n", res);


	return 0;
}
