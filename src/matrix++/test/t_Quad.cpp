#include "ejovotest.hpp"

int main() {


    auto gauss = ejovo::prob::pdf::gauss();


    // Now I want to numerically integrate Gauss.....

    // try between -1 and 1...

    auto p = ejovo::quad::midpoint<double>(-1, 0, gauss, 10000);
    auto pg = ejovo::quad::gauss_legendre<double>(-1, 0, gauss, 10000);


    std::cout << "P(-1 <= X <= 0): " << p << std::endl;
    std::cout << "P(-1 <= X <= 0): " << pg << std::endl;

    std::cout << "P(-1 <= X <= 0): " << ejovo::pnorm(0) - ejovo::pnorm(-1) << std::endl;

    return 0;
}