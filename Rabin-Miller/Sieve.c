#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>
#include<assert.h>
#include"Sieve.h"

int is_prime_sv(struct sieve_t* sv, unsigned n/*, int* mode_code*/) {
	unsigned long long posi = 0;

	
	if((n == 2) || (n == 3)) return 1;

	
	if((n < 2) || (n % 2 == 0) || (n % 3 == 0) || (n % 5) == 0) return 0;
	

	if((n - 1) % 6 == 0) {

		posi = (unsigned long long) (n-1)/(6*CHAR_BIT);
		if(n < (6*CHAR_BIT*posi + 1)) 
			posi = posi - 1;
		
		return (!((sv -> mod1[posi] >> ((n-1)/6) % CHAR_BIT) & 1u));
	}
	

	
	if((n - 5) % 6 == 0) {

		posi = (unsigned long long) (n - 5)/(6*CHAR_BIT);
		if(n < (6*CHAR_BIT*posi + 5)) 
			posi = posi - 1;

		return (!((sv -> mod5[posi] >> ((n-5)/6) % CHAR_BIT) & 1u));
	}

	else 
		return 0;
}

void sieve_set_bit(struct sieve_t* sv, unsigned long long j) {
	unsigned long long posj = 0;

	if((j - 1) % 6 == 0) {
		posj = (unsigned long long) (j-1)/(6*CHAR_BIT);
		if((posj*6*CHAR_BIT + 1) > j) 
			posj = posj - 1;

		sv -> mod1[posj] = (sv -> mod1[posj]) | (1u << ((j-1)/6) % CHAR_BIT);
	}

	if((j - 5) % 6 == 0) {
		posj = (unsigned long long) (j-5)/(6*CHAR_BIT);
		if((posj*6*CHAR_BIT + 5) > j) 
			posj = posj - 1;

		sv -> mod5[posj] = (sv -> mod5[posj]) | (1u << ((j-5)/6) % CHAR_BIT);
	}

}

void fill_sieve (struct sieve_t *sv) {

	unsigned long long i = 0, j = 0, posi = 0, posj = 0, r = sqrt(6*CHAR_BIT*(sv -> n) + 5) + 1, mode_code = 0;
	sv -> mod1[0] = (sv -> mod1[0]) | 1u;

	for(i = 1; i <= r; i++) {

		//if((r >= 1000) && (i%(unsigned long long)(r/100) == 0)) printf("\nprogress:%llu", i*100/r);

		if(is_prime_sv(sv, i)) {

			for(j = 2*i; j <= 6*CHAR_BIT*(sv -> n) + 5; j += i) {
				sieve_set_bit(sv, j);
			}
		}
	}
}

unsigned long long sieve_size(unsigned long long n) {
	
	if(n > 30) {
		float dnum = n;
		float dres = dnum*(log(dnum) + log(log(dnum)));
		//printf("%f\n", dres);
		return (unsigned long long) dres;
	}

	else return 300;
}

void free_sieve(struct sieve_t* s) {
        free(s -> mod1);
	free(s -> mod5);
        s -> mod1 = NULL;
	s -> mod5 = NULL;
        s -> n = 0;
}


#if 0
int main() {
	unsigned long long p = 0, size = 0;
	printf("Enter number: ");
	scanf("%llu", &p);
	if((p == 2) || (p == 3)) {
		printf("\nNumber is simple\n");
		return 0;
	}
	
	if((p < 2) || (p % 2 == 0) || (p % 3 == 0) || (p % 5) == 0) {
		printf("\nNumber is composite\n");
		return 0;
	}

	size = (unsigned long long) p/(CHAR_BIT*6);
	unsigned char* mod1 = (unsigned char*) calloc (size + 2, sizeof(unsigned long long));
	unsigned char* mod5 = (unsigned char*) calloc (size + 2, sizeof(unsigned long long));
	struct sieve_t sv = {size + 1, mod1, mod5};
	
	assert((size >= 0) && (mod1 != NULL) && (mod5 != NULL));
	
	fill_sieve(&sv);

	if(is_prime_sv(&sv, p)) printf("\nNumber is simple\n");
	
	if(!is_prime_sv(&sv, p)) printf("\nNumber is composite\n");

	return 0;
}
#endif
