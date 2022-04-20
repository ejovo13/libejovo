#pragma once

namespace ejovo {

    namespace trig {

    constexpr double pi = 3.14159265358979323846;
    constexpr double two_pi = 2 * 3.14159265358979323846;
    constexpr double half_pi = 3.14159265358979323846 / 2.0;

    template <class T>
    T cos(T x) {
        return std::cos(x);
    }

    template <class T>
    T sin(T x) {
        return std::sin(x);
    }

    template <class T>
    T tan(T x) {
        return std::tan(x);
    }

    }

};