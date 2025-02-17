#include <stdio.h>
#include "RSA.h"

int main() {

	RSA rsa(1024);
	mpz_t m, c;
	mpz_inits(m, c, NULL);
	mpz_set_ui(m, 19);

	rsa.encrypt(c, m);
	gmp_printf("c = %Zd\n", c);

	rsa.decrypt(m, c);
	gmp_printf("m = %Zd\n", m);

	RSA rsa2;
	rsa.getKeys(&rsa2);

	rsa2.encrypt(c, m);
	gmp_printf("c = %Zd\n", c);

	rsa2.decrypt(m, c);
	gmp_printf("m = %Zd\n", m);


	return 0;
}