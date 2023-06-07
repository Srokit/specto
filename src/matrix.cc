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

#include <algorithm>

namespace specto_impl {

Matrix Matrix::withDimensions(int rows, int cols) {
  Matrix m;
  m.rows_ = rows;
  m.cols_ = cols;
  m.data_.resize(rows * cols, 0.0f);
  return m;
}

Matrix& Matrix::operator=(const Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  data_ = other.data_;
  return *this;
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

void Matrix::addMultipleRows(const std::vector<std::vector<float>>& rows) {
  for (const auto& row : rows) {
    addRow(row);
  }
}

Matrix Matrix::transpose() const {
  Matrix result = Matrix::withDimensions(cols_, rows_);
  for (int r = 0; r < rows_; ++r) {
    for (int c = 0; c < cols_; ++c) {
      result.setVal(c, r, getVal(r, c));
    }
  }
  return result;
}

float Matrix::getMax() const {
  return *std::max_element(data_.begin(), data_.end());
}

void Matrix::multScalarInPlace(float scalar) {
  for (float& val : data_) {
    val *= scalar;
  }
}

}  // namespace specto_impl
