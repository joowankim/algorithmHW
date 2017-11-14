#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "ListBaseStack.h"

typedef struct _point
{
	double x;
	double y;
} Point;

double GrahamScan(Point p[]);
void MergeTwoArea(double arr[], int left, int mid, int right);
void MergeSort(double arr[], int left, int right);

void main()
{

}

double GrahamScan(Point p[])
{
	MergeSort(
}

void MergeTwoArea(double arr[], int left, int mid, int right)
{
	int fIdx = left;
	int rIdx = mid+1;
	int i;

	int * sortArr = (double*)malloc(sizeof(double)*(right+1));
	int sIdx = left;

	while(fIdx<=mid && rIdx<=right)
	{
		if(arr[fIdx] <= arr[rIdx])
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

void MergeSort(double arr[], int left, int right)
{
	int mid;

	if(left < right)
	{
		// �߰� ������ ����Ѵ�.
		mid = (left+right) / 2;

		// �ѷ� ������ ������ �����Ѵ�.
		MergeSort(arr, left, mid);
		MergeSort(arr, mid+1, right);

		// ���ĵ� �� �迭�� �����Ѵ�.
		MergeTwoArea(arr, left, mid, right);
	}
}