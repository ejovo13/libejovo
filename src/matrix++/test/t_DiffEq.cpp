#include "libejovo.hpp"
#include <iostream>
#include <fstream>

// I should try and write a routine to compute the zero of a number using newton's method

int main() {

    using namespace ejovo;


    std::cout << "Hello lib\n";

    // Fixed point iteration
    auto f = [] (double x) { return cos(x); };

    // Newton's method
    auto g = [] (double x) { return x - cos(x); };
    auto g_prime = [] (double x) {return sin(x) + 1; };
    double x0 = 1.0;

    auto fp = opti::fixed_point(f, x0);
    auto xs = opti::newtons_method(std::function(g), std::function(g_prime), x0);

    std::cout << "Fixed point := " << fp(1) << std::endl;
    std::cout << "Zero := " << xs(1) << std::endl;


    // use eulers explicit method to find the antiderivative of f2
    double a = -5;
    double b = 3;

    auto f2 = [] (double t, double u) { return u + t; };

    int n = 10000;

    auto ut = ejovo::diffyq::euler_explicit<double>(f2, 0.5, a, b, n);

    // auto sinx = ejovo::linspace(a, b, n).map<double>([&] (auto x) { return x; }).print();

    // ut.print();

    // sinx.print();

    // (sinx - ut).print_lin();

    // pendulum differential equation
    // double g_force = 9.8;
    // double t0 = 0;
    // double tf = trig::two_pi;

    // double L = 5;

    // double gl = g_force / L;


    // auto fu = [&] (double t, const Matrix<double>& u) {
    //     return ejovo::vec<double>({u(2), -(g_force / L) * u(1)});
    // };

    // auto out = ejovo::diffyq::euler_explicit<double>(std::function(fu), ejovo::vec<double>({0, 0}), t0, tf, 10);

    // out.print();

    // ejovo::vec<int>({1, 2, 3}, false).print();
    // ejovo::vec<int>({1, 2, 3}).print();

    // Today we implemented some basic gradient_descent methods.


    // Test out generating and executing R code

    auto x = ejovo::linspace(-10, 4);
    auto y = x.map([&] (auto x) { return exp(x);});


    // write a CSV from a DataFrame type object
    // ejovo::plot

    auto df = ejovo::df({x, y}, {"x", "y"});

    // df.to_csv("test.csv");

    // ejovo::plot(x, y);


    // myfile.close();

    // x.print();


    auto t = ejovo::linspace(a, b, n);

    // ejovo::plot(t, ut, "diff");
    // ejovo::plot(x, y, "exp");




    return 0;
}

