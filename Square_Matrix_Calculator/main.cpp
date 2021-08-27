//
//  main.cpp
//  Matrix_Calculator
//
//  Created by 세광 on 2021/08/26.
//

#include "MyMatrix.hpp"

void Writer(string output);
template <class type> MyMatrix<type> Calc(vector<string> command);
template <class type> vector<type> Reader(string filename, int *row, int *col);
template <class type> int ErrorHanding(vector<type> temp, int row, int col);
template <class type> MyMatrix<type> BasicCalc(MyMatrix<type> M1, MyMatrix<type> M2, vector<string> command);

int main() {
    ifstream fin("input_p2.txt");
    string str;
    while (!fin.eof()) {
        istringstream cutter(str);
        string temp;
        vector<string> command;
        command.clear();
        
        while (getline(cutter, temp, ' ')) command.push_back(temp);
        
        Calc<long long>(command);
    }
    fin.close();
}

void Writer(string output) {
    static int line = 1;
    ofstream fout;
    if (line == 1) {
        fout.open("output_p2.txt");
    } else {
        fout.open("output_p2.txt", ios::app);
        fout << endl;
    }
    fout << output;
    fout.close();
    line++;
}

template <class type> MyMatrix<type> Calc(vector<string> command) {
    MyMatrix<type> none;
    vector<type> temp;
    int row, col;
    if (command[1] == "=") {
        temp = Reader<type>(command[0], &row, &col);
        if (ErrorHanding<type>(temp, row, col)) {
            MyMatrix<type> M3(temp, row, col);
            string name_M3 = command[0];
            for (int i = 0; i < 2; i++) command.erase(command.begin());
            
            M3 = Calc<type>(command);
            if (M3.GetRow() == 0) {
                return none;
            } else {
                ofstream fwrite_M3(name_M3 + ".txt");
                for (int i = 0; i < M3.GetCol(); i++) {
                    for (int j = 0; j < M3.GetRow(); j++) {
                        fwrite_M3 << M3.GetMatrix()[M3.GetCol() * i + j];
                        if (j != M3.GetRow() - 1) fwrite_M3 << " ";
                    }
                    if (i != M3.GetCol() - 1) fwrite_M3 << endl;
                }
                fwrite_M3.close();
            }
        }
    } else {
        switch (command.size()) {
            case 2:
                temp = Reader<type>(command[1], &row, &col);
                if (ErrorHanding<type>(temp, row, col)) {
                    MyMatrix<type> M1(temp, row, col);
                    Writer(M1.Transpose().ToString());
                    return M1.Transpose();
                } else return none;
            
            case 3:
                temp = Reader<type>(command[0], &row, &col);
                if (ErrorHanding<type>(temp, row, col)) {
                    MyMatrix<type> M1(temp, row, col);
                    
                    temp = Reader<type>(command[2], &row, &col);
                    if (ErrorHanding<type>(temp, row, col)) {
                        MyMatrix<type> M2(temp, row, col);
                        return BasicCalc<type>(M1, M2, command);
                    }
                } else return none;
                
            case 4:
                if (command[0] == "TRANS") {
                    temp = Reader<type>(command[1], &row, &col);
                    if (ErrorHanding<type>(temp, row, col)) {
                        MyMatrix<type> M1(temp, row, col);
                        command.erase(command.begin());
                        
                        temp = Reader<type>(command[2], &row, &col);
                        if (ErrorHanding<type>(temp, row, col)) {
                            MyMatrix<type> M2 (temp, row, col);
                            return BasicCalc<type>(M1.Transpose(), M2, command);
                        }
                    }
                } else if (command[2] == "TRANS") {
                    temp = Reader<type>(command[0], &row, &col);
                    if (ErrorHanding<type>(temp, row, col)) {
                        MyMatrix<type> M1(temp, row, col);
                        command.erase(command.begin() + 2);
                        
                        temp = Reader<type>(command[2], &row, &col);
                        if (ErrorHanding<type>(temp, row, col)) {
                            MyMatrix<type> M2(temp, row, col);
                            return BasicCalc<type>(M1, M2.Transpose(), command);
                        }
                    }
                } else return none;
                
            case 5:
                temp = Reader<type>(command[1], &row, &col);
                if (ErrorHanding<type>(temp, row, col)) {
                    MyMatrix<type> M1(temp, row, col);
                    command.erase(command.begin());
                    command.erase(command.begin() + 2);
                    
                    temp = Reader<type>(command[2], &row, &col);
                    if (ErrorHanding<type>(temp, row, col)) {
                        MyMatrix<type> M2(temp, row, col);
                        return BasicCalc<type>(M1.Transpose(), M2.Transpose(), command);
                    }
                } else return none;
        }
    }
    return none;
}

template <class type> vector<type> Reader(string filename, int *row, int *col) {
    *row = 0;
    *col = 0;
    string read;
    ifstream freader(filename + ".txt");
    vector<type> container;
    container.clear();
    if (!freader.is_open()) {
        Writer("NO_MATRIX");
        return container;
    }
    while (!freader.eof()) {
        getline(freader, read);
        istringstream cutter(read);
        string num_string;
        int col_temp = 0;
        while (getline(cutter, num_string, ' ')) {
            type temp = stoll(num_string);
            container.push_back(temp);
            col_temp++;
        }
        (*row)++;
        if (col_temp >= *col) *col = col_temp;
    }
    freader.close();
    return container;
}

template <class type> int ErrorHanding(vector<type> temp, int row, int col) {
    if (row == 0 && col == 0) {
        return 0;
    } else if (row != col) {
        Writer("NOT_SQUARE");
        return 0;
    } else if (temp.size() != row * col) {
        Writer("LOST_ELEMENT");
        return 0;
    } else return 1;
}

template <class type> MyMatrix<type> BasicCalc(MyMatrix<type> M1, MyMatrix<type> M2, vector<string> command) {
    if (M1.GetCol() == M2.GetCol()) {
        MyMatrix<type> M3;
        if (command[1] == "+") M3 = M1 + M2;
        else if (command[2] == "-") M3 = M1 - M2;
        else if (command[3] == "*") M3 = M1 * M2;
        Writer(M3.ToString());
        return M3;
    } else {
        MyMatrix<type> none;
        Writer("UNAVAILABLE_OPERATION");
        return none;
    }
}
