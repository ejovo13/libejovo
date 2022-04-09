// Ejovo namespace for matrix functions

#pragma once

#include "matrix.hpp"
#include <initializer_list>

/**========================================================================
 *!                           Ejovo namespace
 *========================================================================**/
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

namespace ejovo {

    template <class T>
    T id (T x) {
        return x;
    }

    template <class T>
    void plus_eq(T& a, T& b) {
        a += b;
    }

    template <class T>
    void minus_eq(T& a, T& b) {
        a -= b;
    }

    template <class T>
    void times_eq(T& a, T& b) {
        a *= b;
    }

    template <class T>
    void divide_eq(T& a, T& b) {
        a /= b;
    }

    template <class T>
    bool eq (T a, T b) {
        return a == b;
    }

    template <class T>
    bool lt (T a, T b) {
        return a < b;
    }

    template <class T>
    bool gt (T a, T b) {
        return a > b;
    }

    template <class T>
    bool leq (T a, T b) {
        return a <= b;
    }

    template <class T>
    bool geq (T a, T b) {
        return a >= b;
    }

    template <class T> T abs(T x) {
        return x < 0 ? -x : x;
    }

    template <class T>
    Matrix<T> vec(std::initializer_list<T> list) {
        // Get the length of this list
        int n = list.size();
        int i = 1;
        Matrix<T> out{1, n};
        for (auto x : list) {
            out(i) = x;
            i++;
        }
        return out;
    }

    // this is expensive and computes TWO logarithms
    double log_base(double base, double x) {
        return (log(x) / log(base));
    }

    double kthRoot(double n, int k) {
        return std::pow(k, (1.0 / k) * (log_base(k, n)));
    }

    template <class T> Matrix<T> abs(Matrix<T> m) {
        return m.abs();
    }

    // template <class T> Matrix<T>

    template<class T = double>
    Matrix<T> linspace(T start, T end, int n = 100) {

        T diff = (end - start) / (n - 1);

        Matrix<T> lin{n};

        loop_i(lin, [&] (int i) {lin(i) = start + (i - 1) * diff;});
        return lin;
    }

    template <class T = double>
    Matrix<T> logspace(T start_exp, T end_exp, int n = 50, T base = 10) {
        auto exponents = linspace(start_exp, end_exp, n);
        return map(exponents, [&] (auto x) {
            return std::pow(base, x);
        });
    }


    template<class T, class UnaryFn>
    Matrix<T> map(const Matrix<T>& mat, UnaryFn f) {
        // create a copy
        // std::cout << "Calling map\n";
        Matrix mat_copy = mat;
        // std::cout << "Created copy:\n";
        // mat_copy.print();
        loop_i(mat_copy, [&] (int i) {mat_copy(i) = f(mat(i));});
        return mat_copy;
    }



    template<class T, class BinaryFn>
    T reduce(const Matrix<T>& mat, BinaryFn f, T init = 0) {

        if (mat.size() == 0) {
            std::cerr << "Trying to reduce a matrix of size 0, returning default value of T\n";
            return T{};
        }
        if (mat.size() == 1) return mat(1);

        T out = mat(1) + init;

        for (int i = 2; i <= mat.size(); i++) {
            out = f(out, mat(i));
        }
        // loop(mat, [&] (int i) {out = f(out, mat(i));});

        return out;
    }

    template<class T>
    T sum(const Matrix<T>& mat) {
        return reduce(mat, [] (auto x, auto y) {return x + y;});
    }

    template<class T>
    T prod(const Matrix<T>& mat) {
        return reduce(mat, [] (auto x, auto y) {return x * y;}, 1);
    }

    template<class T>
    T min(const Matrix<T>& mat) {
        return reduce(mat, [] (auto x, auto y) {return x < y ? x : y;});
    }

    template<class T>
    T max(const Matrix<T>& mat) {
        return reduce(mat, [] (auto x, auto y) {return x > y ? x : y;});
    }

    template<class T>
    Matrix<T> pow(const Matrix<T>& mat, int n) {
        return map(mat, [&] (auto x) {return std::pow(x, n);});
    }

    template<class T>
    T pnorm(const Matrix<T>& mat, int p = 2) {
        auto mat_pow = pow(mat, p);
        return sum(mat_pow);
    }

    template <class T = int>
    Matrix<T> seq(int n) {
        Matrix<T> out{n};
        loop_i(out, [&] (int i) {out(i) = i;});
        return out;
    }

    template <class T>
    Matrix<T> seq(T start, T end) {
        const int len_seq = (end - start) + 1;
        Matrix<int> out{len_seq};
        out.fill(0);
        loop_i(out, [&] (int i) {
            out(i) = start + (i - 1);
        });
        return out;
    }

    // Make a sequence from 1 to n
    // Matrix<int> seq(int n) {
    //     Matrix<int> out{n};
    //     loop_i(out, [&] (int i) {out(i) = i;});
    //     return out;
    // }

    Matrix<int> seq(int start, int end) {
        const int len_seq = (end - start) + 1;
        Matrix<int> out{len_seq};
        out.fill(0);
        loop_i(out, [&] (int i) {
            out(i) = start + (i - 1);
        });
        return out;
    }

    template<class T>
    T mean(const Matrix<T>& mat) {
        int len = mat.size();
        return sum(mat) / len;
    }

    template <class T>
    T var(const Matrix<T>& mat, bool population = true) {
        T u = mat.mean();

        int den = population ? mat.size() : mat.size() - 1;

        Matrix<T> m = mat - u;
        return m.sqrd().sum() / den;
    }

    template<class T>
    T sd(const Matrix<T>& mat, bool population = true) {
        return sqrt(ejovo::var(mat, population));
    }

    template<class T, class Predicate>
    Matrix<T> filter(Matrix<T> mat, Predicate f) {
        // make one pass to count how many times the result is true
        int count = 0;
        loop_i(mat, [&] (int i) {
            if (f(mat(i))) count ++;
        });

        Matrix<T> out{count};

        int out_i = 1;
        loop_i(mat, [&] (int i) {
            if (f(mat(i))) {
                out(out_i) = mat(i);
                out_i ++;
            }
        });

        return out;
    }

    template<class T, class UnaryFn>
    Matrix<T>& mutate(Matrix<T> &mat, UnaryFn f) {
        for (int i = 0; i < mat.size(); i++) {
            mat[i] = f(mat[i]);
        }
        return mat;
    }

    // whereas map returns a value, apply will just call the function and not save the return
    template <class T, class UnaryFn>
    void apply(Matrix<T> &mat, UnaryFn f) {
        for (int i = 0; i < mat.size(); i++) {
            f(mat[i]);
        }
    }

    template<class T = double>
    Matrix<T> chebynodes_std(int n = 100) {
        auto xi = seq<T>(n);
        return map(xi, [&] (auto x) {
            return -trig::cos(trig::pi * (2 * x - 1) / (2 * n));
        });
    }

    template<class T = double>
    Matrix<T> chebynodes(T a, T b, int n = 100) {
        auto affine_transformation = [&] (auto x) {
            return (a + b) / 2 + ((b - a) / 2) * x ;
        };
        return map(chebynodes_std(n), affine_transformation);
    }


    template <class T>
    std::tuple<Matrix<T>, Matrix<T>> meshgrid(const Matrix<T>& u, const Matrix<T>& v) {

        // Matrix m1 = Matrix<T>::zeros(u.size(), v.size());
        // Matrix m2 = m1.clone();

        Matrix m1 = u.rep_col(v.size());
        Matrix m2 = v.rep_row(u.size());

        return std::make_tuple(m1, m2);
    }




};

namespace ejovo {

    // I want to  add a numeric restriction to this
    template <class T>
    Matrix<T> cos(Matrix<T> x) {
        return map(x, trig::cos<T>);
    }

    template <class T>
    Matrix<T> sin(Matrix<T> x) {
        return map(x, trig::sin<T>);
    }

    template <class T>
    Matrix<T> tan(Matrix<T> x) {
        return map(x, trig::tan<T>);
    }

};

namespace functions {

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

};


namespace opti {

    constexpr int MAX_ITERATIONS = 1E5;
    constexpr double EPS = 1E-10;

    using namespace functions;

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

        while (ejovo::abs(err) < eps && i < max_it) {

            x = g(x);

            i++;
        }

    }

};