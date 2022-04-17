#include "Minimum.hpp"

int main() {

    Matrix<double> m (1, 2);
    const Matrix<double> m_const(1, 2);

    std::cout << "Hello world\n";
    std::cout << m[0] << "\n";
    std::cout << m.first() << "\n";
    std::cout << m.last() << "\n";
    std::cout << m_const.first() << "\n";
    std::cout << m_const.last() << "\n";

    // For both const and mutable, we cant access operator()(int i)
    // m(1);          // Error
    // m.at(1);       // Error
    // m_const(1);    // Error
    // m_const.at(1); // Error

    // For both const and mutable, we can access the operator()(int i, int j)
    // defined by Grid2D.
    m(1, 2);
    m_const(1, 2);


    return 0;
}