#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

const double X[] = {1.415, 1.420, 1.425, 1.430, 1.435, 1.440, 1.445, 1.450, \
    1.455, 1.460, 1.465, 1.470, 1.475};
const double Y[] = {0.888551, 0.889599, 0.890637, 0.891667, 0.892687, 0.893698, \
    0.894700, 0.895693, 0.896677, 0.897653, 0.898619, 0.899738, 0.914587};
double **delta_y;
int n = 0;
int closest_x = 0;

unsigned factorial (unsigned n){
    if (1==n || 0==n)
        return 1;
    else
        return n*factorial(n-1);
}

double round_to(double v, int digits)
{
	double m = pow(10, digits);
	double x = v * m;
	double r = fabs(fmod(x, 1));

	if (r < 0.5)
		return floor(x) / m;
	else
		return (floor(x) + (v < 0 ? -1 : 1)) / m;
}

void delta_y_creation ()
{
    delta_y = new double*[n];
    for (int i=0; i < n; i++){
        delta_y[i] = new double[n];
        for (int j=0; j < n; j++)
            delta_y[i][j] = 0;
    }

    for (int i=0; i<n; i++)
        delta_y[0][i] = Y[i];

    for (int i=1; i<n; i++){
        for (int j = n-i-1; j>=0; j--){
            delta_y[i][j] = delta_y[i-1][j+1]-delta_y[i-1][j];
            //round_to(delta_y[i][j], -6);
            /*if (delta_y[i][j]*1000000 < 1)
                delta_y[i][j] = 0;
                */
        }
    }

    std::ofstream out;
    out.open("out.txt");
    if (out.is_open())
    {
        for (int j=0; j < sizeof(Y)/sizeof(Y[0]); j++) {
            for (int i=0; i < sizeof(Y)/sizeof(Y[0]); i++)
                out << delta_y[i][j] << "\t";
            out << endl;
        }
    }

}

double FIFN (double sought_x){
    double res = 0;

    double q = (sought_x-X[closest_x])/(X[1]-X[0]);
    double q_res = 1;

    for (int i = 0; i<3; i++) {
        for (int j=0; j<i; j++){
            q_res = q_res*(q-j);
        }
        res = res + q_res*delta_y[i][closest_x]/factorial(i);
        q_res = 1;
    }
    return res;
}

int main()
{
    n = sizeof(Y)/sizeof(Y[0]);
    delta_y_creation ();
    cout << endl << endl;
    for (int i=1; i<=30; i++) {
        double sought_x;
        sought_x = 1.4179+(0.001*i);

        double del = 5;
        for (int j=0; j<n; j++){
            if (fabs(X[j]-sought_x) < del) {
                del = fabs(X[j]-sought_x);
                closest_x = j;
            }
        }

        double res = FIFN(sought_x);
        cout << "x = " << sought_x << "\t" << " y = " << res << endl;
    }
    return 0;
}
