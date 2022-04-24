#pragma once

#include <initializer_list>
#include <cstdint>
#include <sys/random.h>
#include <climits>
#include <cmath>
#include "types.hpp"

namespace ejovo {

    namespace rng {


        class Xoshiro {

        public:
            // std::unique_ptr<uint64_t [4]> state;
            uint64_t state[4];

            Xoshiro(); // initialize with random noise from the operating system
            // Xoshiro(std::initializer_list<uint64_t> list);
            Xoshiro(uint64_t, uint64_t, uint64_t, uint64_t);

            Xoshiro& seed();
            // Xoshiro& seed(std::initializer_list<uint64_t> list);
            Xoshiro& seed(uint64_t, uint64_t, uint64_t, uint64_t);

            uint64_t next();
            double next_double();
            int next_int();

            int unif(int a, int b);
            double unifd(double a, double e);
            // double unif(); // Return X ~ U(0, 1)
            double norm();
            double norm(double mean, double sd);
            double exp(double rate = 1);
            int binom(int size, double p = 0.5);
            int hyper(int ndraws, int N, int K);
            bool bernouilli(double p = 0.5); // return true or false
            template <class T> int categorical(const Grid1D<T>& p); // return an integer i from 1 to k representing the category of the p(i)
            int categorical(std::vector<double> p); // For now we will assume that the probabilites are not sorted.



        };

        uint64_t rol64(uint64_t x, int k) {
            return (x << k) | (x >> (64 - k));
        }

        Xoshiro::Xoshiro() {
            this->seed();
        }

        Xoshiro::Xoshiro(uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
            this->seed(a, b, c, d);
        }

        Xoshiro& Xoshiro::seed() {
            getrandom(this->state, 32, 0);
            return *this;
        }

        Xoshiro& Xoshiro::seed(uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
            this->state[0] = a;
            this->state[1] = b;
            this->state[2] = c;
            this->state[3] = d;
            return *this;
        }

        uint64_t Xoshiro::next()
        {
            uint64_t *s = state;
            uint64_t const result = rol64(s[1] * 5, 7) * 9;
            uint64_t const t = s[1] << 17;

            s[2] ^= s[0];
            s[3] ^= s[1];
            s[1] ^= s[2];
            s[0] ^= s[3];

            s[2] ^= t;
            s[3] = rol64(s[3], 45);

            return result;
        }

        int Xoshiro::next_int() {
        // interpret the first 32 bits of the 64 bits as an integer. - this returns a uniform X ~ [0, 2147483647]
            int *iptr = nullptr;
            uint64_t bits = this->next();
            iptr = (int *) &bits;
            return std::abs(iptr[1]);
            // return iptr[1];
        }

        // get a double in the range [0, 1]
        double Xoshiro::next_double() {
            uint64_t val = this->next();
            return (double) val / (double) ULONG_MAX; // This is how we "take the top 53 bits I think........."
        }

        int Xoshiro::unif(int a, int b) {
        // return a random variable X ~ [a, b]
            // int = get_int_xoshiro()
            int spread = (b - a) + 1;
            double x = this->next_double(); // returns a value in [0, 1)

            return (int) std::floor(x * spread) + (a) ; // floor(x * spread) returns a vlue in [0, spread)
        }

        double Xoshiro::unifd(double a, double b) {

            double spread = (b - a);

            double x = this->next_double(); // returns a value in [0, 1)

            return x * spread + a;
        }

        // double Xoshir

        double Xoshiro::norm() {

            double u1 = this->unifd(0, 1);
            double u2 = this->unifd(0, 1);

            double R = std::sqrt(-2 * std::log(u1));

            return R * std::cos(2 * M_PI * u2);
        }

        // sample from X ~ N(mean, std^2)
        double Xoshiro::norm(double mean, double std) {
            return (norm() * std) + mean;
        }

        // sample once from the exponential distribution
        double Xoshiro::exp(double rate) {

            double y = this->unifd(0, 1);

            return (-1.0 / rate) * std::log(1 - y);
        }

        // a single trial of a binomial experiment
        int Xoshiro::binom(int size, double p) {
            int count = 0;
            for (int i = 0; i < size; i++) {
                if (this->next_double() <= p) count++;
            }
            return count;
        }

            // int hyper(int ndraws, int N, int K);
        // n draws, return the number of successes with population N and successful elements K
        int Xoshiro::hyper(int ndraws, int N, int K) {
            // std::cout << "Calculating hyper with ndraws: " << ndraws << ", N: " << N << ", K: " << K << "\n";
            int count = 0;
            double p = 0;
            for (int i = 0; i < ndraws; i++) {

                p = (double) K / N;

                // std::cout << "calculated p: " << p << " == " << K << "/" << N << std::endl;

                if (this->next_double() < p) {
                    // std::cout << "Success, decrementing K\n";
                    count ++;
                    K --; // don't replace the element if we have a success
                } else {
                    // std::cout << "Failure, decrememnting N\n";
                }
                N --; // Reduce the number of total elements, no matter which ball is pulled
            }
            return count;
        }

        bool Xoshiro::bernouilli(double p) {
            return unifd(0, 1) <= p;
        }

        // return a number between 1 and p.size()
        template <class T>
        int Xoshiro::categorical(const Grid1D<T>& p) {

            // iterate along the elements of the matrix (hopefully sorted...)
            // and return the integer of the corresponding division that it falls in
            // | p1 |   p2   |p3|     p4     |, where all the probabilites are ASSUMED
            // to add up to one.
            double x = unifd(0, 1);
            double acc = 0;

            for (int i = 1; i <= p.size(); i++) {
                acc += p(i);
                if (x < acc) return i;
            }

            return 0;
        }



        // create a global Xoshiro
        Xoshiro g_XOSHIRO{};

    };

};