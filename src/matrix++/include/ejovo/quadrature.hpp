// Routines to numerically compute Integrals
#pragma once

#include "types.hpp"
#include "Interval.hpp"
#include "discrete.hpp"

namespace ejovo {

    namespace quad {


    // Accept a single variate (double?) function and compute its integral over an interval

    // In this case a discretization is anything that is iterable... -> Eventually I could be using concepts here
    template <class X, class Y>
    Y midpoint(const X& a, const X& b, std::function<Y(X)> fn, int n = 100) {
        // Discretize the interval into n sub intervals
        if (n == 1) {
            X dx = b - a;
            X xi = (b - a) / 2;
            return dx * fn(xi);
        }

        Matrix<X> interv = ejovo::discrete::midpoints(a, b, n); // equdistant intervals
        X dx = interv(2) - interv(1);

        return dx * ejovo::sum(interv.map(fn));
    }


    // once again, n is the number of subproblems that this is divided into
    template <class X, class Y>
    Y trapezoid(const X& a, const X& b, std::function<Y(X)> fn, int n = 100) {

        // for n intervals, I need n + 1 points.
        if (n <= 0) return nan("");
        if (n == 1) return 0.5 * (fn(a) + fn(b)) / (b - a);

        Matrix<X> interv = ejovo::linspace(a, b, n + 1);
        X dx = interv(2) - interv(1);

        X left = fn(interv(1));
        X right = fn(interv(n + 1));
        X mid = interv(ejovo::seq(2, n)).map(fn).sum();

        return (dx / 2) * (left + 2 * mid + right);
    }

    template <class X, class Y>
    Y simpson(const X& a, const X& b, std::function<Y(X)> fn, int n = 100) {





    }

    template <class X, class Y>
    Y gauss_legendre(const X& a, const X& b, std::function<Y(X)> fn, int n = 100) {

        // Let's implement a 5 point method!!!
        double dx = (b - a) / n;

        double x0_off = 0;
        double x12_off = 0.538469310105683 * (dx / 2.0); // if dx = 2 ([-1, 1]), we want x1 to end up at 0.53846931
        double x34_off = 0.906179845938664 * (dx / 2.0);

        double w0 = 0.568888888888889;
        double w12 = 0.478628670499366;
        double w34 = 0.236926885056189;

        if (n == 1) {
            auto x0 = (b + a) / 2;
            auto x1 = x0 + x12_off;
            auto x2 = x0 - x12_off;
            auto x3 = x0 + x34_off;
            auto x4 = x0 - x34_off;

            return 0.5 * dx * (w0 * fn(x0) + w12 * (fn(x1) + fn(x2)) + w34 * (fn(x3) + fn(x4)));
        }

        // Get the midpoints, and the offsets.

        // I could be more efficient and only store X0, applying the same function on
        // all of the points
        auto X0 = ejovo::linspace(a + dx / 2.0, b - dx / 2.0, n);
        auto X1 = X0 + x12_off;
        auto X2 = X0 - x12_off;
        auto X3 = X0 + x34_off;
        auto X4 = X0 - x34_off;

        // Apply the function in place, not duplicating the X variables.
        X0.mutate(fn);
        X1.mutate(fn);
        X2.mutate(fn);
        X3.mutate(fn);
        X4.mutate(fn);

        return 0.5 * dx * (w0 * X0.sum() + w12 * (X1.sum() + X2.sum()) + w34 * (X3.sum() + X4.sum()));

    }

    template <class X, class Y>
    Y gauss_legendre_2(const X& a, const X& b, std::function<Y(X)> fn, int n = 100) {

        // Implementation of 2 point method

        double dx = (b - a) / n;
        double x01_off = (1.0 / sqrt(3.0)) * (dx / 2.0);

        // Get the midpoints, and the offsets.
        if (n == 1) {
            auto mid = (b + a) / 2;
            auto x0 = mid + x01_off;
            auto x1 = mid - x01_off;

            return 0.5 * dx * (fn(x0) + fn(x1));
        }

        // I could be more efficient and only store X0, applying the same function on
        // all of the points
        auto mid = ejovo::linspace(a + dx / 2.0, b - dx / 2.0, n);

        auto X0 = mid + x01_off;
        auto X1 = mid - x01_off;

        // Apply the function in place, not duplicating the X variables.
        X0.mutate(fn);
        X1.mutate(fn);

        return 0.5 * dx * (X0.sum() +  X1.sum());

    }

    // different implementations of the error function
    namespace erf {

        template <int N = 1000>
        double midpoint(double x) {
            constexpr double coeff = 2.0 / std::sqrt(trig::pi);
            double trap = ejovo::quad::midpoint<double, double>(0,
                                    x,
                                    [&] (double x) { return std::exp(- (x * x)); },
                                    N);
            return coeff * trap;
        }

        template <int N = 1000>
        double trapezoid(double x) {
            constexpr double coeff = 2.0 / std::sqrt(trig::pi);
            double trap = ejovo::quad::trapezoid<double, double>(0,
                                        x,
                                        std::function<double(double)>([&] (double x) { return std::exp(- (x * x)); }),
                                        N);
            return coeff * trap;
        }

        template <int N = 1000>
        double gausslegendre(double x) {
            constexpr double coeff = 2.0 / std::sqrt(trig::pi);

            double trap = ejovo::quad::gauss_legendre<double, double>(0,
                                                x,
                                                std::function<double(double)>([&] (double x) { return std::exp(- (x * x)); }),
                                                N);


            return coeff * trap;
        }

        template <int N = 1000>
        double gausslegendre_2(double x) {
            constexpr double coeff = 2.0 / std::sqrt(trig::pi);

            double trap = ejovo::quad::gauss_legendre_2<double, double>(0,
                                                x,
                                                std::function<double(double)>([&] (double x) { return std::exp(- (x * x)); }),
                                                N);


            return coeff * trap;
        }

    };


    // // Use different quadrature rules to approximate the value of the error function
    // template <int N = 1000>
    // double erf(double x) {
    //     return ejovo::erf::gausslegendre<N>(x);
    // }


    };

};