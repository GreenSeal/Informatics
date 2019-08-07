#pragma once

struct sieve_t {
	unsigned size;
	unsigned char* sieve;
};

struct sieve_t init_sieve(unsigned n);
void free_sieve(struct sieve_t* s);
int NumDig (int num);
