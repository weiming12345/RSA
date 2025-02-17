#pragma once
#ifndef RSA_H
#define RSA_H
#include <stdio.h>
#include <gmp.h>
#include <time.h>

class RSA
{
public:
	mpz_t p, q, n, phi, e, d;
public:
	RSA();
	RSA(int bits);
	RSA(mpz_t n, mpz_t e, mpz_t d);
	~RSA();
	void getKeys(mpz_t n, mpz_t e, mpz_t d) const;
	void getKeys(RSA* rsa);
	void encrypt(mpz_t res, mpz_t m);
	void decrypt(mpz_t res, mpz_t c);
};
#endif // !



