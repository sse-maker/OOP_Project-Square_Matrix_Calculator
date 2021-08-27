//
//  MyMatrix.hpp
//  Matrix_Calculator
//
//  Created by 세광 on 2021/08/27.
//

#ifndef MyMatrix_hpp
#define MyMatrix_hpp

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template<class type> class MyMatrix {
public:
    MyMatrix();
    MyMatrix(vector<type> matrix, int row, int col);
    ~MyMatrix();
    
    int GetRow();
    int GetCol();
    vector<type> GetMatrix();
    
    MyMatrix operator+(const MyMatrix& M2);
    MyMatrix operator-(const MyMatrix& M2);
    MyMatrix operator*(const MyMatrix& M2);
    MyMatrix operator=(const MyMatrix& M2);
    MyMatrix Transpose();
    string ToString();
    
private:
    vector<type> matrix;
    int row, col;
};

#endif /* MyMatrix_hpp */
