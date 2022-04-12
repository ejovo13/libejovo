#include "libejovo.hpp"

// I should try and write a routine to compute the zero of a number using newton's method

int main() {

    using namespace ejovo;

    // Matrix<

    std::cout << "Hello lib\n";


    auto f = [] (double x) { return cos(x); };
    auto g = [] (double x) { return x - cos(x);};
    auto g_prime = [] (double x) {return sin(x) + 1;};

    auto fp = opti::fixed_point(f, 0.5);
    auto xs = opti::newtons_method(std::function(g), std::function(g_prime), 1.0);

    std::cout << "Fixed point := " << fp(1) << std::endl;
    std::cout << "Zero := " << xs(1) << std::endl;

    // std::cout <<

    auto mr = Matrix<double>::rand(2, 10);
    mr.print();

    mr(seq(2), 2).print();

    mr(seq(2), 3) = 0;

    auto mv = mr(seq(2), 3);

    std::cout << mv(1) << std::endl;
    std::cout << mv(2) << std::endl;
    std::cout << mv(3) << std::endl;
    std::cout << mv(4) << std::endl;

    mr.print();


    // use eulers explicit method to find the antiderivative of cos(x)
    // auto co = [] (double x) { return c}


    double a = 0;
    double b = trig::two_pi;

    auto f2 = [] (double t, double u) { return cos(t); };

    int n = 10000;

    auto ut = ejovo::diffyq::euler_explicit<double>(f2, 0, a, b, n);

    auto sinx = ejovo::linspace(a, b, n).map<double>([&] (auto x) { return sin(x); }).print();

    // ut.print();

    sinx.print();

    (sinx - ut).print_lin();

    // pendulum differential equation
    double g_force = 9.8;
    double t0 = 0;
    double tf = trig::two_pi;

    double L = 5;

    // double gl = g_force / L;


    auto fu = [&] (double t, const Matrix<double>& u) {
        return ejovo::vec<double>({u(2), -(g_force / L) * u(1)});
    };

    auto out = ejovo::diffyq::euler_explicit<double>(std::function(fu), ejovo::vec<double>({0, 0}), t0, tf, 10);

    out.print();

    ejovo::vec<int>({1, 2, 3}, false).print();
    ejovo::vec<int>({1, 2, 3}).print();

    return 0;
}