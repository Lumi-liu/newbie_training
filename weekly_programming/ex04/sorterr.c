/*=====================================
Filename:
    sort.c

Copyright (C) 2006 Wistron
All rights reserved.

Description:
    This is a simple insert sort algorithm.

Author/Created Date:
        Lumi-liu, Dec17'14

Modification History:


Note:


======================================*/

#include <stdio.h>
#include <stdlib.h>

//#define MAX 50


void swap_int(int *a,int *b)
{
	int c;
	c = *a;
	*a = *b;
	*b = c;
}



void InsertionSort(int a[],int N)
{
	int j;
	int p;
	int tmp;
	for(p=0; p<N; p++)//p=1
	{
		tmp = a[p];  //p=0
		for(j=p;a[j-1]>tmp; j--)//
		{
			a[j] = a[j-1];
		}
		a[j] = tmp;
	}
}
  

int Median3(int a[],int Left,int Right)
{
        int Cent = (Left + Right) / 2;
        if (a[Left] > a[Cent])
            swap_int(&a[Left],&a[Cent]);
        if (a[Left] > a[Right])
            swap_int(&a[Left],&a[Right]);
        if (a[Cent] > a[Right])
            swap_int(&a[Cent],&a[Right]);
//        swap_int(&a[Cent],&a[Right-1]);
//        return a[Right-1];
        return a[Cent];    
}    


void QuickSort(int a[],int Left,int Right)
{
	int i;
	int j;
    int k;
	int Center;
	const int Cutoff = 3;
	if (Left + Cutoff <= Right)
	{
		Center = Median3(a,Left,Right);
		i = Left;
		j = Right;
		while (1)//for()
		{
			while(a[++i] < Center){;}//下标右移
			while(a[--j] > Center){;}//下标左移
			if (i < j)		
                swap_int(&a[i],&a[j]);
			else
				break;
		}
//		swap_int(&a[i],&a[Right-1]);
		QuickSort(a,Left,i);
		QuickSort(a,i+1,Right);
	}
	else
	{
		InsertionSort(a+Left,Right-Left+1);
	}
}


int main (void) 
{
    srand (time (NULL));
    int MAX;
    int data5[MAX];
    printf("enter a number: ");
    scanf("%d",&MAX);

	size_t i;
    for(i = 0; i<MAX; i++)
        printf ("%2d ", data5[i] = rand () % 100);
	printf ("\n");
	QuickSort(data5, 0, MAX-1);
    for (i = 0; i < MAX; i++)
		printf ("%2d ", data5[i]);
	printf ("\n\n\n");
	return 0;
}
