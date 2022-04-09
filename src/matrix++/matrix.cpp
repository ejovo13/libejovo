#include "ejovo.hpp"
#include "matrix.hpp"
#include "matrix_impl.hpp"
#include "interval.hpp"
#include "view.hpp"
#include "view_imp.hpp"


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

    Matrix<double> prod = ij % ij;

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


    auto g = [] (double x) {
        return x * x - 1;
    };

    auto g_prime = [] (double x) {
        return 2 * x;
    };

    double x0 = 0.5;

    auto root = opti::newtons_method<double>(g, g_prime, x0);

    auto test_fn = functions::ScalarFn<double>();
    double x = 10;

    std::cout << "test_fn applied to x: " << x << " " << test_fn(x) << "\n";

    auto test_fn2 = functions::ScalarFn<double>(
        [&] (auto x) {return x + 10;}
    );

    std::cout << "test_fn2 applied to x: " << x << " " << test_fn2(x) << "\n";

    auto my_x = linspace<double>(1, 10, 10);
    auto my_y = test_fn2(my_x);

    my_y.print();

    // std::cout << "root found as: " << root << "\n";
    root.print();


    auto X = linspace<double>(-trig::pi, trig::pi,  10000);

    auto cosx = cos(X);
    auto sinx = sin(X);

    std::cout << "cosx \\dot sinx" << cosx.dot(sinx) << "\n";


    // cosx.print();
    std::vector<Matrix<double>> vec {Matrix<double>::id(3), Matrix<double>::ij(4)};

    for (auto m : vec) {
        m.print();
    }

    auto Hilb = 1 / vec[1];
    Hilb.print();

    auto t_new = Matrix<double>::zeros(2, 5).to_vec();
    auto t_lin = linspace<double>(1, 10, 10).reshape(2, 5);
    t_new.print();
    t_lin.print();

    auto t_seq = linspace(1, 5, 3);
    auto t_seq2 = linspace(-3, 20, 5);
    // auto t_seq2 = seq(4);
    auto t_out = t_seq.outer_product(t_seq2);
    t_seq.print();
    t_seq2.print();

    // t_lin.t().print();
    t_out.print();


    functions::Interval<double> I{1, 2};

    I.chebynodes(10).print();
    I.linspace(10).print();

    auto test_log = ejovo::logspace<double>(1.0, 10.0, 10, 2); // {2^1, ..., 2^10}
    test_log.print();

    I.logspace(10).print();

    I.print();
    // log
    std::cout << ejovo::log_base(10, 2);
    std::cout << ejovo::log_base(10, 1);

    Matrix<double> ttt = Matrix<double>::row(10);
    ttt.print();
    ttt = Matrix<double>::col(10);
    ttt.print();

    ttt += Matrix<double>::col(10, 5);
    ttt.print();

    ttt = Matrix<double>::id(10);

    loop_col(ttt, [&] (int i, int j) {
        ttt(i, j) += 5;
    });

    mut_row(ttt, [&] (auto x) {
        return x + 10;
    }, 3);

    // mut_diag(ttt, [&] (auto x) {
    //     return x * 3 + 99;
    // }, 1);


    ttt.print();


    ttt.mutate([&] (auto x) {
        return x + 10;
    });

    ttt.print();

    ttt.map([&] (auto x) {
        return 0;
    }).print();

    ttt.print();
    ttt.filter([&] (auto x) {
        return x > 10;
    }).print();

    ttt.fill_if(0, [&] (double x) {
        return x > 10;
    });

    ttt.print();

    ttt.sqrt().print();
    ttt.cbrt().pow(6).print();

    // ttt.filter_gt(10).print();
    ttt.sqrd().filter_gt(10).print();


    ttt = seq<double>(5);
    ttt.print();
    std::cout << ttt.norm() << "\n";
    std::cout << ttt.mean() << "\n";
    std::cout << ttt.sum() << "\n";
    std::cout << ttt.sqrd().sum() << "\n";
    std::cout << ttt.sd() << "\n";
    std::cout << ttt.sd(false) << "\n";
    std::cout << ttt.var() << "\n";
    std::cout << ttt.var(false) << "\n";
    std::cout << ttt.min() << "\n";
    std::cout << ttt.max() << "\n";

    // auto Amat = Matrix::zeros()
    auto Amat = Matrix<double>::zeros(10);
    auto Amat_clone = Amat.clone();

    std::cout << Amat.data.get() << std::endl;
    std::cout << Amat_clone.data.get() << std::endl;

    auto my_seq = seq(5);
    auto my_seq2 = seq(3);

    // my_seq.rep_col(4).print();
    // my_seq.rep_row(3).print();

    auto tup = ejovo::meshgrid(my_seq, my_seq2);

    std::get<0>(tup).print();
    std::get<1>(tup).print();


    std::get<0>(tup).test([&] (auto x) {
        return x == 1;
    }).print();

    Id.print();

    View v{Id, seq(2), seq(3)};

    v.print();

    v = 4;

    Id.print();

    v = Matrix<double>::val(2, 3, 50);
    v.print();
    Id.print();

    Id.view_row(1).print();
    Id.view_col(3).print();

    Id.view_col(1).mutate([&] (auto x) {
        return x + 10;
    });

    Id.print();

    View<double> v2 = Id(seq(5), seq(3));

    v2.print();
    v2 = 13;
    Id.print();

    ttt = Matrix<double>::from({1, 2, 3, 4, 5, 6});
    ttt.print();
    ttt = Matrix<double>::from({1, 2, 3, 4, 5, 6}, 6, 1);
    ttt.print();
    ttt = Matrix<double>::from({1, 2, 5, 6, 9, 8, 0, 19}, 4, 2);
    ttt.print();
    auto id2 = Matrix<double>::id(2);

    id2.print();

    auto kron = id2.kronecker_product(id2);
    kron.print();

    auto lhs = Matrix<int>::from({1, 2, 3, 4}, 2, 2);
    auto rhs = Matrix<int>::from({0, 5, 6, 7}, 2, 2);

    lhs.kronecker_product(rhs).print();

    lhs = Matrix<int>::from({1, -4, 7, -2, 3, 3}, 2, 3);
    rhs = Matrix<int>::from({8, -9, -6, 5, 1, -3, -4, 7, 2, 8, -8, -3, 1, 2, -5, -1}, 4, 4);

    lhs.print();
    rhs.print();

    lhs.kronecker_product(rhs).print();


    lhs = Matrix<int>::from({1, 2, 3, 4}, 2, 2);
    const Matrix<int> id22 = Matrix<int>::id(2);

    id22.print();
    lhs.print();

    id22.hadamard_product(lhs).print();

}