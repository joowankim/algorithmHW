#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
	int k = (int)log2((double)b);
	int i;
	int * bit = (int*)malloc(sizeof(int)*(k + 1));

	for (i = k; i >= 0; i--)
	{
		if (b % 2 == 1)
			bit[i] = 1;
		else
			bit[i] = 0;
		b = b / 2;
	}
	
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

int primeDis(int n)
{
	int p;

	for (p = 3; p < (int)sqrt(n); p += 2)
	{
		if (n%p == 0)
			break;
	}

	return p;
}

int millarRabin(int n)
{
	int q = n - 1;
	int k = 0;
	
	while(q%2 == 0)
	{
		k++;
		q = q / 2;
	}
	
	double rand = srand(time(0))
}

double RSAencryption(int n, int M)
{#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
	int k = (int)(log((double)b)/log((double)2));
	int i;
	int * bit = (int*)malloc(sizeof(int)*(k + 1));

	for (i = k; i >= 0; i--)
	{
		if (b % 2 == 1)
			bit[i] = 1;
		else
			bit[i] = 0;
		b = b / 2;
	}
	
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

int primeDis(int n)
{
	int p;

	for (p = 3; p < (int)sqrt((double)n); p += 2)
	{
		if (n%p == 0)
			break;
	}

	return p;
}

int millarRabin(int n)
{
	int q = n - 1;
	int k = 0;
	int i, j;
	int a, b;
	int d;

	while(q%2 == 0)
	{
		k++;
		q = q / 2;
	}
	
	srand(time(NULL));
	for (i=0; i<log((double)n); i++)
	{
		a = (int)(rand()%(n-1));
		
		if(a < 2)
			a = 2;

		d = Euclid(a, n);
		if(d != 1)
		{
			return 0;
		}

		b = mod_exp(a, q, n);

		if(b == 1 || b == (n - 1))
		{
			continue;
		}
		else
		{
			for(j=0; j<k-1; j++)
			{
				b = (b * b)%n;
				if(b == (n - 1))
					break;
			}

			if(b != (n-1))
			{
				return 0;
			}
		}
	}
	return 1;
}

double RSAencryption(int M, int *n, int *e)
{
	int E = 3, gcd;
	int C;
	int p, q;
	int r;
	int N;

	srand(time(NULL));
	r = (int)rand() + 2;
	while(!millarRabin(r))
		r = (int)rand() + 2;
	p = r;
	r = (int)rand() + 2;
	while(!millarRabin(r) || p == r)
		r = (int)rand() + 2;
	q = r;

	N = p*q;
	*n = N;
	
	for(E = 3; Euclid((p-1)*(q-1), E) != 1; E+=2);

	*e = E;
	C = mod_exp(M, E, N);

	return C;
}

double RSAdecryption(int n, int e, int C)
{
	int d;
	int M;
	int p, q;
	int * temp;

	p = primeDis(n);
	q = n / p;

	temp = Extended_Euclid(e, (p-1)*(q-1));	//x'
	d = temp[1];
	if (temp[1] < 0)
		d = temp[1] + (p-1)*(q-1);

	M = mod_exp(C, d, n);

	return M;
}

void main()
{
	int M = 19, C;
	int n, e;	//public key

	C = RSAencryption(M, &n, &e);
	printf("N = %d \n", n);
	M = RSAdecryption(n, e, C);
	printf(" %d \n", M);
}


}

double RSAdecryption(int n, int e, int C)
{
	int d;
	int M;
	int p, q;
	int * temp;

	p = primeDis(n);
	q = n / p;

	temp = Extended_Euclid(e, (p-1)*(q-1));	//x'
	d = temp[1];
	if (temp[1] < 0)
		d = temp[1] + (p-1)*(q-1);

	M = mod_exp(C, d, n);

	return M;
}

void main()
{
	int M;
	M = RSAdecryption(119, 5, 66);
	printf(" %d \n", M);
}
