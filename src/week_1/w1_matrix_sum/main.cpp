//
// Created by stas on 4.11.19.
//
#include <iostream>
#include <vector>

using namespace std;

class Matrix{
public:

    Matrix(){
        count_rows = 0;
        count_columns = 0;
    }

    Matrix(int new_rows, int new_columns){
        Reset(new_rows, new_columns);
    }


    void Reset(int new_rows, int new_columns){
        if(new_rows < 0 || new_columns < 0){
            throw std::out_of_range("");
        }

        array.assign(new_rows, vector<int>(new_columns));

        count_rows = new_rows;
        count_columns = new_columns;
    }

    int At(int row, int column) const {
        if(row < 0 || column < 0 || column > count_columns-1 || row > count_rows-1){
            throw std::out_of_range("");
        }
        return array[row][column];
    }

    int& At(int row, int column){
        if(row < 0 || column < 0 || column > count_columns-1 || row > count_rows-1){
            throw std::out_of_range("");
        }
        return array[row][column];
    }

    int GetNumRows() const {
        return count_rows;
    }

    int GetNumColumns() const{
        return count_columns;
    }

private:

    vector<vector<int>> array;
    int count_rows = 0;
    int count_columns = 0;
};

istream& operator>>(istream& in, Matrix& matrix) {
    int num_rows, num_columns;
    in >> num_rows >> num_columns;

    matrix.Reset(num_rows, num_columns);
    for (int row = 0; row < num_rows; ++row) {
        for (int column = 0; column < num_columns; ++column) {
            in >> matrix.At(row, column);
        }
    }

    return in;
}

Matrix operator+(const Matrix& one, const Matrix& two) {
    if((one.GetNumColumns() == 0 || one.GetNumRows() == 0) &&
       (two.GetNumColumns() == 0 || two.GetNumRows() == 0)){
        return Matrix();
    }

    if (one.GetNumRows() != two.GetNumRows()) {
        throw invalid_argument("Mismatched number of rows " + to_string(one.GetNumRows()) + "-" + to_string(two.GetNumRows()));
    }

    if (one.GetNumColumns() != two.GetNumColumns()) {
        throw invalid_argument("Mismatched number of rows" + to_string(one.GetNumColumns()) + "-" + to_string(two.GetNumColumns()));
    }

    Matrix result(one.GetNumRows(), one.GetNumColumns());
    for (int row = 0; row < result.GetNumRows(); ++row) {
        for (int column = 0; column < result.GetNumColumns(); ++column) {
            result.At(row, column) = one.At(row, column) + two.At(row, column);
        }
    }

    return result;
}

ostream& operator<<(ostream& out, const Matrix& matrix) {
    out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
    for (int row = 0; row < matrix.GetNumRows(); ++row) {
        for (int column = 0; column < matrix.GetNumColumns(); ++column) {
            if (column > 0) {
                out << " ";
            }
            out << matrix.At(row, column);
        }
        out << endl;
    }

    return out;
}

bool operator==(const Matrix& first, const Matrix& second){
    if((first.GetNumColumns() == 0 || first.GetNumRows() == 0) &&
       (second.GetNumColumns() == 0 || second.GetNumRows() == 0)){
        return true;
    }

    if(first.GetNumRows() != second.GetNumRows()){
        return false;
    }

    if(first.GetNumColumns() != second.GetNumColumns()){
        return false;
    }

    for (int row = 0; row < first.GetNumRows(); ++row) {
        for (int column = 0; column < first.GetNumColumns(); ++column) {
            if (first.At(row, column) != second.At(row, column)) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;
    return 0;
}