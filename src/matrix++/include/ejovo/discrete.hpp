#pragma once

#include "types.hpp"
#include "Interval.hpp"

// Discretization schemes of intervals
namespace ejovo {

    namespace discrete {

        // n is the number of SUBINTERVALS to have | * | * | has n = 2.
        template <class X>
        Matrix<X> midpoints(const X& a, const X& b, int n = 100) {

            if (n <= 0) return Matrix<X>::null();
            if (n == 1) return Matrix<X>::val(1, 1, (b - a) / 2);

            X dx = (b - a) / n;
            return ejovo::linspace(a + (dx / 2), b - (dx / 2), n);

        }

    };

};