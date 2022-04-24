#pragma once

#include "ejovo/rng/rng.hpp"

namespace ejovo {

    namespace monte_carlo {

        // Calculate the integral of f(x) between a and b using monte carlo methods
        double integrate_unif(int n, std::function<double (double)> fn, double a, double b) {

            // sample from a uniform distribution between a and b n times.
            auto sim = runif(n, a, b);
            sim.mutate(fn); // now apply the function

            return sim.mean() * (b - a);
        }

        double integrate_norm_bounded(int n, std::function<double (double)> fn, double a, double b) {

            // Sample from a standard normal distribution.
            auto gauss = ejovo::prob::pdf::gauss();
            auto ind = ejovo::factory::indicator<double>(a, b);

            auto sim = rnorm(n);

            auto h_x = [&] (double x) {
                return fn(x) * ind(x) / gauss(x);
            };

            sim.mutate(h_x);

            return sim.mean();
        }

        double integrate_norm(int n, std::function<double (double)> fn) {

            auto gauss = ejovo::prob::pdf::gauss();

            auto sim = rnorm(n);

            auto h_x = [&] (double x) {
                return fn(x) / gauss(x);
            };

            sim.mutate(h_x);

            return sim.mean();
        }

    };

}