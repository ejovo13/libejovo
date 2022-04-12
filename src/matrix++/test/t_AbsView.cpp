#include "libejovo.hpp"

#include <cassert>

void t_RowView();
void t_ColView();
void t_MatView();
void t_VecView();


int main() {

    std::cout << "Hello lib\n";

    t_RowView();
    t_ColView();
    t_VecView();
    t_MatView();

    // Matrix<double>::RowView(m, 1);
    // Matrix<double>::RowView rv = Matrix<double>::RowView(m, 1);
    // Matrix<double>::RowView rv = m.get_row_view(1);
    // auto cv = m.get_col_view(1);

    // rv.print();
    // cv.print();



}

void t_RowView() {

    Matrix<double> m = Matrix<double>::i(5, 5);

    m.print();

    Matrix<double>::RowView rv(m, 1);

    rv = 10.0; // Unless I overload the operator = and assign for a RowView, this line becomes problematic!!!
    rv = Matrix<double>::zeros(1, 10); // fails
    rv = m.get_row_view(2); // fails

    (rv + 10).print();
    (10 + rv).print();
    (10 * rv).print();

    rv.assign(Matrix<double>::zeros(1, 5), ejovo::id_eq<double, double>);
    rv.assign(1.0, ejovo::id_eq<double, double>);
    rv.assign(m.get_row_view(2), ejovo::id_eq<double, double>);

    rv += 1.0;
    rv += m.get_row_view(3);
    rv += Matrix<double>::val(1, 5, 99);

    rv -= 10.0;
    rv -= m.get_row_view(5);
    rv -= Matrix<double>::ij(1, 5);

    rv *= 10;
    rv /= 5;

    m.print();

}

void t_ColView() {

    Matrix<double> m = Matrix<double>::i(5, 5);

    m.print();

    Matrix<double>::ColView cv(m, 1);

    cv = 10.0; // Unless I overload the operator = and assign for a RowView, this line becomes problematic!!!
    cv = Matrix<double>::zeros(1, 10); // fails
    cv = m.get_col_view(2); // fails

    cv.assign(Matrix<double>::zeros(5, 1), ejovo::id_eq<double, double>);
    cv.assign(1.0, ejovo::id_eq<double, double>);
    cv.assign(m.get_col_view(2), ejovo::id_eq<double, double>);

    cv += 1.0;
    cv += m.get_col_view(3);
    cv += Matrix<double>::val(5, 1, 99);

    cv -= 10.0;
    cv -= m.get_col_view(5);
    cv -= Matrix<double>::ij(5, 1);

    cv *= 10;
    cv /= 5;

    m.print();

}

void t_VecView() {

    auto m = Matrix<double>::i(5, 10);

    auto b = m > 10;
    b.print();

    auto bv = m[b];

    bv.print();

    bv = 10;

    m.print();

    bv = Matrix<double>::zeros(1, 40);

    m.print();

    bv = Matrix<double>::ones(5, 8);

    m.print();

}

void t_MatView() {

    auto m = Matrix<double>::i(4, 8);

    auto sub = m.submat(1, 2, 3, 4);

    m.print();
    sub.print();

    sub = 10;

    m.print();

}