struct sieve_t {
	unsigned long long n;
	unsigned char *mod1;
	unsigned char *mod5;
};

void sieve_set_bit(struct sieve_t* sv, unsigned long long j);
void fill_sieve(struct sieve_t * sv);
int is_prime_sv(struct sieve_t * sv, unsigned n);
unsigned long long sieve_size(unsigned long long n);
void free_sieve(struct sieve_t * s);
