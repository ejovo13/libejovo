#include "libejovo.hpp"

#include <complex>

// Unified matrix type
// unified matrix of floats
class UniMatrix : public ejovo::Grid2D<float> {


public:

    UniMatrix(int m, int n);
    ~UniMatrix();

    // Override pure virtual functions
    float& operator[](int i) override;
    const float& operator[](int i) const override;
    std::size_t ncol() const override;
    std::size_t nrow() const override;

    ejovo::Matrix<float> to_matrix() const override;

    float *data;
    std::size_t m;
    std::size_t n;


};

float& UniMatrix::operator[](int i) {
    return data[i];
}

const float& UniMatrix::operator[](int i) const {
    return data[i];
}

std::size_t UniMatrix::ncol() const {
    return n;
}

std::size_t UniMatrix::nrow() const {
    return m;
}

ejovo::Matrix<float> UniMatrix::to_matrix() const {
    ejovo::Matrix<float> out (m, n);
    out.loop_i([&] (int i) {
        out(i) = this->operator()(i);
    });
    return out;
}


UniMatrix::UniMatrix(int __m, int __n)
    : m{__m}
    , n{__n}
    , data{nullptr}
{
    float *x;
    cudaMallocManaged(&x, (__m * __n) * sizeof(float));
    data = x;
}

// free the associated memory
UniMatrix::~UniMatrix() {
    if (!data) cudaFree(data);
}


__global__ void touch_data(int n, float *A) {

    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;

    for (int i = index; i < n; i += stride) {
        A[i] = 10;
    }

}

__global__ void touch_matrix(UniMatrix& A) {

    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;

    for (int i = index; i < A.size(); i += stride) {
        A[i] = 10;
    }


}


// Create a unified zeros matrix

// ejovo::Matrix<float> unified_matrix(int m, int n) {

//     ejovo::Matrix<float> m;

//     float *unified_data;
//     cudaMallocManaged(&unified_data, (m * n) * sizeof(float));

//     // m.data = std::unique_ptr




// }


int main() {

    using namespace ejovo;

    std::cout << "Hello world\n";

    ejovo::Matrix<double> m = ejovo::Matrix<double>::zeros(10, 3);
    m.print();

    const auto& [th, ph] = meshgrid<double>(linspace<double>(0.0, trig::two_pi, 10), linspace<double>(0.0, trig::pi, 10));


    auto Y01 = [&] (double th, double ph) {
        return 0.5 * sqrt(3.0 / trig::two_pi) * cos(th);
    };

    std::cout << "Azimuthal angle theta:\n";

    th.print();

    std::cout << "Polar angle phi: \n";

    ph.print();

    auto sph_harm = map2<double>(th, ph, Y01);

    std::cout << "Y01: \n";

    sph_harm.print();

    // contour(th, ph, sph_harm);

    // create memory
    // double *

    // Let me go ahead an compute some spherical harmonic functions...

    auto um = UniMatrix(10, 10);
    um.print();

    touch_data<<<1, 1>>>(100, um.data);

    um.print();

    um.fill(10); // This proves that the host can access the memory.

    um.print();



}