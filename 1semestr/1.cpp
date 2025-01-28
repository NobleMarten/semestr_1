//kirill 1 11 1a 1b 2a 3a
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;



double** create(ifstream& f, int n, int m)
{
    if (!f) {
    cout << "can't open file :(\n";
    exit(-1);
    } 
    double** a = new double* [n];
    for (int i=0; i<n; i++){
        a[i] = new double[m];
        for (int j=0; j<m; j++){
        f >> a[i][j];
        }
    }
    return a;
}

void show(ofstream& f, double** a, double* x, int n, int m){
    f << "matrix a: \n";
    for(int i=0; i < n; i++){
        for(int j=0; j < m; j++){
            f << a[i][j] << " ";
        }
        f << endl;
    }
    f << endl;
    f << "vector x: \n";
    for (int i = 0; i < n; i++)
    f << x[i] << "\n";
}

bool p_k(double* a_i, int m) {
    for (int j = 0; j < m; j++) {
        if (a_i[j] < 0) {
            return false;
        }
    }
    return true;
}

double f(double* a_i, int m) {
    double* m_i = new double[m];
    double mx = sin(a_i[0] * a_i[0] + 3.7);
    for (int j = 0; j < m; j++) {
        m_i[j] = sin(a_i[j] * a_i[j] + 3.7);
        if (m_i[j] > mx) {
            mx = m_i[j];
        }
    }
    return mx;
    delete[] m_i;
}

double g(double* a_i, int m) {
    double* m_i = new double[m];
    double mn = cos(a_i[0] - 3.7);
    for (int j = 0; j < m; j++) {
        m_i[j] = cos(a_i[j] - 3.7);
        if (m_i[j] < mn) {
            mn = m_i[j];
        }
    }
    return mn;
    delete[] m_i;
}


void A_to_X(double** a, int n, int m, double*& x) {
    x = new double[n];
    for (int i = 0; i < n; i++) {
        if (p_k(a[i], m)) {
            x[i] = f(a[i], m);
        }
        else {
            x[i] = g(a[i], m);
        }
    }

}

void del_arr(double** arr, int n) { // ф-ия чтобы удалять двумерный динамический массив
    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    
    ifstream in("semestr_1.txt");
    ofstream out("out1.txt");
    int n, m;
    in >> n >> m;

    double** a = create(in, n, m);
    in.close();

    double* x;
    A_to_X(a, n, m, x);

    show(out, a, x, n, m);
    out.close();
    del_arr(a, n);
    delete[] x;
    return 0;
}
