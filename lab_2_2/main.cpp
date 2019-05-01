#include <iostream>
#include <stdio.h>

using namespace std;

int N = 4;

double A[4][5] = {
	{ 5, 2, -1, 2, -22},
	{ 0.5, -4, 2, -1, 14.5},
	{ -1, 0.2, -6, 3, 2.2},
	{1, -0.5, 3, -6, 8}
};

double B[4] = {22, -14.5, -2.2, -8};
double res[4];
double eps = 10;

void print_matrix() {
	for (int i=0; i<N; i++) {
		for (int j=0; j<N+1; j++)
			printf("%s%.1f\t", (j==4)?"| ":"", A[i][j]);
		cout << endl;
	}
	cout << endl;
}

void zeidel() {
	for (int i = 0; i < N; ++i) {
		res[i] = B[i];
		for (int j = 0; j < N; ++j){
			res[i] += A[i][j] * res[j];
		}
	}
	return;
}

void change_matr() {
	for (int i = 0; i < N; ++i) {
		double del = A[i][i];
		for (int j = 0; j < N; ++j) {
			if (i == j) {
				A[i][j] = 0;
			}
			else {
				A[i][j] /= del;
				A[i][j] *= -1;
			}
		}
		B[i] /= del;
	}

	for (int i = 0; i < N; ++i) {
		res[i] = B[i];
	}

	return;
}

void check() {
	double chk;
	for (int i = 0; i < N; ++i) {
		chk = B[i];
		for (int j = 0; j < N; ++j) {
			chk += A[i][j] * res[j];
		}

		chk -= res[i];
		if (chk < 0) chk *= -1;
		if (i == 0)
			eps = chk;
		else
			if (chk > eps) eps = chk;
	}
	return;
}

void output(){
	for (int i = 0; i < N; ++i) {
		printf("x%d = %.5f\n", i+1, res[i]);
	}
}

int main() {
	print_matrix();
	change_matr();

	while (eps >= 0.001) {
		zeidel();
		check();
	}
	output();

	return 0;
}
