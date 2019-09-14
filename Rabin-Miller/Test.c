#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include"Sieve.h"
#include"Rabin_Miller.h"

int main() {
	unsigned long long p = 0, size = 0, i = 0;
	unsigned long long const up_bound = 10000000;
	int sv_check = 0, rb_check = 0;
	clock_t start, end;
	
	
	size = (unsigned long long) up_bound/(CHAR_BIT*6);
	unsigned char* mod1 = (unsigned char*) calloc (size + 2, sizeof(unsigned long long));
	unsigned char* mod5 = (unsigned char*) calloc (size + 2, sizeof(unsigned long long));
	struct sieve_t sv = {size + 1, mod1, mod5};
	
	assert((size >= 0) && (mod1 != NULL) && (mod5 != NULL));
	
	fill_sieve(&sv);

	start = clock();

	for(i = 2; i <= up_bound; i++) {
		sv_check = is_prime_sv(&sv, i);
		rb_check = is_prime(i);
		if(sv_check != rb_check) {
			printf("ERROR!!!!  number = %llu\trb_check = %d\tsv_check = %d\n", i, rb_check, sv_check);
		}
	}

	end = clock();

	printf("time = %fmks\n", (double) end - start);

	return 0;
}
