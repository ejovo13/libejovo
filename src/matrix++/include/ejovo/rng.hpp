#pragma once

#include <utility>


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


    // double pnorm(double x, double mean, double sd) {

    // }

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