#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>
#include<limits.h>

struct sieve_t {
        int n;
        unsigned char* mod1;
	unsigned char* mod5;
};

int sieve_get_bit(int index, const unsigned char* sieve) {
	unsigned posi = 0;
	posi = (unsigned) index/8;
	if(index < CHAR_BIT*posi) posi = posi - 1;
	return ((sieve[posi] >> index%CHAR_BIT) & 1u);
}

void init_sieve (struct sieve_t *sv) {

	unsigned i = 0, j = 0, posi = 0, posj = 0;
	sv -> mod1[0] = (sv -> mod1[0]) | 1u;

        for(i = 1; i <= (sv -> n) - 1; i++) {

		posi = (unsigned) i/CHAR_BIT;
		if (CHAR_BIT*posi > i) posi = posi - 1;

		for(j = 2; j <= (unsigned) sqrt(6*i + 1) + 1; j++) {
			if ((6*i + 1)%j == 0) (sv -> mod1[posi]) = (sv -> mod1[posi]) | (1u << i%CHAR_BIT);
		}
        }

	for(i = 0; i <=  (sv -> n); i++) {

                posi = (unsigned) i/CHAR_BIT;
                if (CHAR_BIT*posi > i) posi = posi - 1;

                for(j = 2; j <= (unsigned) sqrt(6*i + 5) + 1; j++) {
                        if ((6*i + 5)%j == 0) (sv -> mod5[posi]) = (sv -> mod5[posi]) | (1u << i%CHAR_BIT);
                }
        }
}

void free_sieve(struct sieve_t* s) {
        free(s -> mod1);
	free(s -> mod5);
        s -> mod1 = NULL;
	s -> mod5 = NULL;
        s -> n = 0;
}

int main() {
	int n = 0, count = 2, simpnum = 0, size = 0;
	const int SIMPLE_PER_NUM = 10;
	printf("Enter the number of needed prime ");
	scanf("%d", &n);
	size = SIMPLE_PER_NUM*n;
	unsigned char* mod1 = (unsigned char*) calloc((unsigned) size/8 + 1, sizeof(unsigned char));
        unsigned char* mod5 = (unsigned char*) calloc((unsigned) size/8 + 1, sizeof(unsigned char));
        struct sieve_t aratos = {size, mod1, mod5};
	assert((size > 1) && (mod1 != NULL) && (mod5 != NULL));

	init_sieve(&aratos);

        unsigned i = 0, pos = 0;
        for(i = 0; i <= size - 1; i++) {
                
		if (!sieve_get_bit(i, aratos.mod1)) count++;
		
		if(count == n) {
			simpnum = 6*i+1;
			break;
		}
		
		if (!sieve_get_bit(i, aratos.mod5)) count++;

		if (count == n) {
			simpnum = 6*i+5;
			break;
		}

		//printf("\ncount:%d", count);
	}

	printf("\n%d-th simple number is %d\n", n, simpnum);
	free_sieve(&aratos);

        return 0;
}
