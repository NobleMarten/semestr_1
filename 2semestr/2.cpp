// 1.8 1a 1v 3a
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;


double** create(ifstream& f, int n)
{
    if (!f) {
    cout << "can't open file :(\n";
    exit(-1);
    } 
    double** a = new double* [n];
    for (int i=0; i<n; i++){
        a[i] = new double[n];
        for (int j=0; j<n; j++){
        f >> a[i][j];
        }
    }
    return a;
}

void show(ofstream& f, double** a, double** x, int n){
    f << "matrix a: \n";
    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            f << a[i][j] << " ";
        }
        f << "\n";
    }
    f << endl;
    f << "matrix x: \n";
    for (int i = 0; i < n; i++){
        for(int j=0; j < n; j++){
            f << x[i][j] << " ";
        }
        f << "\n";
    }
}

void transposeMatrix(double** a, int n, double**& x) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            x[j][i] = a[i][j];
}

void umnog_Matrix(int n, double** a, double** b, double** c) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
}

void stepen_Matrix(int n, double** a, double** x) {
    double** t = new double*[n];
    for (int i = 0; i < n; i++) 
        t[i] = new double[n];
    umnog_Matrix(n, a, a, t);
    umnog_Matrix(n, t, a, x);

    //for l = 4:

    /*umnog_Matrix(n, a, a, t);
    umnog_Matrix(n, t, a, t);
    umnog_Matrix(n, t, a, x);*/
}

bool predicateP(int n, double** a) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            // вычисление определителя второго порядка
            double determinant = a[i][i] * a[i + 1][j + 1] - a[i][j + 1] * a[i + 1][j];
            if (determinant <= 0)
                return false;
        }
    }
    return true;
}

void del_arr(double** arr, int n) {
    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
}


int main() {
    setlocale(LC_ALL, "ru");

    ifstream in("semestr_2.txt");
    ofstream out("out2.txt");
    int n;
    in >> n;
    bool flag = true;

    double** a = create(in, n);
    in.close();

    double** x = new double* [n];
    for (int i = 0; i < n; i++)
        x[i] = new double[n];

    if (predicateP(n, a)) {
        transposeMatrix(a, n, x);
    } else {
        stepen_Matrix(n, a, x);
        flag = false;
    }

    show(out, a, x, n);
    del_arr(x, n);
    out.close();


    return 0;
}
