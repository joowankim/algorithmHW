#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*
 * When I create two large prime number for making n, m,
 * It unvoked error. Because they are too large to compute with them.
 * So, I guess that the bits of them is cutted by computer.
 * Therefore, I limit the range of the two random prime numbers (P, Q.)
 * So, it would be limited to entered messages' the number of digits.
 * Maybe, to 3 digits is safe and from 4 digits would be a little dangerous 
 */

int Euclid(int a, int b);
int * Extended_Euclid(int a, int b);
int mod_exp(int a, int b, int n);
int isPrime(int n);
int RSAencryption(int M, int e, int n);
int RSAdecryption(int C, int d, int n);
void createRand(int * n, int * m);
int publicKey(int m);
int privateKey(int m, int e);

void main()
{
	int n, m;	//prime numbers' multi, pi(n)
	int d, e;	//private key, public key
	int M, C;	//original message, encrpyted message

	//create random number n, m
	createRand(&n, &m);

	//create public key with m
	e = publicKey(m);
	//create private key with m, e
	d = privateKey(m, e);

	//enter the original message
	printf("enter the message : ");
	scanf("%d", &M);

	//encrypte the message
	C = RSAencryption(M, e, n);

	//decrypte message
	M = RSAdecryption(C, d, n);

	//print the original message
	printf("%d \n", M);
}

int Euclid(int a, int b)
{
	if (b == 0)
		return a;
	else
		return Euclid(b, a%b);
}

int * Extended_Euclid(int a, int b)
{
	int out[3];
	int *g;
	if (b == 0)
	{
		out[0] = a;
		out[1] = 1;
		out[2] = 0;
		return out;
	}
	else
	{
		g = Extended_Euclid(b, a%b);
		out[0] = g[0];
		out[1] = g[2];
		out[2] = g[1] - g[2] * (a / b);
		return out;
	}
}

int mod_exp(int a, int b, int n)
{
	int c = 0;
	int d = 1;
	int k = (int)(log((double)b) / log((double)2));	//#bits of b
	int i;
	int * bit = (int*)malloc(sizeof(int)*(k + 1));

	//change from b to 2's bits
	for (i = k; i >= 0; i--)
	{
		if (b % 2 == 1)
			bit[i] = 1;
		else
			bit[i] = 0;
		b = b / 2;
	}

	//calculate a^b % n = d
	for (i = 0; i <= k; i++)
	{
		c = 2 * c;
		d = (d*d) % n;
		if (bit[i] == 1)
		{
			c = c + 1;
			d = (d*a) % n;
		}
	}

	return d;
}

int isPrime(int n)
{
	int i;
	//if n is smaller than 2, that is not a prime number
	if (n < 2)
	{
		return 0;
	}
	//when n is even number, it is false. Because n is a large prime number
	if (n % 2 == 0)
	{
		return 0;
	}
	
	//if n is not a prime number, it has a divider smaller than sqrt(n)
	for (i = 3; i < (int)sqrt(n) + 1; i += 2)
	{
		if (n%i == 0)
			return 0;
	}

	return 1;
}

int RSAencryption(int M, int e, int n)
{
	int C;
	//encrypte from M to C
	C = mod_exp(M, e, n);

	return C;
}

int RSAdecryption(int C, int d, int n)
{
	int M;
	//decrypte from C to M
	M = mod_exp(C, d, n);

	return M;
}

void createRand(int * n, int * m)
{
	int prime[2];	//P, Q
	int r;

	srand(time(NULL));

	//create random numbers
	for (int i = 0; i < 2; i++)
	{
		do {
			r = (int)rand()%100;
		} while (!isPrime(r));	// if it is not prime, just redo
		prime[i] = r;
	}

	*n = prime[0]*prime[1];
	*m = (prime[0] - 1)*(prime[1] - 1);
}

int publicKey(int m)
{
	int e;
	//finding a small odd integer e relatively prime to m
	for (e = 3; Euclid(m, e) != 1; e += 2);

	return e;
}

int privateKey(int m, int e)
{
	int d;
	int * temp;
	
	//finding the d in de = 1 (mod m)
	temp = Extended_Euclid(e, m);
	d = temp[1];
	if (d < 0)
		d = d + m;

	return d;
}
