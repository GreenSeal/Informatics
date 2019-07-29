#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>
#include<limits.h>

struct sieve_t {
        unsigned size;
        unsigned char* sieve;
};

int sieve_get_bit(int index, const struct sieve_t aratos) {
	unsigned posi = 0;
	posi = (unsigned) index/8;
	if(index < CHAR_BIT*posi) posi = posi - 1;
	return ((aratos.sieve[posi] >> index%CHAR_BIT) & 1u); 
}

struct sieve_t init_sieve (unsigned n) {
        unsigned char* sieve = (unsigned char*) calloc((unsigned) n/CHAR_BIT + CHAR_BIT - 1, sizeof(unsigned char));
        struct sieve_t res = {n, sieve};
        assert((n > 1) && (sieve != NULL));

        unsigned r = (unsigned) sqrt(n) + 1;
        res.sieve[0] = res.sieve[0] | 1u;
	res.sieve[0] = res.sieve[0] | (1u << 1);

        unsigned i = 0, j = 0, posi = 0, posj = 0;

        for(i = 2; i <= r; i ++) {

                if (!sieve_get_bit(i, res)) {
                        for(j = 2*i ;j <= n - 1 ;j += i) {
				posj = (unsigned) j/CHAR_BIT;
				if(j < CHAR_BIT*posj) posj = posj - 1;

				res.sieve[posj] = res.sieve[posj] | (1u << j%CHAR_BIT);
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
	int n = 0, count  = 0, simpnum = 0;
	const int SIMPLE_PER_NUM = 26;
	printf("Enter the number of needed prime ");
	scanf("%d", &n);
        struct sieve_t aratos = init_sieve(SIMPLE_PER_NUM*n);
	unsigned i = 0, pos = 0;
        for(i = 0; i <= aratos.size - 1; i++) {
		
		if(!sieve_get_bit(i, aratos)) count++;
		if(count == n) {
			simpnum = i;
			break;
		}
        }

	printf("\n%d-th simple number is %d\n", n, simpnum);
        free_sieve(&aratos);

        return 0;
}
