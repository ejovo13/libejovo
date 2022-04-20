#pragma once

// Namespace for differential equations and their solutions
#include "types.hpp"

namespace ejovo {

    namespace diffyq {


        // Use euler's method for differential equations
        // need the function, need an initial condition

        // f_tu = [] (double t, double u) { return cos(t); }; // dy/dt = cos(t), u(t) = sin(t)

        template <class X>
        // using X so that we can pass a vector in as an argument
        Matrix<X> euler_explicit(std::function<X(double, X)> f, X u0, double t0, double tf, int n = 1000) {

            //
            auto time = ejovo::linspace(t0, tf, n);
            auto diffs = time.diff();

            Matrix<X> u (1, n);
            u(1) = u0;

            // u.rows({1}, 2).print();
            // u.get_row_view(1, 1, 4).print();

            u.rows({1}, 2).loop_i([&] (int i) {
                u(i + 1) = u(i) + diffs(i) * f(time(i), u(i));
            });

            return u;

        }

        template <class X>
        // using X so that we can pass a vector in as an argument
        Matrix<X> euler_explicit(std::function<Matrix<X>(double, Matrix<X>)> f, Matrix<X> u0, double t0, double tf, int n = 1000) {

            //
            auto time = ejovo::linspace(t0, tf, n);
            auto diffs = time.diff();

            Matrix<X> u (u0.size(), n);
            u.cols({1}) = u0.reshape_col();

            std::cerr << "u0 set to: ";
            u.cols({1}).print();

            // u.rows({1}, 2).print();
            // u.get_row_view(1, 1, 4).print();

            u.rows({1}, 2).loop_i([&] (int i) {
                u.cols({i + 1}) = u.col(i) + diffs(i) * f(time(i), u.col(i));
            });

            return u;

        }




    };



};