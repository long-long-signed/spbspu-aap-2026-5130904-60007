#include "matrix.hpp"

#include <string>

namespace boikomikhail {
  extern const unsigned char dynamic_idr;
  extern const unsigned short smax_element;

  BadMatrix::BadMatrix(std::string err):
    errmsg_(err) {};
  std::string BadMatrix::what()
  {
    return errmsg_;
  }

  TmpList::TmpList(Matrix &mtr):
    str_{nullptr},
    scounter_{0},
    matrix_(mtr) {};
  void TmpList::setScr(int &i)
  {
    scounter_ = i;
  };
  void TmpList::writeM(unsigned &i, unsigned &j, int &strl)
  {
    matrix_.mt_pointer_[i][j] = strl;
  }
  void TmpList::setStr(std::string *st)
  {
    str_ = st;
  };

  Matrix::Matrix(const int &arrt)
  {
    if (arrt < 1 || arrt > 2) {
      throw BadMatrix("Bad args");
    }
    arrt == dynamic_idr ? is_dynamic_ = 1 : is_dynamic_ = 0;
  }
  Matrix::~Matrix()
  {
    if (is_dynamic_) {
      for (unsigned i{0}; i < row_number_; ++i) {
        delete[] mt_pointer_[i];
      }
      delete[] mt_pointer_;
    }
  }

  void Matrix::arrInit()
  {
    if (is_dynamic_) {
      mt_pointer_ = new int *[row_number_];
      for (unsigned i{0}; i < row_number_; ++i) {
        mt_pointer_[i] = new int[column_number_]{0};
      }
    } else if (!is_dynamic_ && getComps() < smax_element) {
      int i2[column_number_][row_number_];
      int *i2_tmp = reinterpret_cast< int * >(i2);
      mt_pointer_ = &i2_tmp;
    } else {
      throw BadMatrix("Failed to save matrix, input data cannot be save to Matrix");
    };
  }
  void Matrix::setRowNumber(const unsigned &rn)
  {
    row_number_ = rn;
  }
  void Matrix::setColumnNumber(const unsigned &cn)
  {
    column_number_ = cn;
  }
  unsigned Matrix::getColumsCount() const
  {
    return column_number_;
  }
  unsigned long long Matrix::getComps() const
  {
    return row_number_ * column_number_;
  }
  unsigned Matrix::getMatrixLocalMin()
  {
    if (!column_number_ || !row_number_) {
      throw BadMatrix("Cannot find minimum for 0-matrix");
    }
    if (row_number_ < 3 || column_number_ < 3) {
      return 0;
    }

    int localminv{0};
    for (unsigned i{1}; i < row_number_ - 1; ++i) {
      const int *__restrict const prev{mt_pointer_[i - 1]};
      const int *__restrict const cur{mt_pointer_[i]};
      const int *__restrict const next{mt_pointer_[i + 1]};

      int left{cur[0]};
      int center{cur[1]};
      for (unsigned j{1}; j + 1 < column_number_; ++j) {
        const int right{cur[j + 1]};
        if (left > center && right > center && prev[j] > center && next[j] > center) {
          ++localminv;
        }
        left = center;
        center = right;
      }
    }
    return localminv;
  }
}
