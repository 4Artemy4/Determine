#include <iostream>
#include "Matrix.h"


using namespace std;

int main() {
    std::string str1 = "4 1 -3 2";
    std::string str2 = "1 -5 6 -2";
    std::string str3 = "-3 4 2 -4";
    std::string str4 = "1 2 3 3 -1 4 5 3 2";

    auto matr4 = new Matrix(3, 3, str4);
    auto *matr1 = new Matrix(2, 2, str1);
    auto *matr2 = new Matrix(2, 2, str2);
    auto *matr3 = new Matrix(2, 2, str3);

//    std::cout << matr1->out() << matr2->out() << matr3->out();
//
//    Matrix *inv1 = matr1->inverseMatrix();
//    Matrix *inv2 = matr2->inverseMatrix();
//    Matrix *temp = *matr3*inv2;
    std::cout << matr4->out();
    std::cout << matr4->determine();
    std::cout << matr4->inverseMatrix()->out();
    return 0;
}

