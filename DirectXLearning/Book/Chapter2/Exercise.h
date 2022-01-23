#pragma once
#include <iostream>

#include <vector>
#include <optional>

namespace Exercise {
typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;

std::optional<Matrix> InvertMatrix(const Matrix& matrix) {
  if (matrix.size() == 0) {
    std::printf("Input matrix is empty\n");
    return {};
  }

  Matrix result(matrix[0].size(), Row(matrix.size(), 0));
  for (size_t i = 0; i < matrix.size(); ++i) {
    for (size_t j = 0; j < matrix[0].size(); ++j) {
      result[j][i] = matrix[i][j];
    }
  }
  return result;
}

std::optional<Matrix> MatrixTimes(const Matrix& A, const Matrix& B) {
  if (A.size() == 0 || B.size() == 0 || A[0].size() != B.size()) {
    std::printf("Matrix A`s column is not equals to B`s row\n");
    return {};
  }

  Matrix result;
  for (const auto& rowA : A) {
    std::vector<int> row(B[0].size(), 0);
    for (size_t i = 0; i < B[0].size(); ++i) {
      for (size_t j = 0; j < B.size(); ++j) {
        row[i] += rowA[j] * B[j][i];
      }
    }
    result.push_back(row);
  }
  return result;
}

void PrintMatrix(const Matrix& m) {
  for (const auto& row : m) {
    for (const auto& i : row) {
      std::cout << i << "\t";
    }
    std::cout << std::endl;
  }
}
} // namespace Exercise
