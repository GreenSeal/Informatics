int is_prime(struct sieve_t* sv, unsigned n/*, int* mode_code*/) {
	unsigned long long posi = 0;

	if((n - 1) % 6 == 0) {

		posi = (unsigned long long) (n-1)/(6*CHAR_BIT);
		if(n < (6*CHAR_BIT*posi + 1)) 
			posi = posi - 1;
		
		return ((sv -> mod1[posi] >> ((n-1)/6) % CHAR_BIT) & 1u);
	}
	

	
	if((n - 5) % 6 == 0) {

		posi = (unsigned long long) (n - 5)/(6*CHAR_BIT);
		if(n < (6*CHAR_BIT*posi + 5)) 
			posi = posi - 1;

		return ((sv -> mod5[posi] >> ((n-5)/6) % CHAR_BIT) & 1u);
	}

	else 
		return 1;
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

		if(!is_prime(sv, i)) {

			for(j = 2*i; j <= 6*CHAR_BIT*(sv -> n) + 5; j += i) {
				sieve_set_bit(sv, j);
			}
		}
	}
}
