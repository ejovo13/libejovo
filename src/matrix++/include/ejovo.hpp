// Ejovo namespace for matrix functions

#pragma once

#include "matrix.hpp"
#include <initializer_list>
#include <cstdint>
#include <sys/random.h>
#include <climits>
#include "Xoshiro.hpp"
#include <map>
#include <functional>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include "Grid2D.hpp"
#include <cmath>

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
typename Matrix<X>::VecView operator|(Matrix<X>& lhs, std::function<bool(X)> pred) {
    typename Matrix<X>::VecView out (lhs, pred);
    return out;
}

template <class X>
typename Matrix<X>::VecView operator|(typename Matrix<X>::VecView& lhs, std::function<bool(X)> pred) {
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

    namespace rng {

        Xoshiro xoroshiro {};

    };

    uint64_t n_choose_k(uint64_t n, uint64_t k) {

        static std::map<std::pair<uint64_t, uint64_t>, uint64_t> values;
        using nk_map = std::map<std::pair<uint64_t, uint64_t>, uint64_t>;

        if (n == k || k == 0 || n == 0) return 1;
        if (n == 1) return 1;

        auto pair = std::make_pair<uint64_t, uint64_t>(std::move(n), std::move(k));

        nk_map::iterator iter = values.find(pair);
        if (iter == values.end()) {
            return values[pair] = n_choose_k(n - 1, k) + n_choose_k(n - 1, k - 1);
            // return n_choose_k(n - 1, k) + n_choose_k(n - 1, k - 1); // Non-memoization is CRAZYYYY long
        } else {
            return iter->second;
        }
    }

    // template <>
    Matrix<double> runif(int n, double a = 0, double b = 1) {
        // ejovo::rng::xoroshiro.unifd(a, b);

        // verify that n is greater than 0
        if (n == 0) return Matrix<double>::null();

        Matrix<double> out(1, n);
        out.loop([&] (double& x) {
            x = ejovo::rng::xoroshiro.unifd(a, b);
        });

        return out;
    }

    // template <>
    Matrix<double> rnorm(int n, double mean = 0, double sd = 1) {
        // ejovo::rng::xoroshiro.unifd(a, b);

        // verify that n is greater than 0
        if (n == 0) return Matrix<double>::null();

        Matrix<double> out(1, n);
        out.loop([&] (double& x) {
            x = ejovo::rng::xoroshiro.norm(mean, sd);
        });

        return out;
    }

        // template <>
    Matrix<double> rexp(int n, double rate = 1) {
        // ejovo::rng::xoroshiro.unifd(a, b);

        // verify that n is greater than 0
        if (n == 0) return Matrix<double>::null();

        Matrix<double> out(1, n);
        out.loop([&] (double& x) {
            x = ejovo::rng::xoroshiro.exp(rate);
        });

        return out;
    }

    Matrix<double> rbinom(int n, int size, double p = 0.5) {

        if (n == 0) return Matrix<double>::null();

        Matrix<double> out(1, n);
        out.loop([&] (double& x) {
            x = ejovo::rng::xoroshiro.binom(size, p);
        });

        return out;
    }

    // k observations
    double dbinom(int k, int size, double p = 0.5) {
        return (double) n_choose_k(size, k) * std::pow(p, k) * std::pow(1 - p, size - k);
    }



    // Hypergeometric distribution.
    // Numer of successes (k) in n draws, total population N, items that have positive quality K
    double dhyper(int k, int n, int N, int K) {
        return ((double) (n_choose_k(K, k) * n_choose_k(N - K, n - k)) / n_choose_k(N, n));
    }

    Matrix<double> rhyper(int n, int ndraws, int N, int K) {

        if (n == 0) return Matrix<double>::null();

        Matrix<double> out(1, n);
        out.loop([&] (double& x) {
            x = ejovo::rng::xoroshiro.hyper(ndraws, N, K);
        });

        return out;

    }


};







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

    template <class T, class U>
    T plus(const T& a, const U& b) {
        return a + b;
    }


    // named functions of +=, -=, /=, and *= operators
    template <class T, class U>
    void id_eq(T& a, const U& b) {
        a = b;
    }

    template <class T, class U>
    void plus_eq(T& a, const U& b) {
        a += b;
    }

    template <class T, class U>
    void minus_eq(T& a, const U& b) {
        a -= b;
    }

    template <class T, class U>
    void times_eq(T& a, const U& b) {
        a *= b;
    }

    template <class T, class U>
    void divide_eq(T& a, const U& b) {
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


    // Function OPERATOR



        // filter


    template <class T>
    Matrix<T> vec(std::initializer_list<T> list, bool col = true) {
        // Get the length of this list
        int n = list.size();
        int i = 1;

        Matrix<T> out;

        if (col) out = Matrix<T>::zeros(n, 1);
        else out = Matrix<T>::zeros(1, n);

        for (auto x : list) {
            out(i) = x;
            i++;
        }
        return out;
    }

    // this is expensive and computes TWO logarithms
    // double log_base(double base, double x) {
    //     return (log(x) / log(base));
    // }

    // double kthRoot(double n, int k) {
    //     return std::pow(k, (1.0 / k) * (log_base(k, n)));
    // }

    template <class T> Matrix<T> abs(Matrix<T> m) {
        return m.abs();
    }

    // template <class T> Matrix<T>

    template<class T = double>
    Matrix<T> linspace(T start, T end, int n = 100) {

        T diff = (end - start) / (n - 1);

        Matrix<T> lin{n};

        lin.loop_i([&] (int i) {lin(i) = start + (i - 1) * diff;});
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
        mat_copy.loop_i([&] (int i) {mat_copy(i) = f(mat(i));});
        return mat_copy;
    }

    template <class T>
    std::vector<T> map(const std::vector<T>& vec, std::function<T(T)> f) {
        std::vector<T> copy {vec};
        int i = 0;
        for (auto el : vec) {
            copy[i] = f(el);
            i++;
        }
        return copy;
    }

    template <class T>
    void print(const std::vector<T>& vec) {
        int n = vec.size();
        std::cout << "{";

        for (auto el : vec) {
            std::cout << el << ", ";
        }

        std::cout << "}\n";
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

    namespace scalar {

        template <class T>
        T max(const T& a, const T& b) {
            return a > b ? a : b;
        }

        template <class T>
        T min(const T& a, const T& b) {
            return a < b ? a : b;
        }

    };



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
        out.loop_i([&] (int i) {out(i) = i;});
        return out;
    }

    template <class T>
    Matrix<T> seq(T start, T end) {
        const int len_seq = (end - start) + 1;
        Matrix<T> out{len_seq};
        out.fill(0);
        out.loop_i([&] (int i) {
            out(i) = start + (i - 1);
        });
        return out;
    }

    // Make a sequence from 1 to n
    // Matrix<int> seq(int n) {
    //     Matrix<int> out{n};
    //     out.loop_i(, [&] (int i) {out(i) = i;});
    //     return out;
    // }

    Matrix<int> seq(int start, int end) {
        const int len_seq = (end - start) + 1;
        Matrix<int> out{len_seq};
        out.fill(0);
        out.loop([&] (int& x) {
            x = start + (x - 1);
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
        mat.loop_i([&] (int i) {
            if (f(mat(i))) count ++;
        });

        Matrix<T> out{count};

        int out_i = 1;
        mat.loop_i([&] (int i) {
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


    // Use euler's method for differential equations







};

namespace ejovo {

    namespace diffyq {


        // Use euler's method for differential equations
        // need the function, need an initial condition

        // f_tu = [] (double t, double u) { return cos(t); }; // dy/dt = cos(t), u(t) = sin(t)

        template <class X>
        // using X so that we can pass a vector in as an argument
        Matrix<X> euler_explicit(std::function<X(double, X)> f, X u0, double t0, double tf, int n = 1000) {

            //
            auto time = ejovo::linspace<double>(t0, tf, n);
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
            auto time = ejovo::linspace<double>(t0, tf, n);
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



    };

    /**========================================================================
     *!                           R interface
     *========================================================================**/
    template <class T>
    class Dataframe {

    public:

        std::vector<Matrix<T>> cols;
        std::vector<std::string> col_names; // This better be the same size as cols...
        std::size_t nrows;


        // Have a vector of matrices
        // Dataframe(std::initializer_list<Matrix<T>> list, std::initializer_list<std::string> names);
        Dataframe(std::vector<Matrix<T>> data, std::vector<std::string> names);

        bool to_csv(const std::string filename);


    private:





    };

    // template <class T>
    // Dataframe<T>::Dataframe(std::initializer_list<Matrix<T>> data, std::initializer_list<std::string> names) : cols{}, cols_names{}, nrows{0} {

    //     int len_mat = list.begin()->size();
    //     int n_added = 0;

    //     for (auto mat : list) {
    //         if (mat.size() != len_mat) continue;
    //         cols.push_back(mat);
    //         n_added ++;
    //     }

    //     nrows = n_added;

    // }

    template <class T>
    Dataframe<T>::Dataframe(std::vector<Matrix<T>> data, std::vector<std::string> names) : cols{data}, col_names{names}, nrows{data.begin()->size()} {}

    Dataframe<double> df(std::initializer_list<Matrix<double>> data, std::initializer_list<std::string> names) {

        // check to make sure that all of the vectors have the same size
        std::vector<Matrix<double>> cols;
        std::vector<std::string> col_names;

        int size = data.begin()->size();

        for (auto mat : data) {
            if (mat.size() != size) throw "You a dumb bitch";
            cols.push_back(mat);
        }

        for (auto n : names) {
            col_names.push_back(n);
        }

        Dataframe<double> out (cols, col_names);
        return out;
    }


    template <class T>
    bool Dataframe<T>::to_csv(const std::string filename) {

        std::ofstream my_file;

        my_file.open(filename);
        const int ncols = cols.size();

        for (int i = 0; i < ncols - 1; i++) {
            my_file << col_names.at(i) << ",";
        }

        my_file << col_names.at(ncols - 1) << "\n";

        // iterate through length of the elements of mat
        for (int i = 1; i <= nrows; i++) {

            // Now add a row
            for (int j = 0; j < ncols - 1; j++) {

                my_file << cols.at(j).at(i) << ",";
            }

            my_file << cols.at(ncols - 1).at(i) << "\n";
        }

        my_file.close();


        return true;
    }


    std::string create_r_plot(std::string filename) {

        return std::string(R"(

library(ggplot2)
library(tibble)
df <- as_tibble(read.csv(')") + filename + ".csv'" + R"())

p <- df |> ggplot(aes(x, y)) + geom_line()

ggsave(')" + filename + ".png" + R"(', p, device = 'png')

)";
    }


    bool plot(Matrix<double> x, Matrix<double> y, std::string filename = "test", int width = 5, int height = 5, std::string units = "cm") {

        auto df = ejovo::df({x, y}, {"x", "y"});

        std::string csv_file = filename + ".csv";
        std::string r_file   = filename + "_temp.r";


        df.to_csv(csv_file);

        // now generate the r code needed to create the image file
        std::ofstream my_file;

        my_file.open(r_file);
        my_file << ejovo::create_r_plot(filename);
        my_file.close();

        // now delete the temp r code, call Rscript
        system((std::string("Rscript ") + filename + "_temp.r").c_str());
        remove(r_file.c_str());
        remove(csv_file.c_str());

        return true;

    }



};




namespace ejovo {

    namespace prob {

        namespace pdf {

            std::function<double(double)> gauss(double mu,  double sigma) {
                return [&] (double x) {
                    return (1.0 / (sigma * sqrt(trig::two_pi))) * exp(((x - mu) / sigma) * ((x - mu) / sigma) * -0.5);
                };
            }

            std::function<double(double)> gauss() {
                return [&] (double x) {
                    return (1.0 / sqrt(trig::two_pi)) * exp(-0.5 * (x * x));
                };
            }

        };


    };





};