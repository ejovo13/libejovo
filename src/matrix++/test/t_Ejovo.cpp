#include "libejovo.hpp"


// Playing around with concepts
namespace ejovo {

template <class T>
concept Cloneable = requires (const Grid1D<T>& grid) {
    // {grid.clone()} -> std::same_as<Matrix<T>>;
    grid.clone();
};

template <class T>
concept Zeroed = requires (T t, int m, int n) {
    t.zeros(m, n);
};

template <class T>
concept Printable = requires (T t) {
    t.print();
};


template <class T>
concept PrintCloneable = Cloneable<T> && Printable<T>;

template <class T>
concept Reproducible = Cloneable<T> && Zeroed<T>;


void printClone(Cloneable auto m) {
    printf("Calling printClone\n");
    m.clone().print();
}

    namespace conc {









    };



};


int main() {

    using namespace ejovo;
    using namespace ejovo::factory;

    std::cout << "Hello Ejovo\n";

    auto m = ejovo::seq<double>(10.0);

    auto mrand = Matrix<double>::rand(4, 5, -10, 10);

    m.print();
    m.map(times(2)).print();

    m.sqrd().print();

    mrand.print();

    mrand.abs().print();
    mrand.diff().print();

    auto mm = Matrix<double>::from({1, 2, 3, 4}, 2, 2);
    mm.print();

    m.sqrt().print();
    m.sqrd().print();

    m.cbrt().print();
    m.cubd().print();

    m.repcol(10).print();
    m.reprow(10).print();

    return 0;
}