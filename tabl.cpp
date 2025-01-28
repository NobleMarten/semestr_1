#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

const int S = 5;
const int n_stolb = 4;
const int otstup = 7;
const int len_str = 97;
const int len_stolb = 15;

void star(ofstream& f, int n, int m) {
    f.width(n);
    for (int i = 0; i < m; i++)
        f << '*';
    f << endl;
}

void star1(ofstream& f, int n) {
    f.width(n);
    f << "*";
    f.width(len_stolb + 1);
    f << "*";

    for (int i = 0; i <= n_stolb; i++) {
        f.width(len_stolb + 1);
        f << '*';
    }
    f << endl;
}

int main() {
    char fullname[S][15];
    char name_Costs[3][20];
    int number_medal[S][n_stolb + 2];
    char cost[80];

    ifstream in("olimpiad.txt");
    ofstream out("cost.txt");

    in.getline(cost, 80);

    for (int i = 0; i < S; i++)
        in >> fullname[i];

    for (int i = 0; i < 3; i++)
        in >> name_Costs[i];

    for (int i = 0; i < S; i++)
        for (int j = 0; j < 3; j++)
            in >> number_medal[i][j];

    in.close();

    // рассчитываем сумму медалей и максимальное количество медалей
    for (int i = 0; i < S; i++) {
        number_medal[i][3] = number_medal[i][0] + number_medal[i][1] + number_medal[i][2];
        int maxMedal = number_medal[i][0];
        for (int j = 1; j < 3; j++) {
            if (number_medal[i][j] > maxMedal) {
                maxMedal = number_medal[i][j];
            }
        }
        number_medal[i][4] = maxMedal; 
    }

    out << endl;
    out.width(4.5 * len_stolb);
    out << cost << endl;
    out << endl << endl;

    star(out, otstup + 1, len_str);
    star1(out, otstup + 1);

    out.width(otstup + 1);
    out << "*";
    out.width(len_stolb + 1);
    out << "*";

    for (int i = 0; i < 3; i++) {
        out << " " << name_Costs[i];
        out.width(len_stolb - strlen(name_Costs[i]));
        out << "*";
    }
    out << "     Total     *"; 
    out << "   Max Medal   *"; 
    out << endl;


    star1(out, otstup + 1);
    star(out, otstup + 1, len_str);

    for (int i = 0; i < S; i++) {
        star1(out, otstup + 1);
        out.width(otstup + 1);
        out << "*";
        out << " " << fullname[i];
        out.width(len_stolb - strlen(fullname[i]));
        out << "*";

        for (int j = 0; j < n_stolb + 1; j++) {
            out << setw(11) << number_medal[i][j]; 
            out << setw(5) << "*";
        }
        out << endl;
        star1(out, otstup + 1);
        star(out, otstup + 1, len_str);
    }



    star(out, otstup + 1, len_str);
    star1(out, otstup + 1);

    out.width(otstup + 1);
    out << "*";
    out << " Total         *"; 

    for (int j = 0; j < n_stolb + 1; j++) {
        int totalSum = 0;
        for (int i = 0; i < S; i++)
            totalSum += number_medal[i][j];
        out << setw(11) << totalSum; 
        out << setw(5) << "*";
    }

    out << endl;
    star1(out, otstup + 1);
    star(out, otstup + 1, len_str);
    out << endl;

    system("pause");
    return 0;
}
