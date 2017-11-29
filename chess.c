#include <stdio.h>
#include <stdlib.h>

typedef struct _point
{
	int x, y;
} Point;

int Promising(Point Path[], int path_idx)
{
	for (int i = 0; i < path_idx; i++) 
	{
		if (abs(Path[i].x - Path[path_idx].x) == abs(Path[i].y - Path[path_idx].y))
			return 1;
	}
	return 0;
}

void Print(Point path[], int rowNum, int bishopNum)
{
	int row = 0, col;
	int i, t;
	for (row = 0; row < rowNum; row++)
	{
		for (col = 0; col < rowNum; col++) 
		{
			for (i = 0; i < bishopNum; i++)
			{
				t = 0;
				if (path[i].x == row && path[i].y == col)
				{
					t = 1;
					break;
				}
			}
			if(t == 1) printf("B");
			else printf("X");
		}
		printf("\n");
	}
	printf("\n");
}

void BackTracking(Point p[], Point path[], int start, int pre, int rowNum, int bishopNum, int * cnt)
{
	for (int i = start; i < rowNum*rowNum; i++)
	{
		path[pre] = p[i];
		if (!Promising(path, pre))
		{
			if (pre == bishopNum - 1)
			{
				(*cnt)++;
				for (int j = 0; j < bishopNum; j++) printf("(%d, %d) ", path[j].x, path[j].y);
				printf("\n");
				Print(path, rowNum, bishopNum);
			}
			else
				BackTracking(p, path, i + 1, pre + 1, rowNum, bishopNum, cnt);
		}
	}
}

void main()
{
	Point * p;	
	Point * path;
	int n = 4, k = 4;
	int i, j, s = 0;
	int cnt = 0;

	p = (Point*)malloc(sizeof(Point)*(n*n));
	path = (Point*)malloc(sizeof(Point) * k);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			p[s].x = i;
			p[s].y = j;
			s++;
		}
	}

	if (path != NULL)
	{
		BackTracking(p, path, 0, 0, n, k, &cnt);
		free(path);
	}

	printf("%d \n", cnt);
	

	
}