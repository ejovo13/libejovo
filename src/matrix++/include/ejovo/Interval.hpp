// Contains the Interval class that can be used in conjunction
// with a ScalarFn<T> to study the function's behavior

#pragma once

#include <functional>

#include "types.hpp"
#include "core.hpp"

namespace ejovo {

    template <class T = double>
    class Interval {

    public:

        T a;
        T b;

        Interval(); // default [0, 1]
        Interval(T a, T b);

        void print() const;

        Matrix<T> linspace(int n = 100) const;
        Matrix<T> logspace(int n = 50, T base = 10) const;
        Matrix<T> chebynodes(int n = 10) const;

    private:

        std::function<T(T)> cheby_affine_transformation();

    };

    template <class T>
    Interval<T>::Interval() : a{0}, b{1} {};

    template <class T>
    Interval<T>::Interval(T a, T b) {
        if (a < b) {
            this->a = a;
            this->b = b;
        } else {
            this->a = b;
            this->b = a;
        }
    }

    template <class T>
    void Interval<T>::print() const {
        std::cout << "[" << a << ", " << b << "]\n";
    }

    template <class T>
    Matrix<T> Interval<T>::linspace(int n) const {
        return ejovo::linspace(a, b, n);
    }

    template <class T>
    Matrix<T> Interval<T>::logspace(int n, T base) const {

        if (a <= 0) {
            return Matrix<T>::null();
        }

        std::cout << "Computing logspace for: "; this->print();

        T start_exp = ejovo::log_base(base, a);
        T end_exp   = ejovo::log_base(base, b);

        std::cout << "start_exp: " << start_exp << std::endl;
        std::cout << "end_exp: " << end_exp << std::endl;

        return ejovo::logspace(start_exp, end_exp, n, base);
    }

    template <class T>
    Matrix<T> Interval<T>::chebynodes(int n) const{
        return ejovo::chebynodes(a, b, n);
    }

    template <class T>
    std::function<T(T)> Interval<T>::cheby_affine_transformation() {
        return [&] (T x) {
            return (1 / 2) * (a + b) + (1 / 2) * (b - a) * x;
        };
    }

};

