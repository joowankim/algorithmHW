#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Euclid(int a,int b)
{
	if (b==0)
		return a;
	else
		return Euclid(b, a%b);
}

int * Extended_Euclid(int a, int b)
{
	int out[3];
	int *g;
	if (b==0)
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
		out[2] = g[1] - g[2]*(a/b);
		return out;
	}
}

int mod_exp(int a, int b, int n)
{
	int c = 0;
	int d = 1;
	int k = (int)sqrt((double)b)+1;
	int i;
	int * bit = (int*)malloc(sizeof(int)*(k+1));

	for (i=k; i>=0; i--)
	{
		if(b%2 == 1)
			bit[i] = 1;
		else
			bit[i] = 0;
		b = b/2;
	}

	for (i=k; i>=0; i--)
	{
		c = 2*c;
		d = (d*d)%n;
		if (bit[k] == 1)
		{
			c = c + 1;
			d = (d*a)%n;
		}
	}

	return d;
}

double RSAdecryption(int n, int e, int C)
{
	int d;
	int M;
	
	d = Extended_Euclid(e, n)[0];	//x'
	printf("%d \n", d);

	return 0;
}

void main()
{
	RSAdecryption(5, 119, 66);
}
