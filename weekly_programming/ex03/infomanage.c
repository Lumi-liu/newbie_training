/*=====================================
Filename:
	infomanage.c

Copyright (C) 2006 Wistron
All rights reserved.

Description:
	This is a simple program with managing students' information.

Author/Created Date:
	Lumi-liu, Dec 3'14

Modification History:


Note:


=====================================*/


#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include<stdlib.h> 

FILE *fp;

typedef struct student
{
	char num[15];
	char name[10];
	int age;
	char sex[4];
	char tele[20];
	struct student *next;
}stu,*lstu;

void readinformation(lstu L)
{

}


lstu mallocnode(void) 
{ 
	lstu p; 
	int i; 
	p=(stu *)malloc(sizeof(stu)); 
	if(p==NULL) 
	return NULL; 
	for(i=0;i<15;i++) 
	p->num[i]='\0'; 
	for(i=0;i<10;i++) 
	p->name[i]='\0'; 
	for(i=0;i<4;i++) 
	p->sex[i]='\0'; 
	for(i=0;i<20;i++) 
	p->tele[i]='\0'; 
	p->age=0; 
	return p; 
} 
void display(lstu L)  
{
	char x;
	int n=1;
	lstu p;
	p=mallocnode();
	p=L->next;
	if(!p)
	{
		printf("no info\n");
		
	}
	else 
	{
//		printf("\n\n\t\t\t\tinfo\n");
		printf("\tnum\tname\tage\tsex\ttele\n");
		while(p)
		{	
			printf("%d.\t%s\t%s\t%d\t%s\t%s\n",n,p->num,p->name,p->age,p->sex,p->tele);
			p=p->next;
			n++;
		}		
	}
}


void insert(lstu L)     
{
	char choice;
	lstu p;
	printf("Do you really want to insert a information ?(Y/N)\n");
	fflush(stdin);
	scanf("%s",&choice);
	while(!(choice=='Y'||choice=='y'||choice=='n'||choice=='N'))
		{	
			fflush(stdin);
			printf("\n Please enter again : ");
			scanf("%c",&choice);//
		}
	while(choice=='Y'||choice=='y')
	{
		p=mallocnode();
		p->next=L->next;//L->next	
		L->next=p;
		printf("Enter number: ");
		scanf("%s",p->num);	
		printf("Enter name: ");
		scanf("%s",p->name);		
		printf("Enter age: ");
		scanf("%d",&p->age);	
		printf("Enter sex: ");
		scanf("%s",p->sex);
		printf("Enter tele: ");
		scanf("%s",p->tele);

		printf("Do you want to insert again?\n");
		fflush(stdin);
		scanf("%s",&choice);
	}
/*	while(!(choice=='n'||choice=='N'))
		{	
			fflush(stdin);
			printf("\n Please enter again : ");
			scanf("%s",&choice);
		}
*/
}
void Delete(lstu L) 
{   
	lstu p,s;
	char nam[10],nu[15];
//	long i;
	int i;
//	p=mallocnode();
//	s=mallocnode();	
	p=L;
	printf("1. num\n");
	printf("2. name\n");
	printf("Please select a number : ");
//	fflush(stdin);
	scanf("%d",&i);
	fflush(stdin);
	switch(i)
	{
		case 1:
			{   
				fflush(stdin);
				printf("Enter num: ");
				scanf("%s",nu);
				if(!p->next)
				{
					printf("No more information!\n");
					break;
				}
				while(p->next)//!
				{
					if(!strcmp(p->next->num,nu))
						break;						            
          			else
						p=p->next;					   
				}
				if(!p->next)
				{
					printf("No find!\n");
					break;
				}
				if(p->next->next)
				{
					s=p;
					p=p->next;
					s->next=p->next;
					free(p);
					printf("\nsuccess\n");
				}
				else
				{
					s=p;
					p=p->next;
					s->next=NULL;
					free(p);
					printf("\nsuccess\n");
				}
				break;
			}
		case 2:
			{ 
				fflush(stdin);  
				printf("Enter name: ");
				scanf("%s",nam);
				if(!p->next)
					printf("No more information!\n");
				while(p->next)
				{
					if(!strcmp(p->next->num,nam))							
						break;
    				else
						p=p->next;					   
				}
				if(!p->next)
				{
					printf("No find!\n");
					break;
				}
				if(p->next->next)
				{
					s=p;
					p=p->next;
					s->next=p->next;
					free(p);
					printf("\nsuccess!\n");
				}
				else
				{
					s=p;
					p=p->next;
					s->next=NULL;
					free(p);
					printf("\nsuccess!\n");
				}
				break;
			}
		default : 
			{ 
				printf("The number is invalid!\n");
				break;
			}

	}	
}

/*
void InsertOneNode(lstu t,lstu L) 
{ 
	lstu p; 
	p=L; 
	while(p->next) 
	{ 
		p=p->next; 
	} 
	p->next=t; 
} 

void readfromfile(lstu L) 
{  
	lstu p; 
	fp=fopen("informationmanage.txt","r"); 
	if(!fp) 
	{ 
	printf("erro\n"); 
	return; 
	} 
	p=mallocnode(); 
	while(fscanf(fp,"%s%s%d%s%s",p->num,p->name,&p->age,p->sex,p->tele) >0)
	{ 
	InsertOneNode(p,L); 
	p=mallocnode(); 
	} 
	fclose(fp); 
}
 */

void init()   
{	lstu p,r;
	char x;
	printf("*********list*********\n\n");
	printf("    1   insert\n");
	printf("    2   display\n");
	printf("    3   delete\n");
	printf("    4   save\n");
	printf("    5   exit\n\n");

	if(!(fp=fopen("informationmanage.txt","at+")))
	{
		fp=fopen("informationmanage.txt","at+");
		printf("informationmanage.txt\n\n");
		fclose(fp);
	}

	
		printf("Please select a number: ");
	
}

lstu creat_head() 
{ 
	lstu L;
	L=mallocnode();
	L->next=NULL;
	return L;
}
void save(lstu L)  
{ 
	lstu p; 
	p=mallocnode();
	p=L->next; 
	if(!p)// p==NULL
	{ 
		printf("No information saved!\n\n"); 
		return; 
	} 
	fp=fopen("informationmanage.txt","at+"); 
	if(!fp) 
	{ 
	printf("ERROR!\n"); 
	return; 
	} 
	while(p) 
	{ 
		fprintf(fp,"%s %s %d %s %s\n",p->num,p->name,p->age,p->sex,p->tele); 
		p=p->next; 
	} 
	printf("The information is saved successfully!\n");
	fclose(fp); 
} 


void main()
{
	int choice;
	lstu L;
	L=creat_head();
	while(1)
	{
		init();
		scanf("%d",&choice);
		while(!(choice>=1&&choice<=5))
		{	
			fflush(stdin);
			printf("\n");
			scanf("%d",&choice);
		}
		
		switch(choice)
			{
				case 1:{insert(L);   break;}
				case 2:{display(L);  break;}
				case 3:{Delete(L);   break;}			
				case 4:{save(L);     break;}
				case 5:{ free(L);  exit(1); break;}
				default:break;
			}		
	}
}
