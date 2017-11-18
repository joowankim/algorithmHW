#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "ListBaseStack.h"

Stack * GrahamScan(Point p[], int n);		
void InsertSort(Point arr[], int n);		// sorting points by ascending order by angle from anchor
double outerProduct(Point p1, Point p2);	// compute outer product
int isCCW(double n);			// judge CCW
Point sub(Point p1, Point p2);	// compute subtraction vector
double p2p(Point p1, Point p2);	// compute distance between p1 and p2

void main()
{
	Stack s;
	Point p[5];
	double length = 0;	// final length of ribon
	Point la, pr, init;	// last pop, present pop, initiation pop  from stack
	int n = sizeof(p)/sizeof(Point);	// size of points' array

	// inputs
	p[0].x = 0, p[0].y = 0;
	p[1].x = 1, p[1].y = 1;
	p[2].x = -1, p[2].y = 1;
	p[3].x = -1, p[3].y = -1;
	p[4].x = 1, p[4].y = -1;

	StackInit(&s);
	s = *GrahamScan(p, n);
	la = SPop(&s);
	init = la;

	while(1)
	{
		pr = SPop(&s);
		length = length + p2p(la, pr);
		la = pr;
		if (la.x == 0 && la.y == 0)
			break;
	}
	length = length + p2p(la, init) + 2;	// length + distance between last pop and initiation pop + init and la knot length

	printf("%f \n", length);
}



void InsertSort(Point *arr, int n)
{
	int i, j;
	Point insData;

	// finding inserting location
	for(i=2; i<n; i++)
	{
		insData = arr[i];
		
		if(insData.y > 0)
		{
			for(j=i-1; j>=1 ; j--)
			{
				// compair the angles by cos
				if(arr[j].x/sqrt(arr[j].x*arr[j].x - arr[j].y*arr[j].y) < insData.x/sqrt(insData.x*insData.x - insData.y*insData.y)) 
					arr[j+1] = arr[j];
				else
					break;
			}
		}
		else
		{
			for(j=i-1; j>=1 ; j--)
			{
				if(arr[j].x/sqrt(arr[j].x*arr[j].x - arr[j].y*arr[j].y) > insData.x/sqrt(insData.x*insData.x - insData.y*insData.y)) 
					arr[j+1] = arr[j];
				else
					break;
			}
		}
		arr[j+1] = insData;
	}
}

Stack * GrahamScan(Point *p, int n)
{
	Stack s;
	int i;
	int anchor, top_idx, next_idx;

	InsertSort(p, n);
	
	SPush(&s, p[0]); anchor = 0;
	SPush(&s, p[1]); next_idx = 1;
	SPush(&s, p[2]); top_idx = 2;

	for(i = 3; i < n; i++)
	{
		while(1)
		{
			if(!isCCW(outerProduct(sub(p[top_idx], p[next_idx]), sub(p[i], p[anchor]))))
			{
				SPop(&s);	// if top_idx's point is CW, discard
				top_idx = next_idx;	
			}
			else
				break;
		}
		SPush(&s, p[i]);
		next_idx = top_idx;
		top_idx = i;
	}

	return &s;
}

Point sub(Point p1, Point p2)
{
	Point p;
	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;

	return p;
}

int isCCW(double n)
{
	if (n > 0)
		return 1;
	else 
		return 0;
}

double outerProduct(Point p1, Point p2)
{
	double t = p1.x*p2.y - p1.y*p2.x;
	return t;
}

double p2p(Point p1, Point p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
