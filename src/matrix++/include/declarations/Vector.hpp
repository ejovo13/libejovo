#pragma once

#include "Grid1D.hpp"
#include "Matrix.hpp"

namespace ejovo {


template <class T>
class Vector : public Grid1D<T> {

    // A vector has size n and can be a column or row vector.
public:
    /**============================================
     *!               Fields
     *=============================================**/
    std::size_t n;
    static ejovo::rng::Xoshiro& xoroshiro;
    std::unique_ptr<T[]> data;
    bool col = true;

    /**============================================
     *!    Grid1D Pure Virtual Functions
     *=============================================**/
    T& operator[](int i) override;
    const T& operator[](int i) const override;

    /**========================================================================
     *!                      Virtual Concept Functions
     *========================================================================**/
    Matrix<T> to_matrix() const override;
    // Matrix<T> new_matrix(int n) const override;
    std::size_t size() const override;

    std::unique_ptr<T[]> copy_data() const;

    Vector& reset();

    /**============================================
     *!               Constructors
     *=============================================**/
    // By default create column vectors
    Vector();
    Vector(int n, bool col = true);

    Vector(const Vector& x); // copy data
    Vector(Vector&& x);      // move data

    /**============================================
     *!               From
     *=============================================**/
    Vector from(std::initializer_list<T> list, bool col = true);

    /**============================================
     *!               Transpose functions
     *=============================================**/
    Vector t() const; // Maybe one of these should just change the flag instead of returning a new vec
    Vector transpose() const;

    /**============================================
     *!               Print Functions
     *=============================================**/
    Vector& print();
    const Vector& print() const;
    const Vector& print_col() const;
    const Vector& print_row() const;

    const Vector& summary() const;
    Vector& summary();


};

};