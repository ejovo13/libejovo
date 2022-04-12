#include "libejovo.hpp"
// #include "matplot/matplot.h"

#include <cassert>
// #include "sciplot/sciplot.hpp"
// #include "matplot.h"
// #include "matplotlibcpp.h"

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

    auto lin = ejovo::linspace<double>(1, 10);



    std::vector<int> v = {1, 2, 3, 4};

    auto from_v = Matrix<double>::from(v).print();

    from_v.print_lin();

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

    int N = 1E5;

    // auto u = runif(N);
    // auto x = rexp(N, 1);
    // auto n = rnorm(N);

    // u.print_lin();
    // x.print_lin();
    // n.print_lin();

    std::cout << n_choose_k(500, 249) << "\n";

    auto bin = rbinom(N, 10, 0.3).print_lin();

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


    return 0;
}