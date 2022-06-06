#pragma once

#include "types.hpp"

namespace ejovo {

    namespace opti {

    constexpr int MAX_ITERATIONS = 1E5;
    constexpr double EPS = 1E-10;

    // using namespace functions;

    // implement newtons method
    template <class T>
    Matrix<T> newtons_method(std::function<T(T)> f, std::function<T(T)> f_prime, T x0, T eps = EPS, int max_it = MAX_ITERATIONS) {

        // f and f_prime are functions of T
        int i = 0;

        T x = x0;

        while (ejovo::abs(f(x)) > eps && i < MAX_ITERATIONS) {

            x = x - f(x) / f_prime(x);
            i ++;
        }

        Matrix<T> out{1, 1};
        out(1) = x;


        std::cout << "Newton's method run with " << i << " iterations\n";
        out.print();

        return out;
    }

    template <class T, class ScalarFn>
    Matrix<T> fixed_point(ScalarFn g, T x0, T eps = EPS, int max_it = MAX_ITERATIONS) {

        int i = 0;
        T x = x0;
        T err = ejovo::abs(g(x) - x);


        while (err > eps && i < max_it) {

            x = g(x);

            i++;
            err = ejovo::abs(g(x) - x);
        }

        Matrix<T> out (1, 1);
        out(1) = x;

        std::cout << "Fixed point method run with " << i << " iterations\n";

        return out;
    }

    // transform ta,b(x_hat) to change the constrained optimisation problem to an unconstrained problem
    template <class X>
    std::function<X(X)> transform_ab(X a, X b) {
        return [&] (X x_hat) {
            return (b + a) / 2 + ((b - a) / 2) * (2 * x_hat) / (1 + x_hat * x_hat);
        };
    }


    };


};