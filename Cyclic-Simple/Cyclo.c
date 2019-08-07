#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"Cyclo.h"

int NumDig(int num) {
	int i = 0, j = 1, dig = 0;

	for(i = 10, j = 1;; i = 10*i, j++) {
		if (num%i == num) {
			dig = j;
			break;
		}
	}

	return dig;
}

int CycloBust(int dig, int num, struct sieve_t aratos){
	int i = 0, j = 0, rem = 0, cyclo = 0, buf = 0;

	int* figs = (int*) calloc (dig, sizeof(int));

	for(i = 0; i <= dig - 1; i++){

		figs[i] = (num % ((int) pow(10, i+1)) - rem) / ((int) pow(10, i));
		rem = num % ((int) pow(10, i+1));
		if (figs[i] == 0) return 0;
	}

	for(j = 0; j <= dig - 1; j++){
		cyclo = 0;
		buf = figs[0];

		for(i = 0; i <= dig - 2; i++){
			figs[i] = figs[i+1];
		}

		figs[dig - 1] = buf;
		
		for(i = 0; i <= dig - 1; i++){
			cyclo = cyclo + figs[i] * pow(10,i);
		}
		
		if(aratos.sieve[cyclo] == 1) return 0;
	}

	free(figs);

	return num;
}





int main() {
	int i = 0, num = 200000, mb1 = num, mb2 = num, dig = 0, res = 0;

	struct sieve_t aratos = init_sieve(20*num);

	for (i = 0; i <= num - 1; i++){

		if(aratos.sieve[mb1] == 0){
			dig = NumDig(mb1);
			res = CycloBust(dig, mb1, aratos);
			if (res != 0) break;

		}

		if(aratos.sieve[mb2] == 0){
			dig = NumDig(mb2);
			res = CycloBust(dig, mb2, aratos);
			if (res != 0) break;			
		}

		mb1++;
		mb2--;
	}

	printf("Nearest circular simple num is %d\n", res);
	
	return 0;
}
