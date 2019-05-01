#include <iostream>
#include <stdio.h>

#define FORMAT "%.3f\t"

using namespace std;

int N = 4;

double y[4];
double x[4];

double A[4][5] = {
	{ 5 ,  1 ,-1, 2, 22  },
	{0.5, -4 , 2,-1,-14.5},
	{-1 , 0.2,-6, 3,-2.2 },
	{ 1 ,-0.5, 3,-6,-8   }
};

double C[4][4] = {
	{1,0,0,0},
	{0,1,0,0},
	{0,0,1,0},
	{0,0,0,1}
};

double B[4][4] = {
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
};

void out_mat_A()
{
	printf("MatA:\n");
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N+1; j++)
		{
			printf("%s", (j==4)?"| ":"");
			printf(FORMAT, A[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

void out_mat_B()
{
	printf("MatB:\n");
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
			printf(FORMAT, B[i][j]);
		cout << endl;
	}
	cout << endl;
}

void out_mat_C()
{
	printf("MatC:\n");
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
			printf(FORMAT, C[i][j]);
		cout << endl;
	}
	cout << endl;
}

double count_B(int i, int j)
{
	if(j>i)
		return 0;

	B[i][j]=A[i][j];

	for(int k = 0; k < j; k++)
	{
		B[i][j]-=((B[i][k])*(C[k][j]));
	}
}

double count_C(int i, int j)
{
	if(i>=j)
		return 0;

	C[i][j]=A[i][j];

	for(int k = 0; k < i; k++)
	{
		C[i][j]-=B[i][k]*C[k][j];
	}
	C[i][j]/=B[i][i];
}

int main()
{
	for(int i=0; i<N; i++)
	{

		for(int j=0; j<N; j++)
		{
			count_C(j,i);
		}
		for(int j=0; j<N; j++)
		{
			count_B(i,j);
		}
	}

	out_mat_A();
	out_mat_B();
	out_mat_C();

	for(int i=0; i<N; i++)
	{
		y[i] = A[i][N];
		for(int k = 0; k < i; k++)
		{
			y[i]-=((B[i][k])*(y[k]));
		}
		y[i]/=B[i][i];
		printf("Y%d = %f\n", i+1, y[i]);
	}
	printf("\n");


	for(int i=N-1; i>=0; i--)
	{
		x[i] = y[i];
		for(int k = i+1; k < N; k++)
		{
			x[i]-=((C[i][k])*(x[k]));
		}
		printf("X%d = %f\n", i+1, x[i]);
	}
}
