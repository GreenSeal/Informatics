#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"Euler.h"

int main() {
	struct sieve_t aratos = init_sieve(500000);
	int i = 0, a = 0, b = 0, n = 0, count = 0, max = 0, maxa = -1000, maxb = 0;

	for(b = 0; b <= 1000; b++) {

		if(aratos.sieve[b] == 1) continue;

		else {
			for(a = -1000; a <= 1000; a++) {
				for(n = 0; n <= 100; n++) {
					
					if((n*n + a*n + b) <= 1) break;

					if(aratos.sieve[n*n + a*n + b] == 0) count++;
					else break;
				}
				
				if(count > max) {
					max = count;
					maxa = a;
					maxb = b;
				}
				count = 0;
			}
		}
	}

	printf ("%d: n*n + (%d*n) + (%d)\n", max, maxa, maxb);

	for(i = 0; i <= max - 1; i++) {
		printf("%d\n", i*i + maxa*i + maxb);
	}
	
	free_sieve(&aratos);		
	return 0;
}

