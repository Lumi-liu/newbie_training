#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MIN 0x01


int main ()
{
	long i;
	while(1)
	{
		printf("请输入一个正整数：");
		scanf("%ld",&i);
		if(i>=0)
		{
			int m = 0;
			while(i)
			{	
				if(MIN & i)
					m++;
				i = i >> 1;
			}
			printf("%d\n",m);
			fflush(stdin);
		}
		else
			break;
	}
	return 0;
}
