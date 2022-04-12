#pragma once

// #include "matrix.hpp"
#include "ejovo.hpp"


/**========================================================================
 *!                           AbstractView definition
*========================================================================**/
template <class T>
class Matrix<T>::AbsView {

public:

    // AbsView(Matrix &m);
    virtual int nrows() const = 0;
    virtual int ncols() const = 0;
    virtual std::string to_string() const = 0;
    virtual Matrix& matrix() const = 0;
    virtual T& operator()(int i) const = 0; // Don't check bounds!!
    virtual T& operator()(int i, int j) const = 0; // Don't check bounds!!

    // virtual T& at(int i) = 0; // check bounds!!
    // virtual T& at(int i, int j) = 0; // check bounds!!
    T& at(int i); // check bounds!!
    T& at(int i, int j); // check bounds!!

    T* get_ptr(); // get a pointer to the underlying data of the matrix
    int size();
    bool valid_bounds(int i);
    bool valid_bounds(int i, int j);
    void print();

    // template <class Fn>
    // AbsView& loop(std::function<T(T)>);
    virtual AbsView& loop(std::function<void(T)>);
    virtual AbsView& loop_i(std::function<void(int)>);
    virtual AbsView& loop_ij(std::function<void(int, int)>);

    virtual AbsView& mutate(std::function<T(T)>);
    // AbsView& mutate(std::function<T(T)>);

    // These Three assignment operators WORK!!!
    // virtual AbsView& assign(Matrix&& mat, std::function<void(T&, const T&)> ass_op);
    virtual AbsView& assign(const Matrix& mat, std::function<void(T&, const T&)> ass_op);
    virtual AbsView& assign(const T& scalar, std::function<void(T&, const T&)> ass_op);
    virtual AbsView& assign(const AbsView& view, std::function<void(T&, const T&)> ass_op); // use const AbsView to bind with any type..

    // Once we get to the actual overload though, we are having non-stop problems....
    // virtual AbsView& operator=(const AbsView& view);
    virtual AbsView& operator=(const Matrix& mat) = 0;
    virtual AbsView& operator=(const AbsView& view);
    virtual AbsView& operator=(const T& scalar) = 0;
    // virtual AbsView& operator=(T scalar);
    // virtual AbsView& operator=(double x);
    // virtual AbsView& operator=(Matrix mat);
    // virtual AbsView& operator=(Matrix&& mat);
    // virtual AbsView& operator=(AbsView& view);

    // template <class U> AbsView& operator=(const U& scalar);

    virtual AbsView& operator+=(const Matrix& mat);
    virtual AbsView& operator+=(const T& scalar);
    virtual AbsView& operator+=(const AbsView& view);

    virtual AbsView& operator-=(const Matrix& mat);
    virtual AbsView& operator-=(const T& scalar);
    virtual AbsView& operator-=(const AbsView& view);

    virtual AbsView& operator*=(const T& scalar);
    virtual AbsView& operator/=(const T& scalar);

    Matrix to_matrix() const;
    // Matrix to_rowvec();
    // Matrix to_colvec();

        // V * 5
    friend Matrix<T> operator*(const AbsView& lhs, const T& scalar) {
        return lhs.to_matrix() *= scalar;
    }

    // 5 * V
    friend Matrix<T> operator*(const T& scalar, const AbsView& rhs) {
        return rhs.to_matrix() *= scalar;
    }

    friend Matrix<T> operator/(const AbsView& lhs, const T& scalar) {
        return lhs.to_matrix() /= scalar;
    }

    friend Matrix<T> operator/(const T& scalar, const AbsView& rhs) {
        return scalar / rhs.to_matrix();
    }

    friend Matrix<T> operator+(const AbsView& lhs, const T& scalar) {
        return lhs.to_matrix() += scalar;
    }

    friend Matrix<T> operator+(const T& scalar, const AbsView& rhs) {
        return rhs.to_matrix() += scalar;
    }

    friend Matrix<T> operator-(const AbsView& lhs, const T& scalar) {
        return lhs.to_matrix() -= scalar;
    }

    friend Matrix<T> operator-(const T& scalar, const AbsView& rhs) {
        return rhs.to_matrix() -= scalar;
    }

    friend Matrix<T> operator-(const AbsView& lhs, const Matrix<T>& rhs) {
        return lhs.to_matrix() -= rhs;
    }

    friend Matrix<T> operator-(const Matrix<T>& lhs, const AbsView& rhs) {
        // We can avoid a copy here and just loop over the rhs elements
        return lhs - rhs.to_matrix();
    }

    std::pair<int, int> ind_to_ij(int n) const;

private:


};

template <class T>
std::pair<int, int> Matrix<T>::AbsView::ind_to_ij(int n) const {
    int i = ((n  - 1) / this->nrows()) + 1;
    int j = (n - 1) % this->nrows() + 1;
    return std::make_pair<int, int>(std::move(i), std::move(j));
}

// template <class T>
// std::pair<int, int> convert_vector_indices_to_ij(const typename Matrix<T>::AbsView& mat, int n) {
//     int i = ((n  - 1) / mat.nrows()) + 1;
//     int j = (n - 1) % mat.nrows() + 1;
//     return std::make_pair<int, int>(std::move(i), std::move(j));
// }


/**========================================================================
 *!                           Abstract View
 *========================================================================**/
template <class T>
int Matrix<T>::AbsView::size() {
    return this->ncols() * this->nrows();
}


/**============================================
 *!               Operator =
 *=============================================**/
template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator=(const Matrix<T>& mat) {
    return this->assign(mat, ejovo::id_eq<T, T>);
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator=(const AbsView& view) {
    return this->assign(view, ejovo::id_eq<T, T>);
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator=(const T& scalar) {
    return this->assign(scalar, ejovo::id_eq<T, T>);
}

// template <class T>
// typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator=(Matrix<T> mat) {
//     return this->assign(mat, ejovo::id_eq<T, T>);
// }

// template <class T>
// typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator=(Matrix<T>&& mat) {
//     return this->assign(mat, ejovo::id_eq<T, T>);
// }

// template <class T>
// typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator=(AbsView&& view) {
//     // Check if this matrix is empty

//     return this->assign(view, ejovo::id_eq<T, T>);
// }

// template <class T>
// template <class U>
// typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator=(const U& scalar) {
//     return this->assign(scalar, ejovo::id_eq<T, U>);
// }




/**============================================
 *!               Operator +=
 *=============================================**/
template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator+=(const Matrix<T>& mat) {
    return this->assign(mat, ejovo::plus_eq<T, T>);
}

// namespace ejovo {

//     template <class T>
//     void plus_eq(T& a, T& b);

// };


template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator+=(const AbsView& view) {
    return this->assign(view, ejovo::plus_eq<T, T>);
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator+=(const T& scalar) {
    return this->assign(scalar, ejovo::plus_eq<T, T>);
}

/**============================================
 *!               Operator -=
 *=============================================**/
template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator-=(const Matrix& mat) {
    return this->assign(mat, ejovo::minus_eq<T, T>);
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator-=(const AbsView& view) {
    return this->assign(view, ejovo::minus_eq<T, T>);
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator-=(const T& scalar) {
    return this->assign(scalar, ejovo::minus_eq<T, T>);
}
/**============================================
 *!               Operator *=
 *=============================================**/
template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator*=(const T& scalar) {
    return this->assign(scalar, ejovo::times_eq<T, T>);
}

/**============================================
 *!               Operator /=
 *=============================================**/
template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator/=(const T& scalar) {
    return this->assign(scalar, ejovo::divide_eq<T, T>);
}

// Loop through the elements x
template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::loop(std::function<void(T)> fn) {
    for (int i = 1; i <= this->size(); i++) {
        fn(this->at(i));
    }
    return *this;
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::loop_i(std::function<void(int)> fn) {
    for (int i = 1; i <= this->size(); i++) {
        fn(i);
    }
    return *this;
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::loop_ij(std::function<void(int, int)> fn) {
    for (int i = 1; i <= this->nrows(); i++) {
        for (int j = 1; j <= this->ncols(); j++) {
            // std::cerr << "RowView ----- (" << i << ", " << j << ")\n";
            // std::cerr << "this(i, j) : " << this->at(i, j) << "\n";
            fn(i, j);
        }
    }
    return *this;
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::mutate(std::function<T(T)> fn) {
    for (int i = 1; i <= this->size(); i++) {
        this->at(i) = fn(this->at(i));
    }
    return *this;
}

template <class T>
// template <class U>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::assign(const T& scalar, std::function<void(T&, const T&)> ass_op) {
    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), scalar);
    });
    return *this;
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::assign(const Matrix& mat, std::function<void(T&, const T&)> ass_op) {
    if (this->nrows() != mat.m || this->ncols() != mat.n) {
        std::cerr << "Matrix operands are not compatible\n";
        return *this;
    }

    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), mat(i, j));
    });
    return *this;
}

// template <class T>
// typename Matrix<T>::AbsView& Matrix<T>::AbsView::assign(Matrix&& mat, std::function<void(T&, const T&)> ass_op) {
//     if (this->nrows() != mat.m || this->ncols() != mat.n) {
//         std::cerr << "Matrix operands are not compatible\n";
//         return *this;
//     }

//     this->loop_ij([&] (int i, int j) {
//         ass_op(this->at(i, j), mat(i, j));
//     });
//     return *this;
// }

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::assign(const AbsView& view, std::function<void(T&, const T&)> ass_op) {
    if (this->nrows() != view.nrows() || this->ncols() != view.ncols()) {
        std::cerr << "Matrix operands are not compatible\n";
        return *this;
    }

    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), view(i, j));
    });
    return *this;
}

template <class T>
bool Matrix<T>::AbsView::valid_bounds(int i) {
    // If between 1 and size
    return (i >= 1) && (i <= this->size());
}

template <class T>
bool Matrix<T>::AbsView::valid_bounds(int i, int j) {
    bool a = (j >= 1) && (j <= this->ncols());
    bool b = (i >= 1) && (i <= this->nrows());
    return a && b;
}

template <class T>
void Matrix<T>::AbsView::print() {

    std::cout << this->nrows() << " x " << this->ncols() << " " << this->to_string() << "\n";

    for (int i = 1; i <= this->nrows(); i++) {
        std::cout << "|";

        for (int j = 1; j < this->ncols(); j++) {
            std::cout << this->operator()(i, j) << ", ";
        }

        std::cout << this->operator()(i, this->ncols()) << "|\n";
    }
}

template <class T>
Matrix<T> Matrix<T>::AbsView::to_matrix() const {

    Matrix out{this->nrows(), this->ncols()};

    out.loop_i([&] (int i) {
        out(i) = this->operator()(i);
    });

    return out;
}

template <class T>
T* Matrix<T>::AbsView::get_ptr() {
    return matrix().data.get();
}

template <class T>
T& Matrix<T>::AbsView::at(int n) {
    if (!this->valid_bounds(n)) {
        std::cerr << "Bound: " << n << " out of bounds " << this->size() << "\n";
        throw "Out of bounds accessing";
    }
    return this->operator()(n);
}

template <class T>
T& Matrix<T>::AbsView::at(int i, int j) {
    if (!this->valid_bounds(i, j)) {
        std::cerr << "Bounds: (" << i << ", " << j << "), out of bounds nrows: " << this->nrows() << " ncol: " << this->ncols() << "\n";
        throw "Out of bounds accessing";
    }
    return this->operator()(i, j);
}