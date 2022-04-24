#pragma once

#include "declarations/AbsView.hpp"

namespace ejovo {

template <class T>
std::pair<int, int> Matrix<T>::AbsView::ind_to_ij(int n) const {
    int i = ((n  - 1) / this->nrow()) + 1;
    int j = (n - 1) % this->nrow() + 1;
    return std::make_pair<int, int>(std::move(i), std::move(j));
}

// template <class T>
// std::pair<int, int> convert_vector_indices_to_ij(const typename Matrix<T>::AbsView& mat, int n) {
//     int i = ((n  - 1) / mat.nrow()) + 1;
//     int j = (n - 1) % mat.nrow() + 1;
//     return std::make_pair<int, int>(std::move(i), std::move(j));
// }


/**========================================================================
 *!                           Abstract View
 *========================================================================**/
// template <class T>
// int Matrix<T>::AbsView::size() {
//     return this->ncol() * this->nrow();
// }


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
// template <class T>
// typename Matrix<T>::AbsView& Matrix<T>::AbsView::loop(std::function<void(T)> fn) {
//     for (int i = 1; i <= this->size(); i++) {
//         fn(this->at(i));
//     }
//     return *this;
// }

// template <class T>
// typename Matrix<T>::AbsView& Matrix<T>::AbsView::loop_i(std::function<void(int)> fn) {
//     for (int i = 1; i <= this->size(); i++) {
//         fn(i);
//     }
//     return *this;
// }

// template <class T>
// typename Matrix<T>::AbsView& Matrix<T>::AbsView::loop_ij(std::function<void(int, int)> fn) {
//     for (int i = 1; i <= this->nrow(); i++) {
//         for (int j = 1; j <= this->ncol(); j++) {
//             // std::cerr << "RowView ----- (" << i << ", " << j << ")\n";
//             // std::cerr << "this(i, j) : " << this->at(i, j) << "\n";
//             fn(i, j);
//         }
//     }
//     return *this;
// }

// template <class T>
// typename Matrix<T>::AbsView& Matrix<T>::AbsView::mutate(std::function<T(T)> fn) {
//     for (int i = 1; i <= this->size(); i++) {
//         this->at(i) = fn(this->at(i));
//     }
//     return *this;
// }

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
    if (this->nrow() != mat.m || this->ncol() != mat.n) {
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
//     if (this->nrow() != mat.m || this->ncol() != mat.n) {
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
    if (this->nrow() != view.nrow() || this->ncol() != view.ncol()) {
        std::cerr << "Matrix operands are not compatible\n";
        return *this;
    }

    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), view(i, j));
    });
    return *this;
}

// template <class T>
// bool Matrix<T>::AbsView::valid_bounds(int i) {
//     // If between 1 and size
//     return (i >= 1) && (i <= this->size());
// }

// template <class T>
// bool Matrix<T>::AbsView::valid_bounds(int i, int j) {
//     bool a = (j >= 1) && (j <= this->ncol());
//     bool b = (i >= 1) && (i <= this->nrow());
//     return a && b;
// }

// template <class T>
// Matrix<T>::AbsView& Matrix<T>::AbsView::print() {

//     std::cout << this->nrow() << " x " << this->ncol() << " " << this->to_string() << "\n";

//     for (int i = 1; i <= this->nrow(); i++) {
//         std::cout << "|";

//         for (int j = 1; j < this->ncol(); j++) {
//             std::cout << this->operator()(i, j) << ", ";
//         }

//         std::cout << this->operator()(i, this->ncol()) << "|\n";
//     }
// }

template <class T>
Matrix<T> Matrix<T>::AbsView::to_matrix() const {

    Matrix out{this->nrow(), this->ncol()};

    out.loop_i([&] (int i) {
        out(i) = this->operator()(i);
    });

    return out;
}

// template <class T>
// Matrix<T>& Matrix<T>::AbsView::matrix() const {
//     return mat;
// }

template <class T>
T* Matrix<T>::AbsView::get_ptr() {
    return matrix().data.get();
}

// template <class T>
// T& Matrix<T>::AbsView::at(int n) {
//     if (!this->valid_bounds(n)) {
//         std::cerr << "Bound: " << n << " out of bounds " << this->size() << "\n";
//         throw "Out of bounds accessing";
//     }
//     return this->operator()(n);
// }

// template <class T>
// T& Matrix<T>::AbsView::at(int i, int j) {
//     if (!this->valid_bounds(i, j)) {
//         std::cerr << "Bounds: (" << i << ", " << j << "), out of bounds nrow: " << this->nrow() << " ncol: " << this->ncol() << "\n";
//         throw "Out of bounds accessing";
//     }
//     return this->operator()(i, j);
// }

};