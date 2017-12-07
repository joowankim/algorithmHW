#include <stdio.h>
#include <stdlib.h>

typedef struct _adj
{
	int n1, n2;
} Adj;

int Promising(int ** adj, int path[], int present)
{
	int i;

	for(i=0; i<present; i++)
	{
		if(adj[present][i] == present && path[i] == path[present])
			return 0;
	}
	return 1;
}
void m_coloring(int ** adj, int path[], int present)
{
	int i=0;

	if(Promising(adj, path, present))
	{
		path[i] = color;
		path
		if(
	}
}

void main()
{
	Adj * adj;
	int ** a;
	int * path;
	int v = 3, e = 3;
	int i, j, k;

	path = (int*)malloc(sizeof(int)*v);
	adj = (Adj*)malloc(sizeof(adj)*e);
	a = (int**)malloc(sizeof(int*)*v);

	for(i=0; i<v; i++)
	{
		k=0;
		for(j=0; j<e; j++)
		{
			if(adj[j].n1 == i || adj[j].n2 == i)
				k++;
		}
		a[i] = (int*)malloc(sizeof(int)*k);
	}
	
	for(i=0; i<v; i++)
	{
		k=0;
		for(j=0; j<e; j++)
		{
			if(adj[j].n1 == i || adj[j].n2 == i)
			{
				if (adj[j].n1 == i)
				{
					a[i][k] = adj[j].n2;
					k++;
				}
				else
				{
					a[i][k] = adj[j].n1;
					k++;
				}
			}
		}
	}


}