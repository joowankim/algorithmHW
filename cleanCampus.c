#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct _point
{
	double x;
	double y;
} Point;


Point GrahamScan(Point p[]);
void InsertSort(Point arr[], int n);
int outerProduct(Point p1, Point p2);
int isCCW(int n);
Point sub(Point p1, Point p2);

void main()
{

}

int isCCW(int n)
{
	if (n > 0)
		return 1;
	else 
		return 0;
}

Point GrahamScan(Point p[])
{
	Point p0;
	p0.x = 0;
	p0.y = 0;
	int n = sizeof(p)/sizeof(Point);
	Point * po = (Point*)malloc(sizeof(Point)*n);

	InsertSort(p, n);
	
	po[0] = p[0];
	po[1] = p[1];
	po[2] = p[2];	

	for(int i = 3, j = 3; i < n; i++)
	{
		while(!isCCW(outerProduct(sub(p[i-1], p[i-2]), sub(p[i], po[0]))))
		{
			
		}
		po[j] = p[i];
	}
}

Point sub(Point p1, Point p2)
{
	Point p;
	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;

	return p;
}
