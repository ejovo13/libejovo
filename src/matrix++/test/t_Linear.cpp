#include "ejovotest.hpp"

using namespace ejovo;

int main() {

    auto m = Matrix<double>::id(5);

    m.print();

    chol(m).print();

    seq(5).print();

    // m(seq(5)).print();

    m.get_row_view(2, 2, 5).print();

    seq(1, 1).print();

    auto matview = m(seq(2, 5), seq(1, 2));
    matview.print();

    Matrix<double>::MatView matview2 (m, seq(2, 5), seq(1, 2));
    matview2 = 5;

    matview2.to_matrix().print();

    m.get_col_view(3) = 5;
    m.print();
    m.submat(1, 2, 2, 3) = 10;
    m.print();

    std::cout << "matview2.nrow(): " << matview2.nrow() << "\n";
    std::cout << "matview2.ncol(): " << matview2.ncol() << "\n";


    std::cout << "============= Chol gaxpy ==========\n";

    chol_gaxpy(m).print();

    return 0;
}