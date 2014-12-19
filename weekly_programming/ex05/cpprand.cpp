/***************************************************************
Filename: cpprand.cpp


Copyright (C) 2006 Wistron
All rights reserved.

Description: 
    This is a is ranndom number generation.

Author/Created Date: 
    Lumi-liu,Mon 15 Dec 2014 04:01:25 PM CST

Modification History:



Note:



**************************************************************/

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
using namespace std;


//#define N 10000000
#define N 100
void swap(int *a,int *b);

int main()
{
    int i;
    int k;
    int *num = new int[N];

    char Filename[] = "cpprand.txt";
    ofstream fout(Filename);

    cout<<"please input K:";
    cin>>k;

    for(i=0;i<N;i++)
        num[i]=i;

    srand((unsigned)time(NULL));
    for(i=0;i<N;i++)
        swap(num[i],num[rand()%N]);

    for(i=0;i<k;i++)
        fout<<num[i]<<"    ";

    delete[] num;
    cout<<endl;
    
    return 1;

}


void swap(int *a,int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
