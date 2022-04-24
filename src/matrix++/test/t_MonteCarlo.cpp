#include "ejovotest.hpp"

int main() {


    auto fx = [&] (auto x) { return x * x; };

    std::cout << "Int(fx; 0, 2): " << ejovo::monte_carlo::integrate_unif(1000000, fx, 0, 2) << std::endl;
    std::cout << "Int(fx; 0, 2): " << ejovo::monte_carlo::integrate_norm_bounded(1000000, fx, 0, 2) << std::endl;


    auto f = [&] (double x) { return std::exp(- x * x); };

    std::cout << "Int(exp(-x^2)): " << ejovo::monte_carlo::integrate_norm(1000000, f) << std::endl;
    std::cout << "sqrt(pi): " << sqrt(ejovo::trig::pi) << "\n";

    return 0;
}