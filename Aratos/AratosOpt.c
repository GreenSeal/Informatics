#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>
#include<limits.h>

struct sieve_t {
        unsigned long long n;
        unsigned char* mod1;
	unsigned char* mod5;
};

int sieve_get_bit(unsigned long long num, const struct sieve_t aratos/*, int* mode_code*/) {
	unsigned long long posi = 0;

	if((num - 1)%6 == 0) {

		posi = (unsigned long long) (num-1)/(6*CHAR_BIT);
		if(num < (6*CHAR_BIT*posi + 1)) posi = posi - 1;
	
		return !((aratos.mod1[posi] >> ((num-1)/6)%CHAR_BIT) & 1u);
	}
	

	
	if((num - 5)%6 == 0) {

		posi = (unsigned long long) (num - 5)/(6*CHAR_BIT);
		if(num < (6*CHAR_BIT*posi + 5)) posi = posi - 1;

		return !((aratos.mod5[posi] >> ((num-5)/6)%CHAR_BIT) & 1u);
	}

	else return 0;
}

void sieve_set_bit(struct sieve_t* sv, unsigned long long j){
	unsigned long long posj = 0;
	
	if((j - 1)%6 == 0) {
        	posj = (unsigned long long) (j-1)/(6*CHAR_BIT);
                if((posj*6*CHAR_BIT + 1) > j) posj = posj - 1;

                sv -> mod1[posj] = (sv -> mod1[posj]) | (1u << ((j-1)/6)%CHAR_BIT);
	}

        if((j - 5)%6 == 0) {
                posj = (unsigned long long) (j-5)/(6*CHAR_BIT);
                if((posj*6*CHAR_BIT + 5) > j) posj = posj - 1;

                sv -> mod5[posj] = (sv -> mod5[posj]) | (1u << ((j-5)/6)%CHAR_BIT);
        }

}

void init_sieve (struct sieve_t *sv) {

	unsigned long long i = 0, j = 0, posi = 0, posj = 0, r = sqrt(sv -> n) + 1, mode_code = 0;
	sv -> mod1[0] = (sv -> mod1[0]) | 1u;

        for(i = 0; 6*i <= r; i++) {

		//if((r >= 1000) && (i%(unsigned long long)(r/100) == 0)) printf("\nprogress:%llu", i*100/r);

		if(sieve_get_bit(6*i + 1, *sv)) {

			for(j = 2*(6*i + 1); j <= (sv -> n) - 1; j += (6*i + 1)) {
				sieve_set_bit(sv, j);
			}
		}

		if(sieve_get_bit(6*i + 5, *sv)) {
			
			for(j = 2*(6*i + 5); j <= (sv -> n) - 1; j += (6*i + 5)) {
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

int main() {
	unsigned long long n = 0, count = 2, simpnum = 0, size = 0;
	printf("Enter the number of needed prime ");
	scanf("%llu", &n);
	size = sieve_size(n);
	//printf("size: %llu\n", size);
	unsigned char* mod1 = (unsigned char*) calloc((unsigned long long) size/48 + 2, sizeof(unsigned char));
        unsigned char* mod5 = (unsigned char*) calloc((unsigned long long) size/48 + 2, sizeof(unsigned char));
        struct sieve_t aratos = {size, mod1, mod5};

	assert((size > 1) && (mod1 != NULL) && (mod5 != NULL));

	init_sieve(&aratos);

        unsigned long long i = 0, pos = 0;
        for(i = 0; i <= size - 1; i++) {
                
		if (sieve_get_bit(i, aratos)) count++;
		
		if(count == n) {
			simpnum = i;
			break;
		}
		
		//if(count % 10000000 == 0) printf("\ncount:%llu", count);
	}

	printf("\n%llu-th simple number is %llu\n", n, simpnum);
	free_sieve(&aratos);

        return 0;
}
