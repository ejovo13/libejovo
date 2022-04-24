#include "libejovo.hpp"
#include "ejovotest.hpp"


// Playing around with concepts
namespace ejovo {

template <class T>
concept Cloneable = requires (const Grid1D<T>& grid) {
    // {grid.clone()} -> std::same_as<Matrix<T>>;
    grid.clone();
};

template <class T>
concept Zeroed = requires (T t, int m, int n) {
    t.zeros(m, n);
};

template <class T>
concept Printable = requires (T t) {
    t.print();
};


template <class T>
concept PrintCloneable = Cloneable<T> && Printable<T>;

template <class T>
concept Reproducible = Cloneable<T> && Zeroed<T>;


void printClone(Cloneable auto m) {
    printf("Calling printClone\n");
    m.clone().print();
}

    namespace conc {









    };



};


int main() {

    using namespace ejovo;
    using namespace ejovo::factory;

    std::cout << "Hello Ejovo\n";

    auto m = ejovo::seq<double>(10.0);

    auto mrand = Matrix<double>::rand(4, 5, -10, 10);

    m.print();
    m.map(times(2)).print();

    m.sqrd().print();

    mrand.print();

    mrand.abs().print();
    mrand.diff().print();

    auto mm = Matrix<double>::from({1, 2, 3, 4}, 2, 2);
    mm.print();

    m.sqrt().print();
    m.sqrd().print();

    m.cbrt().print();
    m.cubd().print();

    m.repcol(10).print();
    m.reprow(10).print();

    std::cout << "Dot product:" << m.repcol(10).dot(m.reprow(10)) << std::endl;

    m.outer_product(m).print();

    m.repcol(10).hadamard_product(m.reprow(10)).print();

    m.hadamard_product(m).print();

    seq(2.5, 3.3, 0.1).print();

    seq(3, 385, 23).print();
    seq(233, 3, -23).print();
    // seq(233, 3, 23).print(); // This throws an error

    seq(3, 285, 15.3).print();
    linspace(1, 2, 40).print();

    // auto x = linspace(-20, 20, 2000);

    // auto cosx = ejovo::cos(x);
    // auto sinx = ejovo::sin(x);
    // auto tanx = ejovo::tan(x);

    // cosx.print();
    // sinx.print();
    // tanx.print();

    // ejovo::plot(x, sinx);

    // auto gauss = ejovo::prob::pdf::gauss();

    // ejovo::plot(x, x.map(gauss), "norm");

    // std::cout << "erf(0): " << ejovo::prob::erf(0) << std::endl;
    // std::cout << "erf(5): " << ejovo::prob::erf(5) << std::endl;
    // std::cout << "quad_erf(0): " << ejovo::quad::erf<50>(0) << std::endl;
    // std::cout << "quad_erf(5): " << ejovo::quad::erf<50>(5) << std::endl;

    // auto x = linspace(-20, 20, 1000);
    // plot(x, x.map(ejovo::prob::erf), "pade_err");

    // plot(x, x.map(ejovo::quad::erf), "quad_err");

    auto x = linspace(-5, 5, 500);
    // auto y = x.map(ejovo::pnorm);

    // plot(x, y, "pnorm");

    // y.print();

    // x = linspace(.05, 3, 100);
    // auto expx = ejovo::exp(x);
    // auto logx = ejovo::log(x);
    // auto logexp = ejovo::log(ejovo::exp(x));

    // plot(x, expx, "expx");
    // plot(x, logx, "logx");
    // plot(x, logexp, "log_exp_x");

    // x = linspace(-4, 4, 200);

    // plot(x, ejovo::sinh(x), "sinh");
    // plot(x, ejovo::cosh(x), "cosh");
    // plot(x, ejovo::tanh(x), "tanh");
    // std::cout << "Calculating the x to the third power";
    // x = linspace(1, 4, 8);
    // pow(x, 3).print();

    // x = seq<double>(5);
    // x.midpoints().print();

    // auto f = [&] (auto x) { return x; };

    // double a = 0;
    // double b = 5;

    // std::cout << "Int(f): " << ejovo::quad::gauss_legendre(a, b, std::function<double(double)>(f), 10);


    // // test difference between erf implementations
    // // get true error function value.
    // x = linspace(-4, 4, 100);
    x = linspace(-4, 4, 100);

    auto gl = x.map(ejovo::pnorm);
    auto gl2 = x.map(ejovo::pnorm_2);
    auto mid = x.map(ejovo::pnorm_mid);

    // ejovo::plot(x, gl);

    printf("\nGauss legendre pnorm: \n");
    gl.print();

    printf("\nGauss legendre2 pnorm: \n");
    gl2.print();

    printf("Midpoint pnorm:\n");
    mid.print();

    auto g = [&] (auto x) {return 7 * std::pow(x, 3) - 8 * x * x - 3 * x + 3; };

    std::cout << g(-sqrt(1.0/3)) + g(sqrt(1.0/3)) << "\n";


    std::cout << "Int(g): " << ejovo::quad::gauss_legendre_2(-1.0, 1.0, std::function<double(double)>(g), 2);

    auto erfx = get_erf_matlab();

    erfx.summary();

    x = linspace(-3, 3, 1000);
    // x = chebynodes()

    auto erf_mid_100 = x.map(ejovo::quad::erf::midpoint<100>);
    auto erf_mid_200 = x.map(ejovo::quad::erf::midpoint<200>);
    auto erf_mid_300 = x.map(ejovo::quad::erf::midpoint<300>);

    auto erf_gauss_1 = x.map(ejovo::quad::erf::gausslegendre<1>);
    auto erf_gauss_2 = x.map(ejovo::quad::erf::gausslegendre<2>);
    auto erf_gauss_10 = x.map(ejovo::quad::erf::gausslegendre<10>);
    auto erf_gauss_50 = x.map(ejovo::quad::erf::gausslegendre<50>);
    auto erf_gauss_100 = x.map(ejovo::quad::erf::gausslegendre<100>);
    auto erf_gauss_200 = x.map(ejovo::quad::erf::gausslegendre<200>);
    auto erf_gauss_300 = x.map(ejovo::quad::erf::gausslegendre<300>);

    auto erf_gauss2_1 = x.map(ejovo::quad::erf::gausslegendre_2<1>);
    auto erf_gauss2_2 = x.map(ejovo::quad::erf::gausslegendre_2<2>);
    auto erf_gauss2_3 = x.map(ejovo::quad::erf::gausslegendre_2<3>);
    auto erf_gauss2_4 = x.map(ejovo::quad::erf::gausslegendre_2<4>);
    auto erf_gauss2_5 = x.map(ejovo::quad::erf::gausslegendre_2<5>);
    auto erf_gauss2_100 = x.map(ejovo::quad::erf::gausslegendre_2<100>);
    auto erf_gauss2_200 = x.map(ejovo::quad::erf::gausslegendre_2<200>);
    auto erf_gauss2_300 = x.map(ejovo::quad::erf::gausslegendre_2<300>);



    // (erfx - erf_mid_100).summary();
    // (erfx - erf_mid_200).summary();
    // (erfx - erf_mid_300).summary();

    std::cout << "Norm(erf - erf_gauss_1): " << (erfx - erf_gauss_1).norm() << std::endl;
    std::cout << "Norm(erf - erf_gauss_2): " << (erfx - erf_gauss_2).norm() << std::endl;
    std::cout << "Norm(erf - erf_gauss_10): " << (erfx - erf_gauss_10).norm() << std::endl;
    std::cout << "Norm(erf - erf_gauss_50): " << (erfx - erf_gauss_50).norm() << std::endl;
    std::cout << "Norm(erf - erf_gauss_100): " << (erfx - erf_gauss_100).norm() << std::endl;
    std::cout << "Norm(erf - erf_gauss_200): " << (erfx - erf_gauss_200).norm() << std::endl;
    std::cout << "Norm(erf - erf_gauss_300): " << (erfx - erf_gauss_300).norm() << std::endl;

    std::cout << "Norm(erf - erf_gauss2_1): " << (erfx - erf_gauss2_1).norm() << std::endl;
    std::cout << "Norm(erf - erf_gauss2_2): " << (erfx - erf_gauss2_2).norm() << std::endl;
    std::cout << "Norm(erf - erf_gauss2_3): " << (erfx - erf_gauss2_3).norm() << std::endl;
    std::cout << "Norm(erf - erf_gauss2_4): " << (erfx - erf_gauss2_4).norm() << std::endl;
    std::cout << "Norm(erf - erf_gauss2_5): " << (erfx - erf_gauss2_5).norm() << std::endl;
    std::cout << "Norm(erf - erf_gauss2_100): " << (erfx - erf_gauss2_100).norm() << std::endl;
    std::cout << "Norm(erf - erf_gauss2_200): " << (erfx - erf_gauss2_200).norm() << std::endl;
    std::cout << "Norm(erf - erf_gauss2_300): " << (erfx - erf_gauss2_300).norm() << std::endl;

    std::cout << "Norm(erf - erf_mid_100): " << (erfx - erf_mid_100).norm() << std::endl;
    std::cout << "Norm(erf - erf_mid_200): " << (erfx - erf_mid_200).norm() << std::endl;
    std::cout << "Norm(erf - erf_mid_300): " << (erfx - erf_mid_300).norm() << std::endl;

    // linspace(1, 30).print();


    // auto fn = [&] (double x, double y) { return x * x + y * x - 3 * y; };
    // auto fn = [&] (double x, double y) { return (1 - x) * (1 - x) + 10 * (y - x * x) * (y - x * x); };
    // auto fn = [&] (double x, double y) { return x * x + y * y; };
    // auto fn = [&] (double x, double y) { return (x - 0.5) * x + x * (y + 0.75) * (y - 0.75); };
    // From TP5
    // auto fn = [&] (double x, double y) { return (x - 4) * (x - 4) + 2 * (y - 3) * (y - 3) + x * y; };

    // const auto& [xx, yy] = meshgrid(linspace(1, 4, 50)); // sweet new syntax
    // contour(xx, yy, std::function<double (double, double)>(fn), "tp5", "seq(7.5, 18, 1.5)", 8, 7);
    // contour(xx, yy, std::function<double (double, double)>(fn), "circle", "log( * seq(-1, 10, 0.3))");


    return 0;
}