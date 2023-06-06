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

  void setVal(int, int, float);
  float getVal(int, int) const;
  inline int getNumRows() const { return rows_; }
  inline int getNumCols() const { return cols_; }

  // Caller is responsible for ensuring dimensions are correct.
  Matrix multByOther(const Matrix&);

 private:
  Matrix() = default;

  int rows_;
  int cols_;
  std::vector<float> data_;
};

}  // namespace specto_impl
