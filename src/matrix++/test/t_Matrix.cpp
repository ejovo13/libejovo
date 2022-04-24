#include "ejovotest.hpp"
// #include "sciplot/sciplot.hpp"
// #include "matplot.h"
// #include "matplotlibcpp.h"

using namespace ejovo;

void t_quad();

int main() {

    auto m = Matrix<double>::ij(4, 8);

    m.print();

    auto b = m > 5;

    b.print();

    std::cout << b.sum<int>() << std::endl;
    std::cout << b.count() << "\n";

    std::cout << (! (m > 5)).count() << std::endl;

    std::cout << m.count([&] (auto x) {
        return x <= 5;
    }) << "\n";

    auto pred = [&] (double x) {
        return x > 5;
    };

    // using namespace ejovo;
    using namespace ejovo::factory;

    std::cout << m.count(pred) << std::endl;
    std::cout << m.count(NOT<double>(pred)) << std::endl;

    std::cout << m.count(OR<double>(lt(5), gt(10))) << std::endl;

    m.print();

    auto pred11 = [&] (double x) {
        return x > 11;
    };

    std::cout << m.all() << std::endl;
    std::cout << m.any() << std::endl;

    std::cout << m.any(gt(10)) << std::endl;
    std::cout << m.any(gt(11)) << std::endl;

    m.where(lt(10)).print();

    // m[ m < 10 ] = 1;
    // m[ m.where(geq(10)) ] = 0;

    // m.print();

    m.which(geq(10)).print();

    auto lin = ejovo::linspace(1, 10);



    std::vector<int> v = {1, 2, 3, 4};

    auto from_v = Matrix<double>::from(v).print();

    // from_v.summary();
    from_v.summary();
    // using namespace matplot;

    // std::vector<double> x = matplot::linspace(-trig::pi, trig::pi);
    // std::vector<double> y = ejovo::map<double>(x, [] (auto __x) { return cos(__x); });



    // matplot::plot(x, y, "-o");

    // matplot::plot(y);

    // matplot::to

    //====================== Sciplot testing ====================
    // using namespace sciplot;
    // Plot plot;
    // Vec x = linspace(0.0, PI, 200);
    // plot.drawCurve(x, std::sin(1.0 * x)).label("sin(x)");
    // plot.drawCurve(x, std::sin(2.0 * x)).label("sin(2x)");
    // plot.show();
    // ==================== Sciplot testing =====================

    using namespace ejovo;

    // ejovo::rng::Xoshiro x{};


    // std::cout << "next: " << x.next() << std::endl;

    // x.seed(1, 2, 3, 4);

    // std::cout << "next: " << x.next() << std::endl;

    auto my_x = ejovo::runif(10);
    my_x.print();

    my_x = ejovo::runif(0).print();

    int N = 1E3;

    // auto u = runif(N);
    // auto x = rexp(N, 1);
    // auto n = rnorm(N);

    // u.summary();
    // x.summary();
    // n.summary();

    std::cout << n_choose_k(500, 249) << "\n";

    auto bin = rbinom(N, 10, 0.3).summary();

    auto bin_p = seq(0, 10).map<double>([&] (auto k) {
        return dbinom(k, 10, 0.3);
    });

    bin_p.print();
    bin_p.cumsum().print();

    auto my_seq = seq<double>(10);

    my_seq.print();
    my_seq.cumavg().print();
    my_seq.cummax().print();
    my_seq.cummin().print();

    // std::cout << dhyper();
    std::cout << dhyper(1, 1, 2, 1) << "\n";

    auto my_hyper = rhyper(10, 8, 10, 5);

    my_hyper.print();

    auto my_hyper_1000 = rhyper(10000, 8, 10, 5);
    my_hyper_1000.summary();

    t_quad();


    return 0;
}

void t_quad() {


    double a = 0;
    double b = 1;

    auto interv = ejovo::discrete::midpoints(a, b);

    interv.print();

    auto f = [&] (double x) {
        return x;
    };

    auto F = [&] (double x) {
        return (x * x) / 2;
    };

    std::cout << "F(b) - F(a) -> " << F(b) - F(a) << "\n";
    // std::cout << "quad::midpoint(a, b, f, 1) -> " << ejovo::quad::midpoint<double, double>(a, b, f, 1) << "\n";

    // for (int i = 1; i <= 100; i++) {

    //     std::cout << "quad::midpoint(a, b, f, " << i << ") -> " << ejovo::quad::midpoint<double, double>(a, b, f, i) << "\n";
    // }


    std::cout << "quad::trapezoid(a, b, f, " << 1 << ") -> " << ejovo::quad::trapezoid<double, double>(a, b, f, 1) << "\n";
    std::cout << "quad::trapezoid(a, b, f, " << 2 << ") -> " << ejovo::quad::trapezoid<double, double>(a, b, f, 2) << "\n";
    std::cout << "quad::trapezoid(a, b, f, " << 3 << ") -> " << ejovo::quad::trapezoid<double, double>(a, b, f, 3) << "\n";

    ejovo::discrete::midpoints(a, b, 1).print();
    ejovo::discrete::midpoints(a, b, 2).print();

    auto fx = std::function<double(const double&)>([&] (double x) {
        return x;
    });

    double k = 5;

    auto g = fx + k;

    std::cout << g(10) << std::endl;

    Matrix<double>::rand().print();
    // auto mx = Matrix<double>::rand(10);

    // auto mv =

    ejovo::runif(100).summary();
    Matrix<double>::rand(100).summary();

    Matrix<int>::rand(10, 10).print();

    auto m = Matrix<int>::rand(10, 10);

    using namespace ejovo::factory;

    // auto mv = m | lt<int>(10) | gt<int>(3);
    auto mv = m | AND(lt<int>(10), gt<int>(5));

    auto mvp = m.vecview(AND(gt(10), even<int>));

    // auto mv_f = mv.filter(gt<int>(5));
    mv.print();
    mvp.print();

    // m.print();
    // mv.print();

}