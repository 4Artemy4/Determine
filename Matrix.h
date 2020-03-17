//
// Created by artemy on 3/17/20.
//


#ifndef DETERMINANT_MATRIX_H
#define DETERMINANT_MATRIX_H


#include <string>

class Matrix {
private:
    unsigned long long columns{};
    unsigned long long rows{};
    double **array{};

    std::string standartFormat(std::string input);

    std::string bracketsFormat(std::string input);

    static int pow10(int step);

    static double stringToDouble(std::string &input);

public:
    Matrix(unsigned long long  numOfRows, unsigned long long  numOfColumns);

    Matrix(unsigned long long  numOfRows, unsigned long long  numOfColumns, double **array);

    Matrix(const Matrix &mtr);

    Matrix(unsigned long long  numOfRows, unsigned long long  numOfColumns, std::string in);

    Matrix *operator+(const Matrix *secondMatrix);

    Matrix *operator+(double num);

    Matrix *operator*(const Matrix *secondMatrix);

    Matrix *operator*(double num);

    Matrix *transposition();

    Matrix *getMinor(unsigned long long  rowForDeleting, unsigned long long  columnForDeleting);

    double determine();

    Matrix *inverseMatrix();

    Matrix *unionMatrix();

    unsigned long long  getNumOfRows();

    unsigned long long  getNumOfColumn();

    double getElement(unsigned long long  row, unsigned long long  column);

    std::string out();

    std::string convertToLibreMathFormat();

};


#endif //DETERMINANT_MATRIX_H
