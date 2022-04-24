#include "ejovotest.hpp"

bool feq(double x, double y, double eps = 1E-10) {
    return (abs(x - y) < eps);
}

void t_gauss_2();

using fn = std::function<double (double)>;

int main() {


    auto gauss = ejovo::prob::pdf::gauss();


    // Now I want to numerically integrate Gauss.....

    // try between -1 and 1...

    auto p = ejovo::quad::midpoint<double>(-1, 0, gauss, 10000);
    auto pg = ejovo::quad::gauss_legendre<double>(-1, 0, gauss, 2);
    auto pg2 = ejovo::quad::gauss_legendre_2<double>(-1, 0, gauss, 2);


    std::cout << "P(-1 <= X <= 0): " << p << std::endl;
    std::cout << "P(-1 <= X <= 0): " << pg << std::endl;
    std::cout << "P(-1 <= X <= 0): " << pg2 << std::endl;

    std::cout << "P(-1 <= X <= 0): " << ejovo::pnorm(0) - ejovo::pnorm(-1) << std::endl;

    t_gauss_2();

    return 0;
}

// With 2 points, we expect the computation of integrals to be EXACT for polynomials of degree 2(n - 1)
void t_gauss_2() {

    auto x = [&] (double x) { return x; };
    auto xsq = [&] (double x) { return x * x; };
    auto xcb = [&] (double x) { return x * x * x; };
    auto xfrth = [&] (double x) { return x * x * x * x; };
    auto xfifth = [&] (double x) { return x * x * x * x * x; };

    auto Fx = [&] (double x) { return xsq(x) / 2.0; };
    auto Fsq = [&] (double x) { return (xcb(x) / 3.0); };
    auto Fcb = [&] (double x) { return (xfrth(x) / 4.0); };
    auto Ffrth = [&] (double x) { return (xfifth(x) / 5.0); };

    double a = -1.0;
    double b = 1.0;

    auto gauss2 = ejovo::quad::gauss_legendre_2<double, double>;


    std::cout << "Gauss2(x): " << gauss2(a, b, x, 1) << "\n";
    std::cout << "Fx(" << b << ") - Fx(" << a << "): " << Fx(b) - Fx(a) << "\n";
    std::cout << "======================================\n";
    std::cout << "Gauss2(x**2): " << gauss2(a, b, xsq, 1) << "\n";
    std::cout << "Fsq(" << b << ") - Fsq(" << a << "): " << Fsq(b) - Fsq(a) << "\n";
    std::cout << "======================================\n";

    assert(feq(gauss2(a, b, xsq, 1), Fsq(b) - Fsq(a)));
    assert(feq(gauss2(a, b, xsq, 2), Fsq(b) - Fsq(a)));
    assert(feq(gauss2(a, b, xsq, 5), Fsq(b) - Fsq(a)));
    assert(feq(gauss2(a, b, xsq, 10), Fsq(b) - Fsq(a)));



    // assert()



}


