/*=====================================
Filename:
	sortfile.c

Copyright (C) 2006 Wistron
	All rights reserved.

Description:
	This file is used to sort about file.

Author/Created Date:
	Lumi-liu, Nov19'14

Modification History:

Note:

=======================================*/

#include <stdio.h>
#include <stdlib.h>  
#include <memory.h>
#include <time.h>
#include <assert.h>

//数据交换函数
void swap_int(int* a,int* b)
{
	int c;
	c = *a;
	*a = *b;
	*b = c;
}

//插入排序
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

//三数取中分割法
int Median3(int a[],int Left,int Right)
{
	//if ( Left+3 >= Right )
	//	return -1;
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

//快速排序
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

const int Num = 1000;
//const int  Num = 10000000;//文件内整数的个数
//便于测试，可先定义Num = 1000；
const int  Knum  = 4;//分割成文件的个数
const char *Ifile = "infile.txt";//未排序的文件名
const char *Ofile = "outfile.txt";//最终的文件名

//生成随机数文件
void  gen_infile(int n)
{
	int i;
	FILE *fp = fopen(Ifile, "wt");
	for(i = 0;i < n; i++)
		fprintf(fp,"%d ",rand()%1000);
	fclose(fp);
}


//读取临时文件中数据的个数
int  read_data(FILE *fp,int a[],int n)
{
	int i = 0;
	while ((i < n) && (fscanf(fp,"%d",&a[i]) != EOF))
		i++;
	printf("read: %d integer\n",i);
	return i;
}

//写入文件
void  write_data(FILE *fp,int a[],int n)
{
	int i;
	for(i=0; i<n; i++)
		fprintf(fp,"%d ",a[i]);
}

//临时文件的命名
char* temp_filename(int index)
{
	char *tempfile = (char*) malloc(64*sizeof(char));
	assert(tempfile);
	sprintf(tempfile, "temp%d.txt", index+1);
	return tempfile;
}

//k路串行读取数据
void k_num_read(void)
{
	char* filename;
	int i;
	int cnt;
	int *arr;
	int n=Num/Knum;
	FILE* fin;
	FILE* tmpfile;
	if (n*Knum < Num)
		n++;//各个文件要读取数据的个数
	arr = (int*)malloc(n * sizeof(int));
	assert(arr);
	fin = fopen(Ifile,"rt");
	i = 0;
	
	//分块循环读取数据并写入临时文件
	while ( (cnt = read_data(fin,arr,n))>0)
	{
		//每次读取时先进行排序
		QuickSort(arr,0,cnt-1);
		filename = temp_filename(i++);
		tmpfile = fopen(filename,"w");
		free(filename);
		write_data(tmpfile,arr,cnt);
		fclose(tmpfile);
	}
	//没有生成k路文件时进行诊断
	assert(i == Knum);
	fclose(fin);
	free(arr);
}


//对临时文件进行合并（败者树）
void k_num_merge(void)
{
	FILE *fout;
	FILE **farr;
	char *filename;
	int  *data;
	char *hasNext;
	int i,j,m,min;
//#ifdef OUTPUT_Ofile_DaTaint id;  
//#endif
	fout = fopen(Ofile,"wt");
	//打开文件
	farr = (FILE**)malloc(Knum*sizeof(FILE*));
	assert(farr);

	for(i = 0; i< Knum;i++)
	{
		filename = temp_filename(i);
		farr[i] = fopen(filename,"rt");
		free(filename);
	}
	//建立包含knum个元素的data，hasnext数组
	//存储k路文件的临时数组和读取结束状态
	data = (int*)malloc(Knum*sizeof(int));
	assert(data);
	hasNext = (char*)malloc(sizeof(char)*Knum);
	assert(hasNext);
	memset(data, 0, sizeof(int) * Knum);
	memset(hasNext, 1, sizeof(char) * Knum);
	
	//先读取第一组数据
	for(i = 0; i < Knum; i++)
	{
		if(fscanf(farr[i], "%d", &data[i]) == EOF)
		{
			hasNext[i] = 0;
		}
	}
//#ifdef OUTPUT_Ofile_DaTaid = 0;  
//#endif
	j  = 0;
F_LOOP:
	if (j < Knum)
	{
		while(1)
		{
			min = data[j];
			m = j;
			for(i = j+1; i < Knum; i++)
			{
				if(hasNext[i] == 1  && min > data[i])
				{
					min = data[i];
					m = i;
				}
			}
			
			if(fscanf(farr[m], "%d", &data[m]) == EOF)
			{
				hasNext[m] = 0;
			}
			fprintf(fout, "%d ", min);  
//#ifdef OUTPUT_Ofile_DaTaprintf("fout :%d  %d/n",++id,min);  
//#endif  
			if (hasNext[m] == 0) //m == j &&
			{
				for (i = j+1; i < Knum; i++)
				{
					if (hasNext[m] != hasNext[i])
					{
						m = i;//
						break;
					}
				}
				if (m != j)
				{
					j = m;
					goto F_LOOP;
				}
				break;
			}
		}
	}
	
	
	free(hasNext);
	free(data);
	for(i = 0; i < Knum; ++i)
	{
		fclose(farr[i]);
   	}
	free(farr);
	fclose(fout);
}


int main()
{
	time_t start = time(NULL),end,start_read,end_read,start_merge,end_merge;
	gen_infile(Num);
	end = time(NULL);
	//生成文件的时间
	printf("gen_infile data time:%f\n", 
					(end - start) * 1000.0/ CLOCKS_PER_SEC);
	start_read = time(NULL);
	k_num_read();
	end_read = time(NULL);
	//读取文件的时间
	printf("k_num_read time:%f\n", 
					(end_read - start_read) * 1000.0/ CLOCKS_PER_SEC);
	start_merge = time(NULL);
	k_num_merge();
	end_merge = time(NULL);
	//临时文件合并的时间
	printf("k_num_merge time:%f\n", 
					(end_merge - start_merge) * 1000.0/ CLOCKS_PER_SEC);
	end = time(NULL);
	//总时间
	printf("total time:%f\n", 
					(end - start) * 1000.0/ CLOCKS_PER_SEC);
	return 0;
} 
