//
//  MyMatrix.cpp
//  Matrix_Calculator
//
//  Created by 세광 on 2021/08/27.
//

#include "MyMatrix.hpp"

template<class type> MyMatrix<type>::MyMatrix() : row(0), col(0) { matrix.clear(); }
template<class type> MyMatrix<type>::MyMatrix(vector<type> matrix, int row, int col) : matrix(matrix), row(row), col(col) {}
template<class type> MyMatrix<type>::~MyMatrix() {}

template<class type> int MyMatrix<type>::GetRow() { return row; }
template<class type> int MyMatrix<type>::GetCol() { return col; }
template<class type> vector<type> MyMatrix<type>::GetMatrix() { return matrix; }

template<class type> MyMatrix<type> MyMatrix<type>::operator+(const MyMatrix& M2) {
    MyMatrix<type> addition;
    addition.row = row;
    addition.col = col;
    for (int i = 0; i < matrix.size(); i++) addition.matrix.push_back(matrix[i] + M2.matrix[i]);
    return addition;
}
template<class type> MyMatrix<type> MyMatrix<type>::operator-(const MyMatrix& M2) {
    MyMatrix<type> subtraction;
    subtraction.row = row;
    subtraction.col = col;
    for (int i = 0; i < matrix.size(); i++) subtraction.matrix.push_back(matrix[i] + M2.matrix[i]);
    return subtraction;
}
template<class type> MyMatrix<type> MyMatrix<type>::operator*(const MyMatrix& M2) {
    MyMatrix<type> multiplication;
    multiplication.row = row;
    multiplication.col = col;
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            type sum = 0;
            for (int k = 0; k < row; k++) sum += matrix[col * i + k] * M2.matrix[col * k + j];
            multiplication.matrix.push_back(sum);
        }
    }
    return multiplication;
}
template<class type> MyMatrix<type> MyMatrix<type>::operator=(const MyMatrix& M2) {
    matrix = M2.matrix;
    row = M2.row;
    col = M2.col;
    return *this;
}
template<class type> MyMatrix<type> MyMatrix<type>::Transpose() {
    MyMatrix<type> transpose;
    transpose.row = row;
    transpose.col = col;
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            transpose.matrix.push_back(matrix[col * j + i]);
        }
    }
    return transpose;
}
template<class type> string MyMatrix<type>::ToString() {
    string set_string = "";
    for (int i = 0; i < matrix.size(); i++) {
        stringstream s;
        s << matrix[i];
        string temp1 = s.str();
        set_string = set_string + temp1;
        if (i != matrix.size() - 1) {
            string temp2 = " ";
            set_string = set_string + temp2;
            if (i % row == row - 1) {
                temp2 = "| ";
                set_string = set_string + temp2;
            }
        }
    }
    return set_string;
}
