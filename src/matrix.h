/**
 * File: src/matrix.h
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Matrix class interface.
 * Version: 0.1
 * Date: 2023-06-05
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#pragma once

#include <vector>

namespace specto_impl {

/**
 * Float matrix data holder which is a 2d array of floats.
 * Can be multiplied by another matrix.
 */
class Matrix {
 public:
  static Matrix withDimensions(int, int);
  Matrix(): rows_(0), cols_(0) {}

  Matrix& operator=(const Matrix&);

  void setVal(int, int, float);
  float getVal(int, int) const;
  inline int getNumRows() const { return rows_; }
  inline int getNumCols() const { return cols_; }

  void setDims(int, int);

  // Caller is responsible for ensuring dimensions are correct.
  Matrix multByOther(const Matrix&) const;

  // Caller is responsible for ensuring col dimension is consistent.
  void addRow(const std::vector<float>&);

  // Caller is responsible for ensuring col dimension is consistent.
  void addMultipleRows(const std::vector<std::vector<float>>&);

  Matrix transpose() const;

  // Undefined behavior if matrix is empty.
  float getMax() const;

  void multScalarInPlace(float);

 private:
  int rows_;
  int cols_;
  std::vector<float> data_;
};

}  // namespace specto_impl
