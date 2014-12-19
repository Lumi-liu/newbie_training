/***************************************************************
Filename: crand.c


Copyright (C) 2006 Wistron
All rights reserved.

Description: 
    This is a  

Author/Created Date: 
    Lumi-liu,Mon 15 Dec 2014 02:22:55 PM CST

Modification History:



Note:



**************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

//#define N 10000000
#define N 100
void swap(int *a,int *b);

int main()
{
    int i;
    int k;
    int p = 0;
    int *num =(int *)malloc(N*sizeof(int));
    int temp;

    FILE *fp = fopen("Ifile.txt", "at");
    if(fp<0)
        printf("can't open !\n");
    
    printf("please input K :");
    scanf("%d",&k);

    for(i=0; i<N; i++)
        num[i] = i;

    for(i=0;i<N;i++)
        swap(&num[i],&num[rand()%N]);
    for(i=0;i<k;i++)
        fprintf(fp,"%d    ",num[i]);
    fclose(fp);
    return 1;
}


void swap(int *a,int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

