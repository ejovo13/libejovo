#include <memory>
#include <iostream>
#include <cstring>
#include <cmath>

template <class T>
class Matrix {

    public:

    int m;
    int n;

    std::unique_ptr<T[]> data;

    //======= constructors
    Matrix();
    Matrix(int m); // create a column vector
    Matrix(int m, int n);
    Matrix(const Matrix& rhs);
    Matrix(Matrix&& rhs);


    /**----------------------
     *!    operators
     *------------------------**/
    Matrix& operator=(const Matrix& rhs);
    // Matrix& operator=(Matrix&& rhs);
    Matrix& operator=(Matrix rhs);

    // call memcpy to copy the data
    std::unique_ptr<T[]> copyData() const;

    int size() const;
    void print() const;
    void fill(T val);
    void reset(); // set data to nullptr, m and n to 0.
    // void mutate()

    /**========================================================================
     *!                           Transformations
     *========================================================================**/
    // create a new matrix whose data is a copy
    Matrix as_vector(); // return a copy of this data in column form
    Matrix as_colvec(); // just a call to as_vector
    Matrix as_rowvec();

    bool isSameSize(const Matrix &rhs) const;
    bool canMultB(const Matrix &rhs) const;
    bool cantMultB(const Matrix &rhs) const;
    bool canAddB(const Matrix &rhs) const;
    bool cantAddB(const Matrix &rhs) const;

    void reshape(std::tuple<int, int> ind);
    void reshape(Matrix& ind);
    void reshape(int i, int j);

    // void to_vector(); // Computing the size of the matrix, change the elements so that the matrix is a col vector;
    // void to_rowvec();
    void to_col();
    void to_vec();
    void to_row();

    Matrix diff() const; // return the back elements minus the front elements


    T& operator()(int i);
    const T& operator()(int i) const;
    T& operator()(int i, int j);
    const T& operator()(int i, int j) const;

    T& at(int i);
    T& at(int i, int j);
    const T& at(int i) const;
    const T& at(int i, int j) const;

    // interpret the indices as INTEGERS and
    Matrix operator()(const Matrix<int> ind);

    T& operator[](int i);
    const T& operator[](int i) const;

    /**========================================================================
     *!                           Binary operations
     *========================================================================**/
    // Take the dot product as if we were VECTORS
    T dot(const Matrix& rhs) const;
    T dot(const Matrix& rhs, int i, int j) const; // dot the ith of this row with the jth column of rhs


    //* Matrix Moperators
    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    Matrix& operator%=(const Matrix& rhs); // hadamard multiplication

    //* Matrix + scalar
    Matrix& operator+=(const T scalar);
    Matrix& operator-=(const T scalar);
    Matrix& operator/=(const T scalar);
    Matrix& operator*=(const T scalar);


    Matrix operator-() const;
    Matrix operator*(const Matrix& rhs) const;

    friend Matrix operator+(Matrix lhs, const Matrix rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Matrix operator+(Matrix lhs, const T scalar) {
        lhs += scalar;
        return lhs;
    }

    friend Matrix operator+(const T scalar, Matrix rhs) {
        rhs += scalar;
        return rhs;
    }

    // friend Matrix operator+(const T scalar )

    // Matrix& operator-=(const Matrix& rhs);

    // these values are passed in by  copy
    friend Matrix operator-(Matrix lhs, const Matrix rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Matrix operator-(Matrix lhs, const T scalar) {
        lhs -= scalar;
        return lhs;
    }

    friend Matrix operator-(const T scalar, Matrix rhs) {
        rhs -= scalar;
        return rhs;
    }

    friend Matrix operator*(const T scalar, Matrix rhs) {
        rhs *= scalar;
        return rhs;
    }

    friend Matrix operator*(Matrix lhs, const T scalar) {
        lhs *= scalar;
        return lhs;
    }

    friend Matrix operator%(Matrix lhs, const Matrix rhs) {
        lhs %= rhs;
        return lhs;
    }


    // fried Matrix operator-(Mat)



    // matrix transpose
    Matrix t();

    // Matrix multiplication




    /**========================================================================
     *!                           Inquiry functions
     *========================================================================**/
    bool is_square();
    bool is_vector(); // return true if one of the dimensions are 1
    bool is_colvec();
    bool is_rowvec();

    int mindim();

    /**========================================================================
     *!                           Static functions
     *========================================================================**/
    static Matrix<T> zeros(int m);
    static Matrix<T> zeros(int m, int n);
    static Matrix<T> ones(int m);
    static Matrix<T> ones(int m, int n);
    static Matrix<T> ij(int m, int n);
    static Matrix<T> id(int n);
    static Matrix<T> id(int m, int n);

    static Matrix<T> hilbert(int n);
    static Matrix<T> hilbert(int m, int n);

    static Matrix<T> diagonal(Matrix& vals);

    /**========================================================================
     *!                           Matrix interface to ejovo functions
     *========================================================================**/

};


/**========================================================================
 *!                           Looping functions
 *========================================================================**/
// loop elements i, j and set i, j according to what f(i, j) returns
template <class T, class BinaryFn>
void loop_ij(Matrix<T>& A, BinaryFn f) {
    for (int i = 1; i <= A.m; i++) {
        for (int j = 1; j <= A.n; j++) {
            f(i, j);
        }
    }
}

template <class T, class UnaryFn>
void loop_i(Matrix<T>& A, UnaryFn f) {
    for (int i = 1; i <= A.size(); i++) {
        f(i);
    }
}

template <class T, class UnaryFn>
void loop_diag(Matrix<T>& A, UnaryFn f, int diag = 0) {
    for (int d = 1 + diag; d <= A.mindim(); d++) {
        f(d);
    }
}

/**========================================================================
 *!                           Ejovo namespace
 *========================================================================**/
namespace ejovo {

    template<class T = double>
    Matrix<T> linspace(T start, T end, int n = 100) {

        T diff = (end - start) / (n - 1);

        Matrix<T> lin{n};

        loop_i(lin, [&] (int i) {lin(i) = start + (i - 1) * diff;});
        return lin;
    }

    template<class T, class UnaryFn>
    Matrix<T> map(const Matrix<T>& mat, UnaryFn f) {
        // create a copy
        // std::cout << "Calling map\n";
        Matrix mat_copy = mat;
        // std::cout << "Created copy:\n";
        // mat_copy.print();
        loop_i(mat_copy, [&] (int i) {mat_copy(i) = f(mat(i));});
        return mat_copy;
    }

    template<class T, class BinaryFn>
    T reduce(const Matrix<T>& mat, BinaryFn f) {

        if (mat.size() == 0) {
            std::cerr << "Trying to reduce a matrix of size 0, returning default value of T\n";
            return T{};
        }
        if (mat.size() == 1) return mat(1);

        T out{mat(1)};
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
        return reduce(mat, [] (auto x, auto y) {return x * y;});
    }

    template<class T>
    T min(const Matrix<T>& mat) {
        return reduce(mat, [] (auto x, auto y) {return x < y ? x : y;});
    }

    template<class T>
    T max(const Matrix<T>& mat) {
        return reduce(mat, [] (auto x, auto y) {return x > y ? x : y;});
    }

    template<class T>
    Matrix<T> pow(const Matrix<T>& mat, int n) {
        return map(mat, [&] (auto x) {return std::pow(x, n);});
    }

    template<class T>
    T pnorm(const Matrix<T>& mat, int p = 2) {
        auto mat_pow = pow(mat, p);
        return sum(mat_pow);
    }

    // Make a sequence from 1 to n
    Matrix<int> seq(int n) {
        Matrix<int> out{n};
        loop_i(out, [&] (int i) {out(i) = i;});
        return out;
    }

    Matrix<int> seq(int start, int end) {
        const int len_seq = (end - start) + 1;
        Matrix<int> out{len_seq};
        out.fill(0);
        loop_i(out, [&] (int i) {
            out(i) = start + (i - 1);
        });
        return out;
    }


    template<class T>
    T mean(const Matrix<T>& mat) {
        int len = mat.size();
        return sum(mat) / len;
    }

    template<class T>
    T sd(const Matrix<T>& mat) {

    }

    template<class T, class Predicate>
    Matrix<T> filter(Matrix<T> mat, Predicate f) {
        // make one pass to count how many times the result is true
        int count = 0;
        loop_i(mat, [&] (int i) {
            if (f(mat(i))) count ++;
        });

        Matrix<T> out{count};

        int out_i = 1;
        loop_i(mat, [&] (int i) {
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


};

using namespace ejovo;

/**========================================================================
 *!                           Constructors
 *========================================================================**/
template <class T> Matrix<T>::Matrix() : m{0}, n{0} { this->data = nullptr; }

template <class T> void Matrix<T>::reset() {
    this->m = 0;
    this->n = 0;
    this->data = nullptr;
}

template <class T> Matrix<T>::Matrix(int n) : m{1}, n{n} {
    this->data = std::unique_ptr<T[]>(new T [n]);
}

template <class T> Matrix<T>::Matrix(int m, int n) : m{m}, n{n} {
    this->data = std::unique_ptr<T[]>(new T [m * n]);
}

template <class T> std::unique_ptr<T[]> Matrix<T>::copyData() const {
    int n = this->size();

    // this->print();
    auto ptr = new T[n]; // allocate the proper space
    memcpy(ptr, this->data.get(), n * sizeof(T)); // copy the data on over
    return std::unique_ptr<T[]>(ptr);
}

template <class T> Matrix<T>::Matrix(const Matrix& rhs) : m{rhs.m}, n{rhs.n} {
    this->data = rhs.copyData();
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& rhs) {
    std::cerr << "Performing copy assignment\n";
    if (this == &rhs)
        return *this;

    this->data = rhs.copyData();
    this->m = rhs.m;
    this->n = rhs.n;

    return *this;
}

// template <class T>
// Matrix<T>& Matrix<T>::operator+=(const Matrix& rhs) {

//     // check if the matrices are compatible for matrix addition.
//     if (!this->canAddB(rhs)) {
//         std::cerr << "Can't add two matrices\n";
//         return *this;
//     }

//     loop_i(rhs, [&] (int i) {
//         this->at(i) += rhs(i);
//     });

//     return *this;
// }



// template <class T>
// Matrix<T>& Matrix<T>::operator=(Matrix&& rhs) {
//     std::cerr << "Performing move assignment =\n";
//     if (this == &rhs)
//         return *this;

//     this->data = rhs.copyData();
//     this->m = rhs.m;
//     this->n = rhs.n;

//     rhs.data = nullptr;
//     rhs.m = 0;
//     rhs.n = 0;

//     return *this;
// }

// template <class T>
// Matrix<T>& Matrix<T>::operator=(const Matrix rhs) {
//     std::swap(data, rhs.data);
//     return *this;
// }

/**========================================================================
 *!                           Indexing operators
 *========================================================================**/
template <class T>
T& Matrix<T>::operator[](int i) {
    return (this->data)[i];
}

template <class T>
const T& Matrix<T>::operator[](int i) const {
    return (this->data)[i];
}

template <class T>
T& Matrix<T>::operator()(int i) {
    return (this->data)[i - 1];
}

template <class T>
T& Matrix<T>::operator()(int i, int j) {
    return this->operator()(i*this->n + j  - this->n);
}

template <class T>
const T& Matrix<T>::operator()(int i) const {
    return (this->data)[i - 1];
}

template <class T>
const T& Matrix<T>::operator()(int i, int j) const {
    return this->operator()(i*this->n + j - this->n);
}

template <class T>
T& Matrix<T>::at(int i) {
    return this->operator()(i);
}

template <class T>
T& Matrix<T>::at(int i, int j) {
    return this->operator()(i, j);
}

template <class T>
const T& Matrix<T>::at(int i) const {
    return this->operator()(i);
}

template <class T>
const T& Matrix<T>::at(int i, int j) const {
    return this->operator()(i, j);
}

// template <class T>
// T& Matrix<T>::at(int i) {
//     return this->operator()(i);
// }

// extract the specified integers
template <class T>
Matrix<T> Matrix<T>::operator()(const Matrix<int> ind) {
    // Assume all the indices are legitamete
    const int n = this->size();
    // check the bounds
    auto valid_ind = ejovo::filter(ind, [&] (int x) {
        return x >= 1 && x <= n;
    });

    // now extract those valid indices
    Matrix<T> out{valid_ind.size()};

    loop_i(valid_ind, [&] (int i) {
        out(i) = this->at(ind(i));
    });

    return out;
}



/**========================================================================
 *!                           Mutations
 *========================================================================**/
template <class T>
void Matrix<T>::fill(T val) {
    for (int i = 0; i < this->size(); i++) {
        this->operator()(i + 1) = val;
        // std::cout << "filling i: " << i << "\n";
    }
}

template <class T>
int Matrix<T>::size() const {
    return this->m * this->n;
}

template <class T>
void Matrix<T>::print() const {

    std::cout << this->m << " x " << this->n << " matrix\n";

    for (int i = 1; i <= this->m; i++) {
        std::cout << "|";

        for (int j = 1; j < this->n; j++) {
            std::cout << this->operator()(i, j) << ", ";
        }

        std::cout << this->operator()(i, this->n) << "|\n";
    }
}

template <class T>
Matrix<T> Matrix<T>::t() {

    Matrix<T> A{this->n, this->m};

    loop_ij(A, [&] (int i, int j) {A(i, j) = this->operator()(j, i);});
    return A;
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix& rhs) {

    if (this->cantAddB(rhs)) {
        std::cerr << "Trying to add incompatible matrices\n";
        return *this;
    }
    // element-wise addition
    loop_i(*this, [&] (int i) {
        this->at(i) += rhs(i);
    });
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix& rhs) {

    if (this->cantAddB(rhs)) {
        std::cerr << "Trying to add incompatible matrices\n";
        return *this;
    }
    // element-wise addition
    loop_i(*this, [&] (int i) {
        this->at(i) -= rhs(i);
    });
    return *this;
}

//========================= Scalar operations ====================
template <class T>
Matrix<T>& Matrix<T>::operator+=(const T scalar) {
    loop_i(*this, [&] (int i) {
        this->at(i) += scalar;
    });
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const T scalar) {
    // element-wise addition
    loop_i(*this, [&] (int i) {
        this->at(i) -= scalar;
    });
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const T scalar) {
    loop_i(*this, [&] (int i) {
        this->at(i) *= scalar;
    });
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator/=(const T scalar) {
    loop_i(*this, [&] (int i) {
        this->at(i) /= scalar;
    });
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator-() const {
    Matrix dup{*this};
    loop_i(dup, [&] (int i) {dup(i) = -this->operator()(i);});
    return dup;
}

// hadamard multiplication
template <class T>
Matrix<T>& Matrix<T>::operator%=(const Matrix& rhs) {

    if (this->size() != rhs.size()) {
        std::cerr << "Not the same size, cant perform hadamard multiplication\n";
        return *this;
    }
    loop_i(*this, [&] (int i) {
        this->at(i) *= rhs(i);
    });
    return *this;
}

template <class T>
T Matrix<T>::dot(const Matrix& rhs) const {
    auto had_res = *this % rhs;
    return sum(had_res);
}

template <class T>
T Matrix<T>::dot(const Matrix& rhs, int i, int j) const {
    // we are assuming that the sizes are legit
    T total = 0;
    for (int k = 1; k <= this->n; k++) {
        total += (this->at(i, k) * rhs(k, j));
    }
    return total;
}


// Matrix multiplication!!!
template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix&rhs) const {

    if (this->cantMultB(rhs)) {
        std::cerr << "Can't multiply matrices\n";
        return zeros(1);
    }
    // o(n3), so we will have 3 loops

    // create output matrix
    Matrix out{this->m, rhs.n};

    for (int i = 1; i <= out.m; i++) {
        for (int j = 1; j <= out.n; j++) {
            out(i, j) = this->dot(rhs, i, j);
        }
    }
    return out;
}

template <class T>
Matrix<T> Matrix<T>::diff() const {
    // create matrix that is smaller
    Matrix out{this->size() - 1};
    for (int i = 0; i < out.size(); i++) {
        out[i] = this->operator[](i + 1) - this->operator[](i);
    }
    return out;
}


template <class T> Matrix<T>::Matrix(Matrix&& rhs) : m{rhs.m}, n{rhs.n} {

    this->data = std::move(rhs.data);
    this->m = rhs.m;
    this->n = rhs.n;

    rhs.data = nullptr;
    rhs.m = 0;
    rhs.n = 0;
}

/**========================================================================
 *!                           Inquiry functions
 *========================================================================**/

template <class T>
int Matrix<T>::mindim() {
    return this->m < this->n ? this->m : this->n;
}


/**========================================================================
 *!                           Static functions
 *========================================================================**/
template <class T>
Matrix<T> Matrix<T>::zeros(int m) {

    Matrix zero{m};
    zero.fill(0);
    return zero;
}

template <class T>
Matrix<T> Matrix<T>::zeros(int m, int n) {

    Matrix zero(m, n);
    zero.fill(0);
    return zero;
}

template <class T>
Matrix<T> Matrix<T>::ones(int m) {

    Matrix one{m};
    one.fill(1);
    return one;
}

template <class T>
Matrix<T> Matrix<T>::ones(int m, int n) {

    Matrix one(m, n);
    one.fill(1);
    return one;
}

template <class T>
Matrix<T> Matrix<T>::id(int n) {
    // take 1 as the identity element...
    Matrix out = zeros(n, n);
    loop_diag(out, [&] (int d) {
        out(d, d) = 1;
    });

    return out;
}

template <class T>
Matrix<T> Matrix<T>::ij(int m, int n) {
    Matrix out(m, n);
    loop_ij(out, [&] (int i, int j) {
        out(i, j) = i + j - 1;
    });
    return out;
}

template <class T>
Matrix<T> Matrix<T>::hilbert(int n) {
    Matrix out = Matrix::ij(n, n);
    loop_i(out, [&] (int i) {
        out(i) = 1 / out(i);
    });
    return out;
}

/**========================================================================
 *!                           Transformations
 *========================================================================**/
template <class T>
void Matrix<T>::reshape(std::tuple<int, int> ind) {

    // verify that the first times the second is legitimate
    if (std::get<0>(ind) * std::get<1>(ind) != this->size()) {
        std::cerr << "Sizes not compatible for reshaping. Aborting.\n";
        return;
    }

    this->m = std::get<0>(ind);
    this->n = std::get<1>(ind);

}

template <class T>
void Matrix<T>::reshape(int m, int n) {

    // verify that the first times the second is legitimate
    if (m * n != this->size()) {
        std::cerr << "Sizes not compatible for reshaping. Aborting.\n";
        return;
    }

    this->m = m;
    this->n = n;
}


template <class T>
void Matrix<T>::to_row() {
    this->reshape(1, this->size());
}

template <class T>
void Matrix<T>::to_col() {
    this->reshape(this->size(), 1);
}

template <class T>
void Matrix<T>::to_vec() {
    this->to_col();
}

template <class T>
Matrix<T> Matrix<T>::as_vector() {
    Matrix out{*this}; // copy this matrix
    out.to_vec();
}

template <class T>
Matrix<T> Matrix<T>::as_colvec() {
    Matrix out{*this}; // copy this matrix
    out.to_col();
}

template <class T>
Matrix<T> Matrix<T>::as_rowvec() {
    Matrix out{*this}; // copy this matrix
    out.to_row();
}








/**========================================================================
 *!                           Inquiry functions
 *========================================================================**/
template <class T>
bool Matrix<T>::is_square() {
    return this->m == this->n;
}

// Eventual I should just have a parent class that is a vector
template <class T>
bool Matrix<T>::is_vector() {
    return this->m == 1 || this->n == 1;
}

template <class T>
bool Matrix<T>::is_colvec() {
    return this->n == 1;
}

template <class T>
bool Matrix<T>::is_rowvec() {
    return this->m == 1;
}

template <class T>
bool Matrix<T>::canMultB(const Matrix &rhs) const {
    return this->n == rhs.m;
}

template <class T>
bool Matrix<T>::cantMultB(const Matrix &rhs) const {
    return !(this->canMultB(rhs));
}

template <class T>
bool Matrix<T>::isSameSize(const Matrix &rhs) const {
    return this->m == rhs.m && this->n == rhs.n;
}

template <class T>
bool Matrix<T>::canAddB(const Matrix &rhs) const {
    return this->isSameSize(rhs);
}

template <class T>
bool Matrix<T>::cantAddB(const Matrix &rhs) const {
    return !(this->isSameSize(rhs));
}


/**========================================================================
 *!                           Functional style things
 *========================================================================**/

namespace std {
    double power(double __x, double __y) {
        return pow(__x, __y);
    }
}



int main() {

    std::cout << "Hello world\n";

    Matrix<double> m;
    Matrix<double> a{5};


    std::cout << "M has size: " << m.size() << std::endl;

    a.print();

    Matrix<double> z = Matrix<double>::zeros(10, 5);

    auto z1 = Matrix<double>::zeros(10);

    z.print();

    z(1, 1) = 10;
    z(1, 2) = 11;
    z.print();
    z(1) = 5;
    z(2) = 15;
    z(3) = 3;

    // for (int i = 0; i < z.size(); i ++) {
    //     // for (int j = 1)
    //     z[i] = i;
    // }

    std::cout << "size: " << z.size() << "\n";

    for (int i = 1; i <= z.m; i ++) {
        for (int j = 1; j <= z.n; j ++) {
            z(i, j) = i + j - 1;
        }
    }

    // for (int i = 0; i < z.size(); i ++) {
    //     z[i] = i;
    // }
    // z(2, 8) = 14;
    z1.fill(10);
    z1.print();
    // z1.print();

    z1.t().print();

    // std::cout << "z1.data: " << z1.data.get() << "\n";
    // std::cout << "z1.data[0]: " << z1.data[0] << "\n";
    auto h = ejovo::linspace<double>(0, 10);
    auto i = ejovo::linspace<int>(1, 10, 10);

    auto i2 = ejovo::map(i, [] (int x) {return x * 2;});

    h.print();
    i.print();
    i2.print();

    auto out = ejovo::reduce(i2, [] (auto x, auto y) {return x + y;});
    std::cout << "out : " << out << "\n";

    std::cout << "max: " << ejovo::max(i2) << "\n";
    std::cout << "min: " << ejovo::min(i2) << "\n";

    auto i3 = ejovo::pow(i2, 2);

    // auto i3 = ejovo::pow(i2, 2);
    i3.print();

    i3 += i2;
    i3.print();
    i3 -= i2;
    i3.print();
    (-i3).print();
    (i3 + -i3).print();
    Matrix<double>::ones(10).print();
    ejovo::seq(10).print();
    ejovo::filter(ejovo::seq(10), [] (auto x) {return x > 5;}).print();

    using namespace ejovo;

    Matrix<int> s = seq(15);
    auto in = seq(2, 10);
    in.print();
    // Matrix<int> b = s;
    Matrix<int> b = s(in);
    // b = s(in);
    std::cout << "b length: " << b.size() << std::endl;

    b.print();

    seq(10)(seq(2)).print();


    auto m_int = Matrix<int>::ij(5, 6);
    m_int.print();
    auto H = Matrix<double>::hilbert(10);
    H.print();

    H += 10;
    H.print();
    H *= 0.5;
    H.print();
    H /= 0.5;
    H.print();

    auto Id = Matrix<double>::id(10);
    Id.print();
    auto res = Id + -1;
    res.print();

    (res - 5).print();
    (10 + res).print();
    (10 * res).print();

    std::cout << "========== Hadamard product ===========\n";
    auto two_id = 2 * Id;
    two_id.print();

    auto ij = Matrix<double>::ij(10, 10);

    Matrix prod = ij % ij;

    // ij %= two_id;
    ij.print();
    prod.print();

    Matrix<double> t1(2, 1);
    t1(1) = 1;
    t1(2) = -1;

    Matrix<double> t2(1, 2);
    t2(1) = 3;
    t2(2) = 3;

    std::cout << "dot: " << t1.dot(t2) << "\n";

    auto t_prod = Matrix<double>::id(2) * t1;
    t_prod.print();

    mutate(t_prod, [] (auto x) {
        return x * 2;
    });



    t_prod.print();

    Matrix<double> space = linspace<double>(1, 10, 10);
    space.print();
    printf("Differences:\n");
    space.diff().print();


}