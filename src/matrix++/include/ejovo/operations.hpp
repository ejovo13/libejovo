#pragma once

namespace ejovo {

    namespace binop {

        template <class X, class Y>
        X plus(const X& x, const Y& y) {
            return x + y;
        }

        template <class X, class Y>
        X plus_abs(const X& x, const Y& y) {
            return x + abs(y);
        }

        template <class X, class Y>
        X minus(const X& x, const Y& y) {
            return x - y;
        }

        template <class X, class Y>
        X times(const X& x, const Y& y) {
            return x * y;
        }

        template <class X, class Y>
        X divided_by(const X& x, const Y& y) {
            return x / y;
        }

        template <class X>
        X min(const X& a, const X& b) {
            return a < b ? a : b;
        }

        template <class X>
        X max(const X& a, const X& b) {
            return a > b ? a : b;
        }

    };

};