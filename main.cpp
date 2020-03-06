#include <iostream>
#include <vector>

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

    Matrix * operator+(const Matrix *secondMatrix) {
        try {
            if (rows != secondMatrix->rows || columns != secondMatrix->columns) throw;
        } catch (exception &e) {
            cout << "nums of rows or columns are not equal";
        }
        auto *temp = new Matrix(rows, columns);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                temp->array[i][j] = this->array[i][j] + secondMatrix->array[i][j];
            }
        }
        return temp;
    }

    Matrix * operator*(const Matrix *secondMatrix) {
        if (this->columns != secondMatrix->rows && this->rows != secondMatrix->columns)return new Matrix(1, 1);
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

    double get(int row, int col) {

    }

    Matrix * getMinor(int rowForDeleting, int columnForDeleting){
        Matrix *result = new Matrix(this->rows-1, this->columns-1);
        for (int i = 0, i1 = 0; i < this->rows; i++) {
            if (i != rowForDeleting){
                for (int j = 0, j1 = 0; j < this->columns; j++) {
                    if (j != columnForDeleting){
                        result->array[i1][j1] = this->array[i][j];
                        j1++;
                    }
                }
                i1++;
            }
        }
        return result;
    }

    int columns{};
    int rows{};
    double **array{};

    double determine() {
        int n = this->rows, originalN = n;

        if (n == 1)return this->array[0][0];
        else if (n<1) return 0;

        Matrix *temp;
        Matrix *arr = new Matrix(*this);

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
            for (int l = 1; l < n+1; ++l) {
                for (int i = 0, j = 0; j < n; ++i, j++) {
                    if (i == key) i++;
                    temp->array[l - 1][j] = arr->array[l][i];
                }
            }
            arr = new Matrix(*temp);
        }
        return result * (arr->array[0][0] * arr->array[1][1] - arr->array[0][1] * arr->array[1][0]);
    }

    Matrix * transposition(){
        auto result = new Matrix(this->rows, this->columns);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                result->array[j][i] = this->array[i][j];
            }
        }
        return result;
    }

    Matrix * inverseMatrix(){
        Matrix *result = new Matrix(this->rows, this->columns);
        double det = this->determine();
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                result->array[i][j] = ((i+j)%2==1?-1:1) * this->getMinor(i, j)->determine()/det;
            }
        }
        return result->transposition();
    }


};

int main() {
    int n = 3;
    double **arr1 = new double*[n];
    double **arr2 = new double*[n];
    double **arr3 = new double*[n];
    srand(1);
    for (int i = 0; i < n; ++i) {
        arr1[i] = new double [n];

        for (int j = 0; j < n; ++j) {
            arr1[i][j] = rand()%10;
        }
    }
    srand(2);

    for (int i = 0; i < n; ++i) {
        arr2[i] = new double [n];

        for (int j = 0; j < n; ++j) {
            arr2[i][j] = rand()%10;
        }
    }
    srand(3);

    for (int i = 0; i < n; ++i) {
        arr3[i] = new double [n];

        for (int j = 0; j < n; ++j) {
            arr3[i][j] = rand()%10;
        }
    }

    Matrix *matr1 = new Matrix(n, n, arr1);
    Matrix *matr2 = new Matrix(n, n, arr2);
    Matrix *matr3 = new Matrix(n, n, arr3);

    cout << matr1->out();
    cout << matr2->out();
    cout << matr3->out();

    Matrix *matrSum = *matr1 + matr2;

    Matrix *matrMult = *matr1 * matr2;

    cout << matrSum->out();
    cout << matrMult->out();

    cout << matrMult->getMinor(2, 2)->out();

    Matrix *minor = matrMult->getMinor(2, 2);
    cout << minor->out();

    cout << minor->determine() << endl;

    Matrix *inv = minor->inverseMatrix();
    cout << inv->out();

    cout << "result\n" << (*minor*inv)->out();

    return 0;
}

