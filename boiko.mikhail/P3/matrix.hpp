#ifndef MATRIX_HPP
#define MATRIX_HPP

#pragma once

#include <stdexcept>
#include <string>

namespace boikomikhail {
  class BadMatrix: public std::exception {
  private:
    std::string errmsg_;

  public:
    BadMatrix(std::string err);
    std::string what();
  };
  class TmpList;
  class Matrix {
    friend class TmpList;

  private:
    unsigned mszie_;
    bool is_dynamic_;
    unsigned row_number_;
    unsigned column_number_;
    int **mt_pointer_;

  public:
    Matrix(const int &arrt);
    void arrInit();
    unsigned getColumsCount() const;
    unsigned long long getComps() const;
    void setRowNumber(const unsigned &cn);
    void setColumnNumber(const unsigned &cn);

    unsigned getMatrixLocalMin();

    ~Matrix();
  };
  class TmpList {
    friend std::ifstream &operator>>(std::ifstream &ifs, TmpList &tmpl);

  private:
    unsigned scounter_;
    const std::string *str_;
    Matrix &matrix_;

  public:
    TmpList(Matrix &mtr);
    void setScr(int &i);
    void setStr(std::string *st);
    void writeM(unsigned &i, unsigned &j, int &strl);
  };
}
#endif
