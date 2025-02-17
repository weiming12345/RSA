#include "RSA.h"
RSA::RSA()
{
	/*只初始化各种变量*/
	mpz_inits(this->p, this->q, this->n, this->phi, this->e, this->d, NULL);
}

RSA::RSA(int bits)
{
	mpz_inits(this->p, this->q, this->n, this->phi, this->e, this->d, NULL);
	/*生成两个大素数 p 和 q*/
	clock_t seed = time(NULL);

	gmp_randstate_t state;
	gmp_randinit_default(state);
	gmp_randseed_ui(state, seed);

	mpz_urandomb(this->p, state, (bits - 1) / 2);
	mpz_nextprime(this->p, this->p);

	mpz_urandomb(this->q, state, (bits + 1) / 2);
	mpz_nextprime(this->q, this->q);

	/*计算 n = p * q*/
	mpz_mul(this->n, this->p, this->q);

	/*计算 φ(n) = (p - 1) * (q - 1)*/
	mpz_t temp_p, temp_q;
	mpz_inits(temp_p, temp_q, NULL);
	mpz_sub_ui(temp_p, this->p, 1);
	mpz_sub_ui(temp_q, this->q, 1);
	mpz_mul(this->phi, temp_p, temp_q);

	/*选择一个 e，条件是 1 < e < φ(n)，且 e 与 φ(n) 互质*/
	mpz_set_ui(this->e, 65537);

	/*计算 d，使得 d * e ≡ 1 (mod φ(n))*/
	mpz_invert(this->d, this->e, this->phi);

	gmp_randclear(state);
}

RSA::RSA(mpz_t n, mpz_t e, mpz_t d)
{
	/*根据n, e, d的值生成密钥*/
	mpz_inits(this->p, this->q, this->n, this->phi, this->e, this->d, NULL);
	mpz_set(this->n, n);
	mpz_set(this->e, e);
	mpz_set(this->d, d);
}

RSA::~RSA()
{
	mpz_clears(this->p, this->q, this->n, this->phi, this->e, this->d, NULL);
}

void RSA::getKeys(mpz_t n, mpz_t e, mpz_t d) const
{
	mpz_set(n, this->n);
	mpz_set(e, this->e);
	mpz_set(d, this->d);
}

void RSA::getKeys(RSA* rsa)
{
	RSA::getKeys(rsa->n, rsa->e, rsa->d);
}

void RSA::encrypt(mpz_t res, mpz_t m)
{
	mpz_powm(res, m, this->e, this->n);
}

void RSA::decrypt(mpz_t res, mpz_t c)
{
	mpz_powm(res, c, this->d, this->n);
}
