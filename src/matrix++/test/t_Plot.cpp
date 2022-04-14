#include "libejovo.hpp"

int main() {

    using namespace ejovo;

    auto x = linspace<double>(-trig::pi, trig::pi, 1000);
    auto sinx = x.map([&] (auto x) { return sin(x); });
    auto cosx = x.map([&] (auto x) { return cos(x); });
    auto tanx = x.map([&] (auto x) { return tan(x); });

    plot(x, sinx, "sin");
    plot(x, cosx, "cos");
    plot(x, tanx, "tan");

    return 0;
}