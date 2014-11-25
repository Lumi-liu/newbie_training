/*==========================================
 Filename:
      howmuchone.c

 Copyright (C) 2014 Wistron
 All rights reserved.

 Description:
      This file is used to calculate how much one in a binary number.

 Author/Created Date:
      Lumi-liu, Nov22,2014

 Modification History:

*/


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
