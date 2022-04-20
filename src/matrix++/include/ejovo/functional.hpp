#pragma once

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
    typename Matrix<X>::VecView out (lhs, pred);
    return out;
}

template <class X>
typename ejovo::Matrix<X>::VecView operator|(typename ejovo::Matrix<X>::VecView& lhs, std::function<bool(X)> pred) {
    // loop through the lhs extracting the elements that are true.
    Matrix<int> new_ind = lhs.filter(pred);

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








    }

};