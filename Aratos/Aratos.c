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
	int n = 0, count = 0, simpnum = 0;
	const int SIMPLE_PER_NUM = 20;
	printf("Enter the number of needed prime ");
	scanf("%d", &n);
	struct sieve_t aratos = init_sieve(SIMPLE_PER_NUM*n);
	int i = 0;
	for(i = 0; i <= aratos.size - 1; i++) {
		if(aratos.sieve[i] == 0) count++;
		if (count == n){
			simpnum = i;
			break;
		}	
	}

	printf("\n%d-th simple number is %d\n", n, simpnum);
	free_sieve(&aratos);

	return 0;
}
