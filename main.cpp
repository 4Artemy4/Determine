#include <iostream>
#include <utility>
#include <vector>
#include <bits/stdc++.h>

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

    Matrix(int numOfRows, int numOfColumns, string in) {

        this->rows = numOfRows;
        this->columns = numOfColumns;
        this->array = new double *[this->rows];
        for (int l = 0; l < this->rows; ++l) {
            this->array[l] = new double[this->columns];
        }

        int i = 0, j = 0;
        string temp;
        if (in[0] == '-' || (in[0] > '0' && in[0] <= '9')) {
            in = standartFormat(in);
        } else if (in[0] == '{' || in[0] == '(' || in[0] == '[') {
            cout << "this function will be added in future\n";
//            in = bracketsFormat(in);
        } else {
            cout << "i can't understand this format,"
                    "pishy normal'no, po shablonu. Ili ya tebya naidu i vivernu pal'cy v druguu storonu. Understand?";
        }

        for (int k = 0; k < in.length(); ++k) {
            if (in[k] == ' ') {
                this->array[j][i] = stringToDouble(temp);
                temp = "";
                i++;
            } else if (in[k] == '\n') {
                this->array[j][i] = stringToDouble(temp);
                i = 0;
                temp = "";
                j++;
            } else temp += in[k];
        }

    }

    string standartFormat(string input) {
        string num, result;
        int rows = 0, columns = 0;
        int start = 0, end = input.length();
        while ((input[start] < '0' || input[start] > '9') && input[start]!='-') start++;
        while (input[end] < '0' || input[end] > '9') end--;
        for (int i = start; i <= end; ++i) {
            if ((input[i] < '0' || input[i] > '9') && input[i] != '-' && input[i] != '.') {
                result += num + " ";
                columns++;
                num = "";
                if (columns == this->columns) {
                    result += '\n';
                    columns = 0;
                }
            } else num += input[i];
        }
        result += num + " ";
        return result;
    }

// Todo Reading from string in brackets format

//    string bracketsFormat(string input) {
//        string result, num;
//        int i = 0, start = 0, end = input.length() - 1, columns = 0;
//        while (input[start] != '{' && input[start] != '(' && input[start] != '[') start++;
//        while (input[end] != '}' && input[end] != ')' && input[end] != ']') end--;
//        try {
//            if (start >= end) throw 5;
//            stack<char> brackets;
//            i = start;
//            while (i <= end) {
//                if (input[i] == '{' || input[i] == '[' || input[i] == '(') {
//                    brackets.push(input[i]);
//                } else if (input[i] == '}' && brackets.top() == '{') brackets.pop();
//                else if (input[i] == ']' && brackets.top() == '[') brackets.pop();
//                else if (input[i] == ')' && brackets.top() == '(') brackets.pop();
//                else if ((input[i] == ',' || input[i] == ' ') && num.length() > 0) {
//                    if (columns != this->columns) {
//                        columns++;
//                    } else {
//                        columns = 0;
//                        result += '\n';
//                    }
//                    result += num + " ";
//                    num = "";
//                } else if ((input[i] > '0' && input[i] <= '9') || input[i] == '.') {
//                    num += input[i];
//                }
//                i++;
//            }
//            if(!brackets.empty()) throw 5;
//        } catch (int error) {
//            if (error == 5) cout << "some error in format of input string. Maybe you are forget bracket";
//            exit(error);
//        }
//        cout << result;
//        return result;
//    }
//
    double stringToDouble(string &input) {
        double result = 0;
        int nums = 0;
        bool positive = true;

        if (input[0] == '-') {
            nums++;
            positive = false;
        }
        while (input[nums] != '.' && input[nums] != ',' && nums < input.length()) nums++;
        for (int i = positive ? 0 : 1; i < nums; ++i) {
            result += (input[i] - '0') * pow10(nums - i - 1);
        }
        for (int j = nums + 1; j < input.length(); ++j) {
            result += double(input[j] - '0') / pow10(j - nums);
        }
        if (positive) return result;
        return -result;
    }

    int pow10(int step) {
        int result = 1;
        for (int i = 1; i < step + 1; ++i) {
            result *= 10;
        }
        return result;
    }

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
    string str1 = "4 1 -3 2";
    string str2 = "1 -5 6 -2";
    string str3 = "-3 4 2 -4";

    auto *matr1 = new Matrix(2, 2, str1);
    auto *matr2 = new Matrix(2, 2, str2);
    auto *matr3 = new Matrix(2, 2, str3);

    cout << matr1->out() << matr2->out() << matr3->out();
    return 0;
}

