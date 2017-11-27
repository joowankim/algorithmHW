#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _point
{
	double x;
	double y;
} Point;

double p2p(Point p1, Point p2);	// distance between p1 and p2
double closestPair(Point *p, int l, int r);	// closest pair's distance
void MergeTwoAreaX(Point arr[], int left, int mid, int right);	// merge sort by x value
void MergeTwoAreaY(Point arr[], int left, int mid, int right);	// merge sort by y value
void MergeSort(Point arr[], int left, int right, char a);	// merge sort
void inputPoint(char * line, Point * p);	// read the information by text file

void main()
{
	FILE * fp = fopen("marketing.txt", "r");
	Point * p;
	char Line[81];
	int i, n;
	double temp;

	if(fp == NULL)
	{
		printf("File read failed. \n");
		exit(1);
	}

	fgets(Line, 81, fp);	// read first line
	n = atoi(Line);
	p = (Point*)malloc(sizeof(Point)*n);

	// read points' information
	i=0;
	while(fgets(Line, 81, fp))
	{
		inputPoint(Line, &p[i]);
		i++;
	}
	fclose(fp);

	// compute closest pair's distance
	temp = closestPair(p, 0, n-1);

	printf("%f \n", temp);
}

void inputPoint(char * line, Point * p)
{
	int i, j;
	double t;
	char temp[10];

	// x value
	for(i=0; line[i] != ' '; i++)
		temp[i] = line[i];
	temp[i] = '\0';
	t = atof(temp);
	(*p).x = t;

	// y value
	for(i = i+1, j=0; line[i] != '\n'; i++, j++)
		temp[j] = line[i];
	temp[j] = '\0';
	t = atof(temp);
	(*p).y = t;
}

double closestPair(Point *p, int l, int r)
{
	int i, j;
	int q;	// middle point's index
	int c = 0;	// the number of points in d*d square from middle point
	double dl, dr;	// minimum distance in left/right side
	double d, m;	// minimun distance
	Point * S = (Point*)malloc(sizeof(Point)*(r+1));

	MergeSort(p, l, r, 'x');	// sort by x value

	// the number of points is less than 3
	if(r - l < 3)
	{
		double min = p2p(p[l], p[l+1]);
		for(i=l; i<=r; i++)
		{
			for(j=i+1; j<=r; j++)
			{
				if(min > p2p(p[i], p[j]))
					min = p2p(p[i], p[j]);
			}
		}
		return min;
	}

	q = (l+r)/2;
	if((l+r)%2 != 0) q++;

	dl = closestPair(p, l, q-1);	// left side minimum distance
	dr = closestPair(p, q, r);		// right side minimum distance

	if(dl > dr) d = dr;
	else d = dl;

	// points in d*d square from the middle point
	for(i=l; i<=r; i++)
	{
		if(p[q].x - d <= p[i].x && p[i].x <= p[q].x + d)
		{
			S[c] = p[i];
			c++;
		}
	}

	MergeSort(S, 0, c - 1, 'y');	// sort by y value

	// compute distances between a point and each 7 points
	for(i=0; i<c; i++)
	{
		for(j=i+1; j<i+8; j++)
		{
			if(j == c) break;
			m = p2p(S[i], S[j]);
			if(m < d) d = m;
		}
	}

	return d;
}

double p2p(Point p1, Point p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void MergeTwoAreaX(Point arr[], int left, int mid, int right)
{
	int fIdx = left;
	int rIdx = mid+1;
	int i;

	Point * sortArr = (Point*)malloc(sizeof(Point)*(right+1));
	int sIdx = left;

	while(fIdx<=mid && rIdx<=right)
	{
		if(arr[fIdx].x <= arr[rIdx].x)
			sortArr[sIdx] = arr[fIdx++];
		else
			sortArr[sIdx] = arr[rIdx++];

		sIdx++;
	}

	if(fIdx > mid)
	{
		for(i=rIdx; i<=right; i++, sIdx++)
			sortArr[sIdx] = arr[i];
	}
	else
	{
		for(i=fIdx; i<=mid; i++, sIdx++)
			sortArr[sIdx] = arr[i];
	}

	for(i=left; i<=right; i++)
		arr[i] = sortArr[i];
	
	free(sortArr);
}

void MergeTwoAreaY(Point arr[], int left, int mid, int right)
{
	int fIdx = left;
	int rIdx = mid+1;
	int i;

	Point * sortArr = (Point*)malloc(sizeof(Point)*(right+1));
	int sIdx = left;

	while(fIdx<=mid && rIdx<=right)
	{
		if(arr[fIdx].y <= arr[rIdx].y)
			sortArr[sIdx] = arr[fIdx++];
		else
			sortArr[sIdx] = arr[rIdx++];

		sIdx++;
	}

	if(fIdx > mid)
	{
		for(i=rIdx; i<=right; i++, sIdx++)
			sortArr[sIdx] = arr[i];
	}
	else
	{
		for(i=fIdx; i<=mid; i++, sIdx++)
			sortArr[sIdx] = arr[i];
	}

	for(i=left; i<=right; i++)
		arr[i] = sortArr[i];
	
	free(sortArr);
}


void MergeSort(Point arr[], int left, int right, char a)
{
	int mid;

	if(left < right)
	{
		mid = (left+right) / 2;

		MergeSort(arr, left, mid, a);
		MergeSort(arr, mid+1, right, a);

		if(a=='x') MergeTwoAreaX(arr, left, mid, right);
		else MergeTwoAreaY(arr, left, mid, right);
	}
}
