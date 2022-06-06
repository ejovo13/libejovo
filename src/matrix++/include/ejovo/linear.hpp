// Definitions for linear algebra functions that operate on symmetric positive definite matrices

#include "types.hpp"
#include "core.hpp"

namespace ejovo {

    // Take a positive definite symmetric matrix and return the cholesky decomposition
    template<class T>
    Matrix<T> chol(const Matrix<T>& K) {

        if (!K.is_square()) return K.null();

        const std::size_t n = K.nrow();
        Matrix<T> L (n, n);

        for (std::size_t i = 1; i <= n; i++) {

            for (std::size_t j = 1; j <= i; j++) {

                T sum = 0;

                for (std::size_t k = 1; k < i; k++) {
                    sum += L(i, k) * L(j, k);
                }

                if (i == j) {
                    L(i, j) = std::sqrt(K(i, i) - sum);
                } else {
                    L(i, j) = (1.0 / L(i, j) * (K(i, j) - sum));
                }

            }
        }

        return L;
    }

    template <class T>
    Matrix<T> chol_gaxpy(const Matrix<T>& K) {

        if (!K.is_square()) return K.null();
        const std::size_t n = K.nrow();

        auto A = K.clone();

        A.print();

        for (std::size_t j = 1; j <= n; j++) {

            if (j > 1) {

                std::cout << "j := " << j << "\n";

                auto col = A.get_col_view(j, j, n);


                std::cout << "j:n := ";
                seq<int>(j, n).print();
                seq<int>(1, j - 1).print();

                auto sub = A(seq<int>(j, n), seq<int>(1, j - 1));
                // auto tmat = (A.get_row_view(j, 1, j - 1)).to_matrix().transpose();

                col.print();
                sub.print();
                // tmat.print();

                // A(j:n, j)
                // col = col - sub.dot(tmat);

            }

            auto col2 = A.get_col_view(j, j, n);
            col2 = col2 / std::sqrt(A(j, j));

        }

        return A;
    }


}