#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>

struct sieve_t {
	unsigned size;
	unsigned char* sieve;
};

struct sieve_t init_sieve (unsigned n) {
	unsigned char* sieve = (unsigned char*) calloc(n, sizeof(unsigned char));
	struct sieve_t res = {n, sieve};
	assert((n > 1) && (sieve != NULL));

	unsigned r = (unsigned) sqrt(n) + 1;
	res.sieve[0] = res.sieve[1] = 1;

	int i = 0, j = 0;

	for(i = 2; i <= r; i ++) {
		if (sieve[i] == 0) {
			for(j = 2*i ;j <= n ;j += i){
				sieve[j] = 1;
			}
		}
	}

	return res;
}

void free_sieve(struct sieve_t* s) {
	free(s -> sieve);
	s -> sieve = NULL;
	s -> size = 0;
}

int main() {
	struct sieve_t aratos = init_sieve(100);
	int i = 0;
	for(i = 0; i <= aratos.size; i++) {
		printf("%d\n", aratos.sieve[i]);
	}
	free_sieve(&aratos);

	return 0;
}
