/**
 * File: src/matrix.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Matrix class implementation.
 * Version: 0.1
 * Date: 2023-06-05
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "matrix.h"

namespace specto_impl {

Matrix Matrix::withDimensions(int rows, int cols) {
  Matrix m;
  m.rows_ = rows;
  m.cols_ = cols;
  m.data_.resize(rows * cols, 0.0f);
  return m;
}

void Matrix::setVal(int row, int col, float val) {
  data_[row * cols_ + col] = val;
}

float Matrix::getVal(int row, int col) const {
  return data_[row * cols_ + col];
}

void Matrix::setDims(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  data_.resize(rows * cols, 0.0f);
}

Matrix Matrix::multByOther(const Matrix& other) const {
  Matrix result = Matrix::withDimensions(rows_, other.cols_);
  for (int r = 0; r < rows_; ++r) {
    for (int oc = 0; oc < other.cols_; ++oc) {
      float sum = 0.0f;
      for (int c = 0; c < cols_; ++c) {
        sum += getVal(r, c) * other.getVal(c, oc);
      }
      result.setVal(r, oc, sum);
    }
  }
  return result;
}

void Matrix::addRow(const std::vector<float>& row) {
  data_.insert(data_.end(), row.begin(), row.end());
  rows_++;
  cols_ = row.size();
}

}  // namespace specto_impl
