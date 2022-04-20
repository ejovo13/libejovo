#pragma once

#include <functional>

#include "types.hpp"
#include "trig.hpp"

namespace ejovo {

    namespace prob {

        namespace pdf {

            std::function<double(double)> gauss(double mu,  double sigma) {
                return [&] (double x) {
                    return (1.0 / (sigma * sqrt(trig::two_pi))) * std::exp(((x - mu) / sigma) * ((x - mu) / sigma) * -0.5);
                };
            }

            std::function<double(double)> gauss() {
                return [&] (double x) {
                    return (1.0 / sqrt(trig::two_pi)) * std::exp(-0.5 * (x * x));
                };
            }

        };

        // pade approximant [5, 4]
        double erf(double x) {

            double sqrt_pi = sqrt(trig::pi);
            constexpr double two_fif = 2.0 / 15.0;

            double num = two_fif * x * (49140.0 + (x * x) * (3570.0 + (x * x) * (739)));
            double den = sqrt_pi * (3276 + (x * x) * (1330 + (x * x) * (165)));

            return num / den;
        }



    };



};