#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _point
{
	double x;
	double y;
} Point;

double p2p(Point p1, Point p2);
double closestPair(Point *p, int l, int r);
void MergeTwoAreaX(Point arr[], int left, int mid, int right);
void MergeTwoAreaY(Point arr[], int left, int mid, int right);
void MergeSort(Point arr[], int left, int right, char a);
void inputPoint(char * line, Point * p);

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

	fgets(Line, 81, fp);
	n = atoi(Line);
	p = (Point*)malloc(sizeof(Point)*n);

	i=0;
	while(fgets(Line, 81, fp))
	{
		inputPoint(Line, &p[i]);
		i++;
	}
	fclose(fp);

	temp = closestPair(p, 0, n-1);

	printf("%d \n", temp);
}

void inputPoint(char * line, Point * p)
{
	int i, j;
	double t;
	char temp[10];

	for(i=0; line[i] != ' '; i++)
		temp[i] = line[i];
	temp[i] = '\0';
	t = atof(temp);
	(*p).x = t;

	for(i = i+1, j=0; line[i] != '\n'; i++, j++)
		temp[j] = line[i];
	temp[j] = '\0';
	t = atof(temp);
	(*p).y = t;
}

double closestPair(Point *p, int l, int r)
{
	int i, j;
	int q;
	int c = 0;
	double dl, dr;
	double d, m;
	Point * S = (Point*)malloc(sizeof(Point)*(r+1));

	MergeSort(p, l, r, 'x');
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

	dl = closestPair(p, l, q-1);
	dr = closestPair(p, q, r);

	if(dl > dr) d = dr;
	else d = dl;

	for(i=l; i<=r; i++)
	{
		if(p[q].x - d <= p[i].x && p[i].x <= p[q].x + d)
		{
			S[c] = p[i];
			c++;
		}
	}

	MergeSort(S, 0, c - 1, 'y');

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
		// 중간 지점을 계산한다.
		mid = (left+right) / 2;

		// 둘로 나눠서 각각을 정렬한다.
		MergeSort(arr, left, mid, a);
		MergeSort(arr, mid+1, right, a);

		// 정렬된 두 배열을 병합한다.
		if(a=='x') MergeTwoAreaX(arr, left, mid, right);
		else MergeTwoAreaY(arr, left, mid, right);
	}
}