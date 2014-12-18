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
		for(j=p;/* j>0 && */a[j-1]>tmp; j--)//
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
	swap_int(&a[Cent],&a[Right-1]);
	return a[Right-1];
}    




/* 冒泡排序 */
void bubble_sort (int data[], size_t size) 
{
    int swap;
	size_t i;
	for (i = 0; i < size - 1; ++i) 
    {
		int ordered = 1;
		size_t j;
		for (j = 0; j < size - 1 - i; j++)//++j
			if (data[j+1] < data[j]) 
            {
				swap = data[j];
				data[j] = data[j+1];
				data[j+1] = swap;
				ordered = 0;
			}
		if (ordered)
			break;
	}
}


/* 插入排序 */
void insert_sort (int data[], size_t size) 
{
	size_t i;
	for (i = 0; i < size; i++)//++i 
    {
		int inserted = data[i];
		size_t j;
		for (j = i; j > 0 && inserted < data[j-1];--j)//--j
			data[j] = data[j-1];
		if (j != i)
			data[j] = inserted;
	}
}


/* 选择排序 */
void select_sort (int data[], size_t size) 
{
	size_t i;
    size_t min;
    size_t j;
    int swap;

	for (i = 0; i < size - 1; ++i) 
    {
		min = i;
		for (j = i + 1; j < size; ++j)
			if (data[j] < data[min])
				min = j;
		if (min != i) 
        {
			swap = data[i];
			data[i] = data[min];
			data[min] = swap;
		}
	}
}



/* 快速排序 */
void quick_sort (int data[], size_t left,size_t right) 
{
	size_t p = (left + right) / 2;
	size_t i = left;
    size_t j = right;
    int pivot = data[p];

    while (i < j) 
    {
        while(i<p&&pivot>=data[i])
            i++;
//		for (;  (i<p && pivot>=data[i]); i++);//!(i>=p||pivot<data[i])   ++i
		if (i < p) 
        {
			data[p] = data[i];
			p = i;
	    }

        while(j>p&&data[j]>=pivot)
            j--;
//    	for (;  (j>p && data[j]>=pivot); j--);//!(j<=p||data[j]<pivot)   --j
    	if (j > p) 
        {
		    data[p] = data[j];
            p = j;
	    }
	}
	data[p] = pivot;
	if (p - left > 1)
		quick_sort (data, left, p - 1);
	if (right - p > 1)
		quick_sort (data, p + 1, right);

}



void QuickSort(int a[],int Left,int Right)
{
	int i;
	int j;
	int Center;
	const int Cutoff = 3;
	if (Left + Cutoff <= Right)
	{
		Center = Median3(a,Left,Right);
		i = Left;
		j = Right-1;
		while (1)//for()
		{
			while(a[++i] < Center){;}//下标右移
			while(a[--j] > Center){;}//下标左移
			if (i < j)
				swap_int(&a[i],&a[j]);
			else
				break;
		}
		swap_int(&a[i],&a[Right-1]);
		QuickSort(a,Left,i-1);  
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
	int data1[MAX];
    int data2[MAX];
    int data3[MAX];
    int data4[MAX];
    int data5[MAX];
    
    FILE *fp = fopen("sort.txt","at");
    if(fp<0)
        printf("can't open !\n");

    printf("enter a number: ");
    scanf("%d",&MAX);

	size_t i;
//    size_t size = sizeof(data) / sizeof(data[0]);


   for (i = 0; i < MAX; i++)
    {
		printf ("%2d ", data1[i] = rand () % 100);
        fprintf(fp,"%d  ",data1[i]);
    }
    fprintf(fp,"\n");
	printf ("\n");
	bubble_sort (data1, MAX);
    for (i = 0; i < MAX; i++)
    {
		printf ("%2d ", data1[i]);
        fprintf(fp,"%d  ",data1[i]);
    }
    fprintf(fp,"\n\n\n");
	printf ("\n\n\n");


    for (i = 0; i < MAX; i++)
    {
		printf ("%2d ", data2[i] = rand () % 100);
        fprintf(fp,"%d  ",data2[i]);
    }
    fprintf(fp,"\n");
	printf ("\n");
	insert_sort (data2, MAX);
    for (i = 0; i < MAX; i++)
    {
		printf ("%2d ", data2[i]);
        fprintf(fp,"%d  ",data2[i]);
    }
    fprintf(fp,"\n\n\n");
	printf ("\n\n\n");



    for (i = 0; i < MAX; i++)
    {
		printf ("%2d ", data3[i] = rand () % 100);
        fprintf(fp,"%d  ",data3[i]);
    }
    fprintf(fp,"\n");
	printf ("\n");
	select_sort (data3, MAX);	
    for (i = 0; i < MAX; i++)
    {
		printf ("%2d ", data3[i]);
        fprintf(fp,"%d  ",data3[i]);
    }
    fprintf(fp,"\n\n\n");
	printf ("\n\n\n");



    for (i = 0; i < MAX; i++)
    {
		printf ("%2d ", data4[i] = rand () % 100);
        fprintf(fp,"%d  ",data4[i]);
    }
    fprintf(fp,"\n");
	printf ("\n");
    quick_sort (data4, 0, MAX - 1);
    for (i = 0; i < MAX; i++)
    {
		printf ("%2d ", data4[i]);
        fprintf(fp,"%d  ",data4[i]);
    }
    fprintf(fp,"\n\n\n");
	printf ("\n\n");



    for(i = 0; i<MAX; i++)
    {
        printf ("%2d ", data5[i] = rand () % 100);
        fprintf(fp,"%d  ",data5[i]);
    }
    fprintf(fp,"\n");
	printf ("\n");
	QuickSort(data5, 0, MAX-1);
    for (i = 0; i < MAX; i++)
    {
		printf ("%2d ", data5[i]);
        fprintf(fp,"%d  ",data5[i]);
    }
    fprintf(fp,"\n\n\n");
	printf ("\n\n\n");

    fclose(fp);
	return 0;
}
