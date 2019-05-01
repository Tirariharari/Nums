#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>
#include <fstream>

using namespace std;

void search_LU(vector <vector <double> > A, vector <vector <double> > &L,
               vector <vector <double> > &U, int n)
{
    U=A;
    for(int i = 0; i < n; i++)
        for(int j = i; j < n; j++)
            L[j][i]=U[j][i]/U[i][i];
    for(int k = 1; k < n; k++)
    {
        for(int i = k-1; i < n; i++)
            for(int j = i; j < n; j++)
                L[j][i]=U[j][i]/U[i][i];
        for(int i = k; i < n; i++)
            for(int j = k-1; j < n; j++)
                U[i][j]=U[i][j]-L[i][k-1]*U[k-1][j];
    }
}

void proisv(vector <vector <double> > A,
            vector <vector <double> > B,
            vector <vector <double> > &R, int n)
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                R[i][j] += A[i][k] * B[k][j];
}

void show(vector <vector <double> > A, int n) {
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout <<"\t"<< A[i][j] << "\t";
        cout << endl;
    }
}

int main() {
    int n=3;
    ifstream in("matrix.txt");
    ifstream inB("B.txt");
    vector <vector <double> > A (n), L (n), U(n), R(n);
    double ar[n*n];
    double B[n];
    for(int i =0;i<n*n;i++)
        in>>ar[i];
    for(int i =0; i<n; i++)
        inB>>B[i];
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            A[i].push_back(ar[i*n+j]);
            L[i].push_back(0);
            U[i].push_back(0);
            R[i].push_back(0);
        }
    }
    search_LU(A,L,U,n);
    _getch();
    cout << endl;
    cout << "B:" << endl;
    for(int i =0; i<n; i++)
    cout << B[i] << "\t";
    cout << endl << endl;
    double Y[n];
    Y[0] = B[0]/L[0][0];
    for (int i =1; i<n; i++){
        Y[i] = B[i];
        for (int j=0; j<i; j++){
            Y[i] = Y[i] - Y[j]*L[i][j];
        }
        Y[i] = Y[i]/L[i][i];
    }
    cout << "Y:" << endl;
    for(int i =0; i<n; i++)
        cout << Y[i] << "\t";
    cout << endl << endl;
    double X[n];
    for(int i =n-1; i>=0; i--){
        X[i] = Y[i];
        for(int j=n-1; j>i; j--){
            X[i] = X[i] - X[j]*U[i][j];
        }
    X[i] = X[i]/U[i][i];
    }
    cout << "X:" << endl;
    for(int i =0; i<n; i++)
        cout << X[i] << "\t";
    cout << endl << endl;
    double O[n];
    cout << "AX=" << endl;
    for(int i =0; i<n; i++)
        O[i]=0;
    for (int i =0; i<n; i++){
        for(int j=0; j<n; j++){
            O[i]+= A[i][j]*X[j];
        }
        cout << O[i] << "\t";
    }
    cout << endl;
    return 0;
}
