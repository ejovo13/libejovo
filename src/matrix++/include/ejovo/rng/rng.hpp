#pragma once

#include <map>

#include "types.hpp"
#include "Xoshiro.hpp"
#include "ejovo/quadrature.hpp"



namespace ejovo {

    namespace rng {

        Xoshiro xoroshiro {};

    };

    // Memoized version of nCk
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

    Matrix<double> runif(int n, double a = 0, double b = 1) {

        // verify that n is greater than 0
        if (n == 0) return Matrix<double>::null();

        Matrix<double> out(1, n);
        out.loop([&] (double& x) {
            x = ejovo::rng::xoroshiro.unifd(a, b);
        });

        return out;
    }

    Matrix<double> rnorm(int n, double mean = 0, double sd = 1) {

        // verify that n is greater than 0
        if (n == 0) return Matrix<double>::null();

        Matrix<double> out(1, n);
        out.loop([&] (double& x) {
            x = ejovo::rng::xoroshiro.norm(mean, sd);
        });

        return out;
    }

    Matrix<double> rexp(int n, double rate = 1) {

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

    // random variable of the categorical distribution
    Matrix<int> rcat(int n, const Matrix<double>& p) {

        if (n == 0) return Matrix<int>::null();

        Matrix<int> out(1, n);
        out.loop([&] (int& x) {
            x = ejovo::rng::xoroshiro.categorical<double>(p);
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

    template <int N = 1000>
    double erf(double x) {
        return ejovo::quad::erf::gausslegendre<N>(x);
    }

    double pnorm(double x) {

        double root2 = std::sqrt(2.0);
        return 0.5 * (1 + ejovo::erf<2>(x / root2));

    }

    double pnorm_2(double x) {

        double root2 = std::sqrt(2.0);
        return 0.5 * (1 + ejovo::quad::erf::gausslegendre_2<1000>(x / root2));

    }

    double pnorm_mid(double x) {

        double root2 = std::sqrt(2.0);
        return 0.5 * (1 + ejovo::quad::erf::midpoint<100>(x / root2));

    }

    // Take in discrete bins (for example ejovo::seq(10)) and count
    // the number of times each
    Matrix<int> histogram_counts_discrete(const Grid1D<int>& obs, const Grid1D<int>& bins) {

        // Traverse through the observations.
        Matrix<int> counts = Matrix<int>::zeros(1, bins.size());

        // loop through the observations
        obs.loop([&] (const auto& x) {
            // and find the appropriate bin
            for (int i = 1; i <= bins.size(); i++) {
                if (x == bins(i)) {
                    counts(i) ++;
                    break;
                }
            }
        });

        return counts;
    }

    Matrix<double> histogram_freq_discrete(const Matrix<int>& obs, const Matrix<int>& bins) {

        Matrix<int> counts = histogram_counts_discrete(obs, bins);
        int total = counts.sum();

        return counts.map<double>([&] (auto x) { return x / (double) total; });
    }

};