#include <iostream>
#include <chrono>

using namespace std;

class Matrix {
public:

    Matrix(int numOfRows, int numOfColumns) {
        this->rows = numOfRows;
        this->columns = numOfColumns;
        this->array = new double *[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->array[i] = new double[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                this->array[i][j] = 0;
            }
        }
    }

    Matrix(int numOfRows, int numOfColumns, double **array) {
        this->columns = numOfColumns;
        this->rows = numOfRows;
        this->array = new double *[this->rows];
        for (int i = 0; i < rows; ++i) {
            this->array[i] = new double[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                this->array[i][j] = array[i][j];
            }
        }
    }

    Matrix(Matrix &mtr) {
        this->rows = mtr.rows;
        this->columns = mtr.columns;
        this->array = new double *[this->rows];
        for (int i = 0; i < rows; ++i) {
            this->array[i] = new double[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                this->array[i][j] = mtr.array[i][j];
            }
        }
    }


    Matrix operator+(const Matrix &matrix2) {
        try {
            if (rows != matrix2.rows || columns != matrix2.columns) throw;
        } catch (exception &e) {
            cout << "nums of rows or columns are not equal";
        }
        auto *temp = new Matrix(rows, columns);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                temp->array[i][j] = this->array[i][j] + matrix2.array[i][j];
            }
        }

        return *temp;
    }

    Matrix operator*(const Matrix &b) {

    }

//    Matrix operator=(const Matrix& matrix2) {
//        try {
//           if (this->rows != matrix2.rows || this->columns != matrix2.columns) throw ;
//        }catch (exception& e){
//            cout << "nums of rows or columns are not equal";
//        }
//
//        for (int i = 0; i < this->rows; ++i) {
//            for (int j = 0; j < this->columns; ++j) {
//                this->array[i][j] = matrix2.array[i][j];
//            }
//        }
//        this->columns = matrix2.columns;
//        this->rows = matrix2.rows;
//        return *this;
//    }

    Matrix *copy() {
        Matrix *temp = new Matrix(this->rows, this->columns, this->array);
        return temp;

    }

    string out() {
        string result;
        for (int i = 0; i < this->columns; ++i) {
            result += "|  ";
            for (int j = 0; j < this->rows; ++j) {
                result += std::to_string(this->array[i][j]) + "  ";
            }
            result += "|\n";
        }
        return result+'\n';
    }

    Matrix get(int row, int col) {

    }

    int columns{};
    int rows{};
    double **array{};

    double determine() {
        int n = this->rows, originalN = n;

        Matrix *temp;
        Matrix *arr = new Matrix(*this);
//        std::cout << temp->out();
//        std::cout << arr->out();

        int key;
        double coef, result = 1;
        for (int k = 0; k < originalN - 2; ++k) {
            key = 0;
            while (!arr->array[0][key]) key++;
            if (key % 2) result = -result;
            result *= arr->array[0][key];
            for (int i = key + 1; i < n; ++i) {
                if (arr->array[0][i] != 0) {
                    coef = arr->array[0][i] / arr->array[0][key];
                    for (int j = 1; j < n; ++j) arr->array[j][i] -= coef * arr->array[j][key];
                }
            }

            temp = new Matrix(n - 1, n - 1);
            for (int l = 1; l < n; ++l) {
                for (int i = 0, j = 0; j < n-1; ++i, j++) {
                    if (i == key) i++;
                    temp->array[l - 1][j] = arr->array[l][i];
                }
            }

            n--;
            arr = new Matrix(*temp);
        }
        return result * (temp->array[0][0] * temp->array[1][1] - temp->array[0][1] * temp->array[1][0]);
    }


};

int main() {
    int n = 4, originalN = n;

    double **arr = new double *[n];
    arr[0] = new double[n]{2, -4, -9, -5};
    arr[1] = new double[n]{1, 3, 5, -1};
    arr[2] = new double[n]{2, -5, 0, 9};
    arr[3] = new double[n]{-2, 0, -1, 1};

    Matrix *matr = new Matrix(4, 4, arr);
    std::cout << matr->out()<< matr->determine();

//    Matrix *matr2 = new Matrix(1, 1);

    //
//    matr2 = new Matrix(*matr);
//    std::cout << matr2->out();
//
//    auto matr3 = new Matrix(*matr2);
//    std::cout << matr2->out();


    srand(time(0));

    auto t1 = std::chrono::high_resolution_clock::now();

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
//                cout << arr[m][i]<<"  ";
            }
//            cout << endl;
        }
//        cout << "koeff = " << result;
//        cout << endl << endl;
    }

//    cout << "____________________________" << endl;

//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            cout << arr[i][j] << "  ";
//        }
//        cout << endl;
//    }

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
//    cout << "determine = " << result * (arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0]);
//    cout << endl << duration;
    return 0;
}

