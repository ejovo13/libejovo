#include "libejovo.hpp"

int main() {

    using namespace ejovo;

    auto x = linspace<double>(-trig::pi, trig::pi, 1000);
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
    // auto xi = linspace<double>(-3, 3);
    // auto yi = xi.map([&] (auto x) { return x * x - 3;} );

    // plot(xi, yi, "fx.png");


    auto norm_pdf = ejovo::prob::pdf::gauss();

    x = linspace<double>(-4, 4, 100);
    auto y = x.map(norm_pdf);

    // y.print();

    plot(x, y, "Normal_Distribution");

    return 0;
}