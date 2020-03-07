#include <iostream>
#include <vector>

using namespace std;

class Matrix {

private:
    int columns{};
    int rows{};
    double **array{};
public:
    Matrix(int numOfRows, int numOfColumns) {
        try {
            if (numOfRows < 1 || numOfColumns < 1) throw 66;
        } catch (int error) {
            cout << "invalid size (" << numOfRows << ", " << numOfColumns << ")\n";
            exit(error);
        }
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
        try {
            if (numOfRows < 1 || numOfColumns < 1) throw 66;
        } catch (int error) {
            cout << "invalid size (" << numOfRows << ", " << numOfColumns << ")\n";
            exit(error);
        }
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

    //ToDo enter matrix from string
//    Matrix(int numOfRows, int numOfColumns, string &in){
//        int i = 0, j = 0;
//        string temp;
//
//        this->rows = numOfRows;
//        this->columns = numOfColumns;
//        this->array = new double *[this->rows];
//        for (int i = 0; i < this->rows; ++i) {
//            this->array[i] = new double[this->columns];
//        }
//
//        for (int k = 0; k < in.size(); ++k) {
//            if(in[k] == ' ') {
//                this->array[i][j] = temp;
//                temp = "";
//                i++;
//            }
//            else if (in[k] == '\n') j++;
//            else temp+=in[k];
//        }
//
//
//    }
//
//    double stringToDouble(string input){
//
//        for (int i = 0; i < input.size(); ++i) {
//
//        }
//    }
//
//    int pow10(int step){
//        int result = 1;
//        for (int i = 1; i < step+1; ++i) {
//            result*=10;
//        }
//        return result;
//    }

    Matrix *operator+(const Matrix *secondMatrix) {
        try {
            if (this->rows != secondMatrix->rows || this->columns != secondMatrix->columns)throw 10;
        } catch (int error) {
            cout << "nums of rows or columns are not equal" << "\nrows: (" << this->rows << ")\t(" << secondMatrix->rows
                 << ')' << "\ncolumns: (" << this->columns << ")\t(" << secondMatrix->columns << ')';
            exit(error);
        }
        auto *temp = new Matrix(this->rows, this->columns);

        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                temp->array[i][j] = this->array[i][j] + secondMatrix->array[i][j];
            }
        }
        return temp;
    }

    Matrix *operator*(const Matrix *secondMatrix) {
        try {
            if (this->columns != secondMatrix->rows && this->rows != secondMatrix->columns)throw 10;
        } catch (int error) {
            cout << "num of columns1 and rows2 or rows1 and columns2 are not equal" << "\ncolumns1: (" << this->columns
                 << ")\trows2: (" << secondMatrix->rows
                 << ')' << "\nrows1: (" << this->columns << ")\tcolumns2: (" << secondMatrix->columns << ')';
            exit(error);
        }
        double sum = 0;
        Matrix *result = new Matrix(this->columns, this->rows);

        for (int k = 0; k < this->rows; ++k) {
            for (int i = 0; i < this->columns; ++i) {
                for (int j = 0; j < secondMatrix->columns; ++j) {
                    sum += this->array[k][j] * secondMatrix->array[j][i];
                }
                result->array[k][i] = sum;
                sum = 0;
            }

        }
        return result;
    }

    Matrix *transposition() {
        if (this->rows == 1 && this->columns == 1) return this;
        auto result = new Matrix(this->rows, this->columns);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                result->array[j][i] = this->array[i][j];
            }
        }
        return result;
    }


    Matrix *getMinor(int rowForDeleting, int columnForDeleting) {
        try {
            if (this->columns <= columnForDeleting || this->rows <= rowForDeleting)throw 10;
            else if (rowForDeleting < 0 || columnForDeleting < 0) throw -1;
        } catch (int error) {
            if (error == 10)
                cout << "row or column for deleting >= size of matrix" << "\nrows: original ("
                     << this->rows << ")\tfor deleting (" << rowForDeleting << ')'
                     << "\ncolumns: original(" << this->columns << ")\tfor deleting(" << columnForDeleting << ')';
            if (error == -1)cout << "maloletniy debil\n";
            exit(error);
        }

        if (this->rows == 1 && this->columns == 1)return this;
        auto *result = new Matrix(this->rows - 1, this->columns - 1);
        for (int i = 0, i1 = 0; i < this->rows; i++) {
            if (i != rowForDeleting) {
                for (int j = 0, j1 = 0; j < this->columns; j++) {
                    if (j != columnForDeleting) {
                        result->array[i1][j1] = this->array[i][j];
                        j1++;
                    }
                }
                i1++;
            }
        }
        return result;
    }


    double determine() {
        try {
            if (this->rows != this->columns) throw 10;
        } catch (int error) {
            cout << "Matrix is not square\n" << "\nnum of rows = " << this->rows << "\nnum of columns = "
                 << this->columns;
            exit(error);
        }

        int n = this->rows, originalN = n;
        if (n == 1)return this->array[0][0];

        Matrix *temp;
        auto *arr = new Matrix(*this);

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
            n--;
            temp = new Matrix(n, n);
            for (int l = 1; l < n + 1; ++l) {
                for (int i = 0, j = 0; j < n; ++i, j++) {
                    if (i == key) i++;
                    temp->array[l - 1][j] = arr->array[l][i];
                }
            }
            arr = new Matrix(*temp);
        }
        return result * (arr->array[0][0] * arr->array[1][1] - arr->array[0][1] * arr->array[1][0]);
    }


    Matrix *inverseMatrix() {
        try {
            if (this->rows != this->columns) throw 10;
        } catch (int error) {
            cout << "Matrix is not square\n" << "\nnum of rows = " << this->rows << "\nnum of columns = "
                 << this->columns;
            exit(error);
        }
        int n = this->rows;
        Matrix *result = new Matrix(n, n);
        double det = this->determine();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                result->array[i][j] = ((i + j) % 2 == 1 ? -1 : 1) * this->getMinor(i, j)->determine() / det;
            }
        }
        return result->transposition();
    }

    int getNumOfRows() {
        return this->rows;
    }

    int getNumOfColumn() {
        return this->columns;
    }

    double getElement(int row, int column) {
        try {
            if (row < 0 || column < 0 || row >= this->rows || column >= this->columns) throw 66;
        } catch (int error) {
            cout << "invalid indexes\n" << "num of rows in matrix = " << this->rows << "\t your value = " << row
                 << "\nnum of columns in matrix = " << this->columns << "\t your value = " << column;
            exit(error);
        }
        return this->array[row][column];
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
        return result + '\n';
    }
};

int main() {
    double **arr = new double *[1];
    arr[0] = new double[1]{6};
    Matrix *zero = new Matrix(1, 1, arr);

    double **arr1 = new double *[4];
    arr1[0] = new double[4]{4, 1, 0, 4};
    arr1[1] = new double[4]{-3, 2, 9, 5};
    arr1[2] = new double[4]{-7, 8, 12, 5};
    arr1[3] = new double[4]{4, 2, 6, 0};
    Matrix *matr1 = new Matrix(4, 4, arr1);

    double **arr2 = new double *[2];
    arr2[0] = new double[2]{1, -5};
    arr2[1] = new double[2]{6, -2};
    Matrix *matr2 = new Matrix(2, 2, arr2);

    double **arr3 = new double *[2];
    arr3[0] = new double[3]{-3, 4, 2};
    arr3[1] = new double[3]{2, -4, 7};
//    arr3[2] = new double [3]{5, 3, 8};

    Matrix *matr3 = new Matrix(2, 3, arr3);

    cout << matr1->determine();
//    *matr3*matr3;
//    matr1->getMinor(0, 3);
//    cout << matr2->inverseMatrix()->out() << matr2->out() << (*matr2->inverseMatrix() * matr2)->out();

    return 0;
}

