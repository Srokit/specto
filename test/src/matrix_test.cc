/**
 * File: test/src/matrix_test.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Unit tests for matrix class.
 * Version: 0.1
 * Date: 2023-06-05
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "gtest/gtest.h"

#include "matrix.h"

TEST(MatrixTest, MultiplySameDimensions) {
  specto_impl::Matrix m1 = specto_impl::Matrix::withDimensions(2, 2);
  m1.setVal(0, 0, 1.0f);
  m1.setVal(0, 1, 2.0f);
  m1.setVal(1, 0, 3.0f);
  m1.setVal(1, 1, 4.0f);

  specto_impl::Matrix m2 = specto_impl::Matrix::withDimensions(2, 2);
  m2.setVal(0, 0, 5.0f);
  m2.setVal(0, 1, 6.0f);
  m2.setVal(1, 0, 7.0f);
  m2.setVal(1, 1, 8.0f);

  specto_impl::Matrix result = m1.multByOther(m2);

  EXPECT_EQ(result.getNumRows(), 2);
  EXPECT_EQ(result.getNumCols(), 2);

  EXPECT_FLOAT_EQ(result.getVal(0, 0), 19.0f);
  EXPECT_FLOAT_EQ(result.getVal(0, 1), 22.0f);
  EXPECT_FLOAT_EQ(result.getVal(1, 0), 43.0f);
  EXPECT_FLOAT_EQ(result.getVal(1, 1), 50.0f);
}


TEST(MatrixTest, MultiplyDiffDimensions) {
  specto_impl::Matrix m1 = specto_impl::Matrix::withDimensions(2, 3);
  m1.setVal(0, 0, 1.0f);
  m1.setVal(0, 1, 2.0f);
  m1.setVal(0, 2, 3.0f);
  m1.setVal(1, 0, 4.0f);
  m1.setVal(1, 1, 5.0f);
  m1.setVal(1, 2, 6.0f);

  specto_impl::Matrix m2 = specto_impl::Matrix::withDimensions(3, 2);
  m2.setVal(0, 0, 7.0f);
  m2.setVal(0, 1, 8.0f);
  m2.setVal(1, 0, 9.0f);
  m2.setVal(1, 1, 10.0f);
  m2.setVal(2, 0, 11.0f);
  m2.setVal(2, 1, 12.0f);

  specto_impl::Matrix result = m1.multByOther(m2);

  EXPECT_EQ(result.getNumRows(), 2);
  EXPECT_EQ(result.getNumCols(), 2);

  EXPECT_FLOAT_EQ(result.getVal(0, 0), 58.0f);
  EXPECT_FLOAT_EQ(result.getVal(0, 1), 64.0f);
  EXPECT_FLOAT_EQ(result.getVal(1, 0), 139.0f);
  EXPECT_FLOAT_EQ(result.getVal(1, 1), 154.0f);
}

TEST(MatrixTest, AddRow) {
  specto_impl::Matrix m1;
  m1.addRow({1.0f, 2.0f});

  EXPECT_EQ(m1.getNumRows(), 1);
  EXPECT_EQ(m1.getNumCols(), 2);

  EXPECT_FLOAT_EQ(m1.getVal(0, 0), 1.0f);
  EXPECT_FLOAT_EQ(m1.getVal(0, 1), 2.0f);

  m1.addRow({3.0f, 4.0f});

  EXPECT_EQ(m1.getNumRows(), 2);
  EXPECT_EQ(m1.getNumCols(), 2);

  EXPECT_FLOAT_EQ(m1.getVal(1, 0), 3.0f);
  EXPECT_FLOAT_EQ(m1.getVal(1, 1), 4.0f);
}

TEST(MatrixTest, AddMultRows) {
  specto_impl::Matrix m1;
  m1.addMultipleRows({{1.0f, 2.0f}, {3.0f, 4.0f}});

  EXPECT_EQ(m1.getNumRows(), 2);
  EXPECT_EQ(m1.getNumCols(), 2);

  EXPECT_FLOAT_EQ(m1.getVal(0, 0), 1.0f);
  EXPECT_FLOAT_EQ(m1.getVal(0, 1), 2.0f);
  EXPECT_FLOAT_EQ(m1.getVal(1, 0), 3.0f);
  EXPECT_FLOAT_EQ(m1.getVal(1, 1), 4.0f);

  m1.addMultipleRows({{5.0f, 6.0f}, {7.0f, 8.0f}});

  EXPECT_EQ(m1.getNumRows(), 4);
  EXPECT_EQ(m1.getNumCols(), 2);

  EXPECT_FLOAT_EQ(m1.getVal(2, 0), 5.0f);
  EXPECT_FLOAT_EQ(m1.getVal(2, 1), 6.0f);
  EXPECT_FLOAT_EQ(m1.getVal(3, 0), 7.0f);
  EXPECT_FLOAT_EQ(m1.getVal(3, 1), 8.0f);
}

TEST(MatrixTest, Transpose) {
  specto_impl::Matrix m1 = specto_impl::Matrix::withDimensions(2, 3);
  m1.setVal(0, 0, 1.0f);
  m1.setVal(0, 1, 2.0f);
  m1.setVal(0, 2, 3.0f);
  m1.setVal(1, 0, 4.0f);
  m1.setVal(1, 1, 5.0f);
  m1.setVal(1, 2, 6.0f);

  specto_impl::Matrix result = m1.transpose();

  EXPECT_EQ(result.getNumRows(), 3);
  EXPECT_EQ(result.getNumCols(), 2);

  EXPECT_FLOAT_EQ(result.getVal(0, 0), 1.0f);
  EXPECT_FLOAT_EQ(result.getVal(0, 1), 4.0f);
  EXPECT_FLOAT_EQ(result.getVal(1, 0), 2.0f);
  EXPECT_FLOAT_EQ(result.getVal(1, 1), 5.0f);
  EXPECT_FLOAT_EQ(result.getVal(2, 0), 3.0f);
  EXPECT_FLOAT_EQ(result.getVal(2, 1), 6.0f);
}