#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>

struct sieve_t {
        unsigned size;
        unsigned char* sieve;
};

struct sieve_t init_sieve (unsigned n) {
        unsigned char* sieve = (unsigned char*) calloc((unsigned) n/8 + 7, sizeof(unsigned char));
        struct sieve_t res = {n, sieve};
        assert((n > 1) && (sieve != NULL));

        unsigned r = (unsigned) sqrt(n) + 1;
        res.sieve[0] = res.sieve[0] | 1u;
	res.sieve[0] = res.sieve[0] | (1u << 1);

        unsigned i = 0, j = 0, posi = 0, posj = 0;

        for(i = 2; i <= r; i ++) {
		posi = (unsigned) i/8;
		if(i < 8*posi)	posi = posi - 1;


                if (((res.sieve[posi] >> i%8) & 1u) == 0) {
                        for(j = 2*i ;j <= n ;j += i) {
				posj = (unsigned) j/8;
				if(j < 8*posj) posj = posj - 1;

				res.sieve[posj] = res.sieve[posj] | (1u << j%8);
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
        unsigned i = 0, pos = 0;
        for(i = 0; i <= aratos.size; i++) {
		pos = (unsigned) i/8;
		if (8*pos > i) pos = pos - 1;

                printf("%d\n", (aratos.sieve[pos] >> i%8) & 1u);
        }
        free_sieve(&aratos);

        return 0;
}
