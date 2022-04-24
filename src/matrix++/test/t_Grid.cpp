#include "ejovotest.hpp"

void t_Matrix();

using namespace ejovo;
int main() {


    std::cout << "Hello world\n";

    auto m = Matrix<double>::ij(10);
    auto m2 = Matrix<double>::zeros(5, 20);
    auto m3 = Matrix<double>::zeros(1, 2);

    std::cout << m.first() << std::endl;
    std::cout << m.last() << "\n";

    // m.fill(3);

    // m.print();

    assert(m.size() == m2.size());
    assert(m.is_same_size(m2));
    assert(m.isnt_same_size(m3));
    assert(m.is_valid_bound(4));
    assert(!m.is_valid_bound(1000));

    t_Matrix();

    return 0;
}

void t_Matrix() {

    // boolean tests
    auto t_bool = [] () {

        auto pos = Matrix<double>::from({1, 2, 3, 4, 5});
        auto pos_neg = Matrix<double>::from({1, -3, 3, 5, -3});
        auto neg = Matrix<double>::from({-3, -1, -5, -3, -4});

        assert(pos.all(ejovo::factory::gt<double>(0)));
        assert(pos.none(ejovo::factory::lt<double>(0)));

        assert(pos_neg.any(ejovo::factory::lt<double>(0)));
        assert(pos_neg.any(ejovo::factory::gt<double>(0)));

        assert(neg.all(ejovo::factory::lt<double>(0)));
        assert(neg.none(ejovo::factory::gt<double>(0)));

        assert(pos.count(ejovo::factory::lt<double>(0)) == 0);
        assert(pos.count(ejovo::factory::gt<double>(0)) == 5);

        assert(neg.count(ejovo::factory::lt<double>(0)) == 5);
        assert(neg.count(ejovo::factory::gt<double>(0)) == 0);

        assert(pos_neg.count(ejovo::factory::lt<double>(0)) == 2);
        assert(pos_neg.count(ejovo::factory::gt<double>(0)) == 3);

    };

    // fill and mutate tests
    auto t_fill = [] () {

        auto m = Matrix<double>::from({1, 2, 3, 4, 5});
        auto m2 = Matrix<double>::from({1, 2, 3, 4, 5});
        auto m3 = Matrix<double>::val(1, 5, 3);
        auto m4 = Matrix<double>::from({1, 2, 3, 99, 99});
        auto m5 = Matrix<double>::from({2, 4, 6, 198, 198});
        auto m6 = Matrix<double>::from({1, 2, 3, 198, 198});

        m2.fill(3);
        m.fill_if(99, ejovo::factory::gt<double>(3));

        assert(m3 == m2);
        assert(m == m4);

        m4.mutate([&] (auto x) { return x * 2; });

        assert(m4 == m5);

        m5.mutate_if(ejovo::factory::times(0.5), ejovo::factory::lt(10));

        assert(m5 == m6);

    };

    auto t_stats = [] () {

        auto x = ejovo::seq<double>(5);

        assert(x.sum() == 15);
        assert(x.mean() == 3);

        assert(x.var(false) == 2.5);
        assert(x.sd(false) == sqrt(2.5));
        assert(x.var() == 2);
        assert(x.sd() == sqrt(2));
        assert(x.min() == 1);
        assert(x.max() == 5);
        assert(x.prod() == 120);

        std::cout << "x.norm() -> " << x.norm() << "\n";
        std::cout << "sqrt(1...) -> " << sqrt(1 + 4 + 9 + 16 + 25) << "\n";

        // I lose precision that's carry
        assert(abs(x.norm() - sqrt(1 + 4 + 9 + 16 + 25)) < 0.0000001);

        auto y = Matrix<double>::from({-1, 2, 3, 4, -5});

        assert(y.sum_abs() == 15);
        assert(y.sum() == 3);


    };

    t_bool();
    t_fill();
    t_stats();














}