#include "matrix.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace boikomikhail {
  unsigned char dynamic_idr{2};
  unsigned char in_file_argc{2};
  unsigned char exp_arg_count{3};
  unsigned short smax_element{10000};
  std::ifstream &operator>>(std::ifstream &ifs, TmpList &tmpl)
  {
    int strl {std::stoi(*tmpl.str_)};
    switch (tmpl.scounter_) {
    case 0:
      strl <= 0 ? throw BadMatrix("Invalid columns number given") : tmpl.matrix_.setRowNumber(strl);
      break;
    case 1:
      strl <= 0 ? throw BadMatrix("Invalid rows number given") : tmpl.matrix_.setColumnNumber(strl);
      tmpl.matrix_.arrInit();
      break;
    default:
      tmpl.scounter_ -= 2;
      if (tmpl.scounter_ < tmpl.matrix_.getComps()) {
          unsigned i_d = (tmpl.scounter_ / tmpl.matrix_.getColumsCount());
          unsigned j_d = (tmpl.scounter_ % tmpl.matrix_.getColumsCount());
          tmpl.writeM(i_d, j_d, strl);
      } else {
          throw BadMatrix("Given matrix has too many elements");
      }
      break;
    }
    return ifs;
  }
}

  int main(int argc, char *argv[])
  {
    std::clog << "Each matrix element may be an integer." << std::endl;
    try {
      if (argc - 1 != boikomikhail::exp_arg_count) {
        throw std::invalid_argument("Not enough, or too many arguments(expected 3)");
      };
      if (std::stoi(argv[1]) < 1 || std::stoi(argv[1]) > 2) {
        throw std::invalid_argument("First arg is out of range");
      };
      try {
        std::ifstream m_in(argv[boikomikhail::in_file_argc]);
        std::ofstream m_out(argv[boikomikhail::in_file_argc + 1]);

        if (!m_in.is_open() || !m_out.is_open()) {
          throw std::runtime_error("Failed to open IN/OUT stream for given file(s)");
        }
        std::string *st{new std::string};
        boikomikhail::Matrix matrix{ std::stoi(argv[1]) };
        boikomikhail::TmpList mlist{matrix};
        try {
          for (int i{0}; m_in >> *st; ++i) {
            mlist.setScr(i);
            mlist.setStr(st);
            m_in >> mlist;
          }
          m_out << matrix.getMatrixLocalMin();
        } catch (const std::invalid_argument &e) {
          throw boikomikhail::BadMatrix("Matrix element from given file cannot be stoi to int");
        } catch (const std::out_of_range &e) {
          throw boikomikhail::BadMatrix("Matrix element from given file is out of range(int)");
        };
        delete st;
        m_in.close();
        m_out.close();
      } catch (boikomikhail::BadMatrix &e) {
        std::cerr << e.what() << std::endl;
        return 2;
      }

    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
      return 1;
    }
    return 0;
  }
