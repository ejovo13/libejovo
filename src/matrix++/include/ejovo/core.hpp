#pragma once

#include "types.hpp"
#include "trig.hpp"
#include "factory.hpp"

namespace ejovo {

template <class T = int>
Matrix<T> seq(T n) {
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


Matrix<double> seq(int start, int end, double diff) {
    if( ((end - start) / diff) < 0 ) throw "Wrong sign";

    const int len_seq = 1 + abs((end - start) / diff);
    Matrix<double> out(1, len_seq);
    out.loop_i([&] (int i) {
        out(i) = start + (i - 1) * diff;
    });
    return out;
}

// template <class T>
// Matrix<T> seq(T start, T end, T diff) {

//     if( ((end - start) / diff) < 0 ) throw "Wrong sign";

//     const int len_seq = 1 + abs((end - start) / diff);
//     Matrix<T> out(1, len_seq);
//     out.loop_i([&] (int i) {
//         out(i) = start + (i - 1) * diff;
//     });
//     return out;
// }

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

    Matrix m1 = u.repcol(v.size());
    Matrix m2 = v.reprow(u.size());

    return std::make_tuple(m1, m2);
}

template <class T>
std::tuple<Matrix<T>, Matrix<T>> meshgrid(const Matrix<T>& u) {

    // Matrix m1 = Matrix<T>::zeros(u.size(), v.size());
    // Matrix m2 = m1.clone();

    Matrix m1 = u.repcol(u.size());
    Matrix m2 = u.reprow(u.size());

    return std::make_tuple(m1, m2);
}

/**========================================================================
 *!                           Mappable functions
 *========================================================================**/
// C++ 20 gang shit
template <class T>
concept Mappable = requires (Grid1D<T> t, std::function<T(T)> f) {
    {t.map(f)} -> std::same_as<Matrix<T>>;
};

// I want to  add a numeric restriction to this
template <Mappable M>
auto cos(M m) {
    return m.map(trig::cos<double>);
}

template <Mappable M>
auto sin(M m) {
    return m.map(trig::sin<double>);
}

template <Mappable M>
auto tan(M m) {
    return m.map(trig::tan<double>);
}

template <Mappable M>
auto log(M m) {
    return m.map(::log);
}

template <Mappable M>
auto exp(M m) {
    return m.map(::exp);
}

template <Mappable M>
auto asin(M m) {
    return m.map(::asin);
}

template <Mappable M>
auto acos(M m) {
    return m.map(::acos);
}

template <Mappable M>
auto atan(M m) {
    return m.map(::atan);
}

template <Mappable M>
auto tanh(M m) {
    return m.map(::tanh);
}

template <Mappable M>
auto cosh(M m) {
    return m.map(::cosh);
}

template <Mappable M>
auto sinh(M m) {
    return m.map(::sinh);
}

template <Mappable M>
auto pow(M m, int k) {
    return m.map(ejovo::factory::pow<double, k>);
}

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
Matrix<double> linspace(double start, double end, int n = 100) {

    double diff = (end - start) / (n - 1);

    Matrix<double> lin (1, n);

    lin.loop_i([&] (int i) {lin(i) = start + (i - 1) * diff;});
    return lin;

}

// template<class T = double>
// Matrix<T> linspace(T start, T end, int n = 100) {

//     T diff = (end - start) / (n - 1);

//     Matrix<T> lin{n};

//     lin.loop_i([&] (int i) {lin(i) = start + (i - 1) * diff;});
//     return lin;
// }

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



// template<class T>
// T pnorm(const Matrix<T>& mat, int p = 2) {
//     auto mat_pow = pow(mat, p);
//     return sum(mat_pow);
// }

};
