#pragma once

// This file contains functions that operator on functions and also those that adopt a functional approach to
// programming like the map and filter functions

#include <functional>

#include "declarations/Matrix.hpp"


// Let's get crazy and start overloading function operators!!!
/**========================================================================
 *!                           binop(f, g)
 *========================================================================**/
template <class X, class Y>
std::function<Y(const X&)> operator+(std::function<Y(const X&)> f, std::function<Y(const X&)> g) {
    return [&] (const X& x) {
        return f(x) + g(x);
    };
}

template <class X, class Y>
std::function<Y(const X&)> operator-(std::function<Y(const X&)> f, std::function<Y(const X&)> g) {
    return [&] (const X& x) {
        return f(x) - g(x);
    };
}

template <class X, class Y>
std::function<Y(const X&)> operator*(std::function<Y(const X&)> f, std::function<Y(const X&)> g) {
    return [&] (const X& x) {
        return f(x) * g(x);
    };
}

template <class X, class Y>
std::function<Y(const X&)> operator/(std::function<Y(const X&)> f, std::function<Y(const X&)> g) {
    return [&] (const X& x) {
        return f(x) / g(x);
    };
}

/**========================================================================
 *!                           binop(f, scalar)
 *========================================================================**/
template <class X, class Y>
std::function<Y(const X&)> operator+(std::function<Y(const X&)> f, const Y& y) {
    return [&] (const X& x) {
        return f(x) + y;
    };
}

template <class X, class Y>
std::function<Y(const X&)> operator+(const Y& y, std::function<Y(const X&)> f) {
    return [&] (const X& x) {
        return y + f(x);
    };
}

template <class X, class Y>
std::function<Y(const X&)> operator-(std::function<Y(const X&)> f, const Y& y) {
    return [&] (const X& x) {
        return f(x) - y;
    };
}

template <class X, class Y>
std::function<Y(const X&)> operator-(const Y& y, std::function<Y(const X&)> f) {
    return [&] (const X& x) {
        return y - f(x);
    };
}

template <class X, class Y>
std::function<Y(const X&)> operator*(std::function<Y(const X&)> f, const Y& y) {
    return [&] (const X& x) {
        return f(x) * y;
    };
}

template <class X, class Y>
std::function<Y(const X&)> operator*(const Y& y, std::function<Y(const X&)> f) {
    return [&] (const X& x) {
        return y * f(x);
    };
}

template <class X, class Y>
std::function<Y(const X&)> operator/(std::function<Y(const X&)> f, const Y& y) {
    return [&] (const X& x) {
        return f(x) / y;
    };
}

template <class X, class Y>
std::function<Y(const X&)> operator/(const Y& y, std::function<Y(const X&)> f) {
    return [&] (const X& x) {
        return y / f(x);
    };
}

// m | ejovo::pipe::filter( lt(10) );
template <class X>
typename ejovo::Matrix<X>::VecView operator|(ejovo::Matrix<X>& lhs, std::function<bool(X)> pred) {
    typename ejovo::Matrix<X>::VecView out (lhs, pred);
    return out;
}

template <class X>
typename ejovo::Matrix<X>::VecView operator|(typename ejovo::Matrix<X>::VecView& lhs, std::function<bool(X)> pred) {
    // loop through the lhs extracting the elements that are true.
    ejovo::Matrix<int> new_ind = lhs.filter(pred);

}


/**========================================================================
 *!                           Boolean Function Operators
 *========================================================================**/
// Boolean function operators!!!!!
template <class X>
std::function<bool(const X&)> operator&&(std::function<bool(const X&)> f, std::function<bool(const X&)> g) {
    return [&] (const X& x) {
        return f(x) && g(x);
    };
}

template <class X>
std::function<bool(const X&)> operator||(std::function<bool(const X&)> f, std::function<bool(const X&)> g) {
    return [&] (const X& x) {
        return f(x) || g(x);
    };
}

template <class X>
std::function<bool(const X&)> operator!(std::function<bool(const X&)> f) {
    return [&] (const X& x) {
        return !f(x);
    };
}

namespace ejovo {

    namespace functional {


    template <class T>
    T id(T x) {
        return x;
    }

    template <class T>
    class ScalarFn {

        public:

        // a scalar function takes a t and returns a t
        ScalarFn();
        ScalarFn(std::function<T(T)> fn);

        T operator()(T x) {
            return fn(x);
        }

        Matrix<T> operator()(Matrix<T> x) {
            return ejovo::map(x, fn);
        }

        private:

        std::function<T(T)> fn;
    };

    template <class T>
    ScalarFn<T>::ScalarFn(): fn{id<T>} {};

    template <class T>
    ScalarFn<T>::ScalarFn(std::function<T(T)> __fn) : fn{__fn} {};

    // return f o g, such that
    // f: Y -> Z
    // g: X -> Y
    // f o g : X -> Z
    template <class X, class Y, class Z>
    std::function<Z(X)> comp(std::function<Z(Y)> f, std::function<Y(X)> g) {
        return [&] (X x) {
            return f(g(x));
        };
    }

    };


};