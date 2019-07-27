#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>

struct sieve_t {
        int n;
        unsigned char* mod1;
	unsigned char* mod5;
};

void init_sieve (struct sieve_t *sv) {

	unsigned i = 0, j = 0, posi = 0, posj = 0;
	sv -> mod1[0] = (sv -> mod1[0]) & ~(1u);

        for(i = 1; i <= (sv -> n); i++) {

		posi = (unsigned) i/8;
		if (8*posi > i) posi = posi - 1;

		for(j = 2; j <= (unsigned) sqrt(6*i + 1) + 1; j++) {
			if ((6*i + 1)%j == 0) (sv -> mod1[posi]) = (sv -> mod1[posi]) | (1u << i%8);
		}
        }

	for(i = 0; i <=  (sv -> n); i++) {

                posi = (unsigned) i/8;
                if (8*posi > i) posi = posi - 1;

                for(j = 2; j <= (unsigned) sqrt(6*i + 5) + 1; j++) {
                        if ((6*i + 5)%j == 0) (sv -> mod5[posi]) = (sv -> mod5[posi]) | (1u << i%8);
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
	int n = 20;
	unsigned char* mod1 = (unsigned char*) calloc((unsigned) n/8 + 7, sizeof(unsigned char));
        unsigned char* mod5 = (unsigned char*) calloc((unsigned) n/8 + 7, sizeof(unsigned char));
        struct sieve_t aratos = {n, mod1, mod5};
	assert((n > 1) && (mod1 != NULL) && (mod5 != NULL));

	init_sieve(&aratos);

        unsigned i = 0, pos = 0;
        for(i = 0; i <= aratos.n; i++) {
                pos = (unsigned) i/8;
                
		if (8*pos > i) pos = pos - 1;
		
#if 0
		if ((aratos.minus1[pos] >> i%8) & 1u == 0u)
               		printf("%d\n",6*i - 1);

		if ((aratos.plus1[pos] >> i&8) & 1u == 0u)
			printf("%d\n", 6*i + 1);
#endif
	printf("%d: %d\n %d:%d\n", 6*i + 1, (aratos.mod1[pos] >> i%8) & 1u, 6*i + 5, (aratos.mod5[pos] >> i%8) & 1u);
	}
        free_sieve(&aratos);

        return 0;
}
