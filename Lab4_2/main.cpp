#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

const double X[] = {1.50, 1.55, 1.60, 1.65, 1.70, 1.75, 1.80, 1.85, 1.90, \
                    1.95, 2.00, 2.05, 2.10, 2.15, 2.20};
const double Y[] = {15.132, 17.422, 20.393, 23.994, 28.160, 32.812, 37.857, \
                    43.189, 48.689, 54.225, 59.158, 64.817, 69.550, 74.782, 79.548};

double **delta_y; //  [столбец/номер дельты] [строка/соотвествие x-у]
int n = 0;

unsigned factorial (unsigned n) {
    if (1==n || 0==n)
        return 1;
    else
        return n*factorial(n-1);
}

double round_to(double v, int digits) {
	double m = pow(10, digits);
	double x = v * m;
	double r = fabs(fmod(x, 1));

	if (r < 0.5)
		return floor(x) / m;
	else
		return (floor(x) + (v < 0 ? -1 : 1)) / m;
}

void delta_y_creation () {
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
            round_to(delta_y[i][j], -6);
            if (fabs(delta_y[i][j]*1000000) < 1)
                delta_y[i][j] = 0;
        }
    }

    /*
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
    */
}

double q_G_search (double q, int n_counter){  /// Поиск коэффициента (q+n-1)*...*(q-n) для формулы Гаусса
    if (n_counter == 0)
        return 1;
    if (n_counter == 1)
        return q;

    double qn = 1;
    int in_descending = (n_counter/2)+1;
    for (int i=0; i<in_descending; i++)
        qn = qn*(q-i);
    for (int i=1; i<=n_counter-in_descending; i++)
        qn = qn*(q+i);
    return qn;
}

double Gauss (double sought_x) {
    double res = 0;
    int idx_closest_x = 0;
    double q = 1;
    double qn = 1;

    /// Поиск ближайшего значения x
    for (int j=0; j<n; j++){
        if (fabs(X[j]-sought_x) < fabs(X[idx_closest_x]-sought_x)) {
            idx_closest_x = j;
        }
    }
    q = (sought_x-X[idx_closest_x])/(X[1]-X[0]);
    //cout << q << endl;

    for (int i=0, j=0; i<2*idx_closest_x; i++) {
        qn = q_G_search(q, i);
        res = res + qn*(delta_y[idx_closest_x-j][i])/factorial(i);
        if (i%2==1)
            j++;
        qn = 1;
    }

    return res + Y[idx_closest_x];
}

double q_S_search (double q, int n_counter) {  /// Поиск коэффициента (q+n-1)*...*(q-n) для формулы Стирлинга
    double res = q;
    for (int i=1; i<n_counter; i++){
        res = res*(pow(q, 2) - pow(i, 2));
    }
    return res;
}

double Stirling (double sought_x) {
    /// Поиск ближайшего x
    double res = 0;
    int idx_closest_x = 0;
    for (int j=0; j<n; j++){
        if (fabs(X[j]-sought_x) < fabs(X[idx_closest_x]-sought_x)) {
            idx_closest_x = j;
        }
    }

    /// Вычисление q (шаг)
    double q = 1;
    q = (sought_x-X[idx_closest_x])/(X[1]-X[0]);

    for (int i = 0, j = 0; i < 2*idx_closest_x; i++){
        double coeff;
        switch (i){
        case 0:
            coeff = 1;
            break;
        case 1:
            coeff = q;
            break;
        case 2:
            coeff = pow(q, 2);
        default:
            coeff = q_S_search(q, j)/factorial(i);
            break;
        }
        double y = 0;

        if (i%2 == 1){
            j++;
            y = (delta_y[i][idx_closest_x-j] + delta_y[i][idx_closest_x-j+1])/2;
        } else {
            y = delta_y[i][idx_closest_x-j];
        }
        res += coeff*y;
    }
    return res;
}

double q_B_search (double p, int n_counter) {  /// Поиск коэффициента (q+n-1)*...*(q-n) для формулы Бесселя
    /*
    double res = 1;
    for (int i=1; i<n_counter; i++){
        res = res*(pow(p, 2) - (pow(i, 2)/4));
    }
    return res;
    */
}

double Bessel (double sought_x) {
    /*
    /// Поиск ближайшего x
    double res = 0;
    int idx_closest_x = 0;
    for (int j=0; j<n; j++){
        if (fabs(X[j]-sought_x) < fabs(X[idx_closest_x]-sought_x)) {
            idx_closest_x = j;
        }
    }

    /// Вычисление q (шаг)
    double q = 1;
    q = (sought_x-X[idx_closest_x])/(X[1]-X[0]);
    double p = q - 0.5;

    for (int i = 0, j = 0; i < 2*idx_closest_x; i++){
        double coeff;
        //
        double y = 0;

        if (i%2 == 1){
            j++;
            //y =
        } else {
            //y =
        }
        res += coeff*y;
    }
    return res;
    return 0;
    */
}

int main() {
    double sought_x = 0;
    n = sizeof(Y)/sizeof(Y[0]);
    delta_y_creation ();

    sought_x=1.60+(0.006*3);
    cout << sought_x << endl;
    cout << "Gauss : " << Gauss (sought_x) << endl;

    sought_x=1.725+(0.002*3);
    cout << sought_x << endl;
    cout << "Stirling : " << Stirling (sought_x) << endl;

    sought_x=1.83+(0.003*3);  /// -
    cout << sought_x << endl;
    cout << "Bessel : " << Bessel (sought_x) << endl;
    return 0;
}
