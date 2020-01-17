#include <iostream>

using namespace std;

int main() {
    srand(time(0));

    int n = 5, originalN = n;
    double **arr = new double *[n];
    for (int i = 0; i < n; ++i) arr[i] = new double[n];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            arr[i][j] = rand() % 10;
            cout << arr[i][j] << "  ";
        }
        cout << endl;
    }

    int key;
    double coef, result = 1;
    for (int k = 0; k < originalN - 2; ++k) {
        key = 0;
        while (!arr[0][key]) key++;
        if (key % 2) result = -result;
        result *= arr[0][key];
        for (int i = key + 1; i < n; ++i) {
            if (arr[0][i] != 0) {
                coef = arr[0][i] / arr[0][key];
                for (int j = 1; j < n; ++j) arr[j][i] -= coef * arr[j][key];
            }
        }

        double **temp = new double *[n - 1];
        for (int j = 0; j < n; ++j) temp[j] = new double[n - 1];

        for (int l = 1; l < n; ++l) {
            for (int i = 0, j = 0; j < n; ++i, j++) {
                if (i == key) i++;
                temp[l - 1][j] = arr[l][i];
            }
        }

        n--;
        for (int i = 0; i < n; ++i) arr[i] = new double[n];
        for (int m = 0; m < n; ++m) {
            for (int i = 0; i < n; ++i) {
                arr[m][i] = temp[m][i];
            }
        }
    }

    cout << "____________________________" << endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << arr[i][j] << "  ";
        }
        cout << endl;
    }
    cout << "determine = " << result * (arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0]);
    return 0;
}
