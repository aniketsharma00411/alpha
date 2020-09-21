#ifndef _matrix_operations_hpp_
#define _matrix_operations_hpp_

#include <all.h>
#include <matrix.hpp>

class MatrixOp {
  private:
    Matrix cofactor(Matrix, Matrix, int, int);
    Matrix adjoint(Matrix);

  public:
    Matrix concat(Matrix, Matrix, std::string);
    Matrix matrix_mult(Matrix, Matrix);
    double determinant(Matrix, int);
    Matrix inverse(Matrix);
};

Matrix MatrixOp::concat(Matrix mat1, Matrix mat2, std::string type) {
    if (type == "column") {
        if (mat1.row_length() != mat2.row_length())
            assert(("The Matrix objects should be of compatible dimensions", false));
        for (int i = 0; i < mat1.row_length(); i++) {
            mat1.str_mat[i].insert(mat1.str_mat[i].end(), mat2.str_mat[i].begin(),
                                   mat2.str_mat[i].end());
        }
    } else if (type == "row") {
        if (mat1.col_length() != mat2.col_length())
            assert(("The Matrix objects should be of compatible dimensions", false));
        mat1.str_mat.insert(mat1.str_mat.end(), mat2.str_mat.begin(), mat2.str_mat.end());

    } else {
        assert(("Concatenate dimension wrong", false));
    }
    if (mat1.if_double) {
        mat1.to_double();
    }
    return mat1;
}

Matrix MatrixOp::matrix_mult(Matrix mat1, Matrix mat2) {
    if (mat1.col_length() != mat2.row_length())
        assert(("The Matrix objects should be of compatible dimensions", false));

    Matrix mat;
    for (int i = 0; i < mat1.row_length(); i++) {
        std::vector<double> row;
        for (int j = 0; j < mat2.col_length(); j++) {
            row.push_back(0);
        }
        mat.double_mat.push_back(row);
    }
    for (unsigned long int i = 0; i < mat1.row_length(); i++) {
        for (unsigned long int j = 0; j < mat2.col_length(); j++) {
            for (unsigned long int k = 0; k < mat2.row_length(); k++) {
                mat.double_mat[i][j] += (mat1.double_mat[i][k] * mat2.double_mat[k][j]);
            }
        }
    }
    mat.to_string();
    return mat;
}

Matrix MatrixOp::cofactor(Matrix mat, Matrix temp, int p, int q) {
    int i = 0, j = 0;
    for (int row = 0; row < mat.row_length(); row++) {
        for (int col = 0; col < mat.col_length(); col++) {
            if (row != p && col != q) {
                temp.double_mat[i][j++] = mat.double_mat[row][col];
                if (j == mat.col_length() - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
    temp.to_string();
    return temp;
}

double MatrixOp::determinant(Matrix mat, int n) {
    if (mat.row_length() != mat.col_length())
        assert(("The Matrix must be a square matrix", false));
    double D = 0;
    if (n == 1)
        return mat.double_mat[0][0];
    Matrix temp;
    for (int i = 0; i < n; i++) {
        std::vector<double> row;
        for (int j = 0; j < n; j++) {
            row.push_back(0);
        }
        temp.double_mat.push_back(row);
    }
    temp.to_string();
    int sign = 1;
    for (int f = 0; f < n; f++) {
        temp = cofactor(mat, temp, 0, f);
        D += sign * mat.double_mat[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }
    return D;
}

Matrix MatrixOp::adjoint(Matrix mat) {
    Matrix result;
    for (int i = 0; i < mat.row_length(); i++) {
        std::vector<double> row;
        for (int j = 0; j < mat.col_length(); j++) {
            row.push_back(0);
        }
        result.double_mat.push_back(row);
    }
    result.to_string();
    if (mat.col_length() == 1) {
        result.double_mat[0][0] = 1;
        return result;
    }

    int sign = 1;
    Matrix temp;
    for (int i = 0; i < mat.row_length(); i++) {
        std::vector<double> row;
        for (int j = 0; j < mat.col_length(); j++) {
            row.push_back(0);
        }
        temp.double_mat.push_back(row);
    }
    temp.to_string();
    for (int i = 0; i < mat.row_length(); i++) {
        for (int j = 0; j < mat.col_length(); j++) {
            temp = cofactor(mat, temp, i, j);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            result.double_mat[j][i] = (sign) * (determinant(temp, temp.col_length() - 1));
        }
    }
    result.to_string();
    return result;
}

Matrix MatrixOp::inverse(Matrix mat) {
    if (mat.row_length() != mat.col_length())
        assert(("The Matrix must be a square matrix", false));
    double det = determinant(mat, mat.col_length());
    if (det == 0)
        assert(("The Matrix is singular", false));

    Matrix adj = adjoint(mat);
    Matrix result;
    for (int i = 0; i < mat.row_length(); i++) {
        std::vector<double> row;
        for (int j = 0; j < mat.col_length(); j++) {
            row.push_back(0);
        }
        result.double_mat.push_back(row);
    }
    for (int i = 0; i < mat.col_length(); i++)
        for (int j = 0; j < mat.col_length(); j++)
            result.double_mat[i][j] = adj.double_mat[i][j] / det;
    result.to_string();
    return result;
}

#endif /* _matrix_operations_hpp_ */