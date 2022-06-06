#include "libejovo.hpp"

int main() {

    using namespace ejovo;

    auto x = linspace(-trig::pi, trig::pi, 1000);
    auto sinx = x.map([&] (auto x) { return sin(x); });
    // auto cosx = x.map([&] (auto x) { return cos(x); });
    // auto tanx = x.map([&] (auto x) { return tan(x); });

    // plot(x, sinx, "sin");
    // plot(x, cosx, "cos");
    // plot(x, tanx, "tan");

    auto rudio = x.map([&] (auto x) {return x + 1;});

    // plot(x, rudio, "Rudio");


    // auto filt = x.filter([&] (auto x) { return x < 0; } );
    // filt.print();
    // auto xi = linspace(-3, 3);
    // auto yi = xi.map([&] (auto x) { return x * x - 3;} );

    // plot(xi, yi, "fx.png");


    auto norm_pdf = ejovo::prob::pdf::gauss();

    x = linspace(-4, 4, 100);
    auto y = x.map(norm_pdf);

    // y.print();

    plot(x, y, "Normal_Distribution");

    auto h_x = [&] (double x) {
        return x * sin(x);
    };

    double a = 2;
    double b = 6;

    auto t_ab = opti::transform_ab(a, b);

    x = linspace(0, 15);
    y = x.map(h_x);

    auto f_t_x = functional::comp(std::function<double(double)>(h_x), t_ab);

    auto long_x = linspace(-10, 10, 200);

    double ftx = f_t_x(0);

    std::cout << "ftx(0): " << ftx;
    auto long_y = long_x.map(t_ab);

    plot(x, y, "xsinx");
    plot(long_x, long_y, "t_26");


    return 0;
}