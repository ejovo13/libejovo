#pragma once

#include <iostream>
#include <fstream>
#include "types.hpp"

namespace ejovo {

/**========================================================================
 *!                           R interface
*========================================================================**/
template <class T>
class Dataframe {

public:

    std::vector<Matrix<T>> cols;
    std::vector<std::string> col_names; // This better be the same size as cols...
    std::size_t nrow;


    // Have a vector of matrices
    // Dataframe(std::initializer_list<Matrix<T>> list, std::initializer_list<std::string> names);
    Dataframe(std::vector<Matrix<T>> data, std::vector<std::string> names);

    bool to_csv(const std::string filename);


private:





};

// template <class T>
// Dataframe<T>::Dataframe(std::initializer_list<Matrix<T>> data, std::initializer_list<std::string> names) : cols{}, cols_names{}, nrow{0} {

//     int len_mat = list.begin()->size();
//     int n_added = 0;

//     for (auto mat : list) {
//         if (mat.size() != len_mat) continue;
//         cols.push_back(mat);
//         n_added ++;
//     }

//     nrow = n_added;

// }

// random Numeric concept
template<typename NumericType>
concept Numeric = std::is_arithmetic<NumericType>::value;

template <class T>
Dataframe<T>::Dataframe(std::vector<Matrix<T>> data, std::vector<std::string> names) : cols{data}, col_names{names}, nrow{data.begin()->size()} {}

template <Numeric T>
Dataframe<T> df(std::initializer_list<Matrix<T>> data, std::initializer_list<std::string> names) {

    // check to make sure that all of the vectors have the same size
    std::vector<Matrix<T>> cols;
    std::vector<std::string> col_names;

    int size = data.begin()->size();

    for (auto mat : data) {
        if (mat.size() != size) throw "You a dumb bitch";
        cols.push_back(mat);
    }

    for (auto n : names) {
        col_names.push_back(n);
    }

    Dataframe<T> out (cols, col_names);
    return out;
}


template <class T>
bool Dataframe<T>::to_csv(const std::string filename) {

    std::ofstream my_file;

    my_file.open(filename);
    const int ncol = cols.size();

    for (int i = 0; i < ncol - 1; i++) {
        my_file << col_names.at(i) << ",";
    }

    my_file << col_names.at(ncol - 1) << "\n";

    // iterate through length of the elements of mat
    for (int i = 1; i <= nrow; i++) {

        // Now add a row
        for (int j = 0; j < ncol - 1; j++) {

            my_file << cols.at(j).at(i) << ",";
        }

        my_file << cols.at(ncol - 1).at(i) << "\n";
    }

    my_file.close();


    return true;
}

// Given a csv in x,y format, construct the r code to draw a simple plot
std::string create_r_plot(std::string filename) {

    return std::string(R"(

library(ggplot2)
library(tibble)
df <- as_tibble(read.csv(')") + filename + ".csv'" + R"())

p <- df |> ggplot(aes(x, y)) + geom_line()

ggsave(')" + filename + ".png" + R"(', p, device = 'png')

)";
}

// Assuming I have a csv in x,y,z format + an R EXPRESSION for the breaks,
std::string create_contour_plot(std::string filename) {

    return std::string(R"(

library(ggplot2)
library(tibble)
df <- as_tibble(read.csv(')") + filename + ".csv'" + R"())

p <- df |> ggplot(aes(x, y, z = z)) + geom_contour_filled()

ggsave(')" + filename + ".png" + R"(', p, device = 'png')

)";
}

std::string create_contour_plot_breaks(std::string filename, std::string rexp_breaks = "", int width = 5, int height = 5) {

    if (rexp_breaks == "") {
        std::cout << "Default breaks\n";
        return std::string(R"(

library(ggplot2)
library(tibble)
df <- as_tibble(read.csv(')") + filename + ".csv'" + R"())

p <- df |> ggplot(aes(x, y, z = z)) + geom_contour_filled() + theme(legend.position = "none")

ggsave(')" + filename + ".png" + R"(', p, device = 'png', width = )" + std::to_string(width) + R"(, height = )" + std::to_string(height) + R"()

)";

    } else {

        return std::string(R"(

library(ggplot2)
library(tibble)
df <- as_tibble(read.csv(')") + filename + ".csv'" + R"())

p <- df |> ggplot(aes(x, y, z = z)) + geom_contour_filled(breaks = )" + rexp_breaks + R"() + theme(legend.position = "none")

ggsave(')" + filename + ".png" + R"(', p, device = 'png')

)";



    }


}


bool plot(Matrix<double> x, Matrix<double> y, std::string filename = "test", int width = 5, int height = 5, std::string units = "cm") {

    auto df = ejovo::df({x, y}, {"x", "y"});

    std::string csv_file = filename + ".csv";
    std::string r_file   = filename + "_temp.r";


    df.to_csv(csv_file);

    // now generate the r code needed to create the image file
    std::ofstream my_file;

    my_file.open(r_file);
    my_file << ejovo::create_r_plot(filename);
    my_file.close();

    // now delete the temp r code, call Rscript
    system((std::string("Rscript ") + filename + "_temp.r").c_str());
    remove(r_file.c_str());
    remove(csv_file.c_str());

    return true;

}

bool contour(Matrix<double> x, Matrix<double> y, Matrix<double> z, std::string filename = "test", std::string rexp_breaks = "", int width = 5, int height = 5, std::string units = "cm") {

    if (x.isnt_same_shape(y) || x.isnt_same_shape(z)) return false;

    // Coerce these matrices into vectors that can be used in the data frame.
    std::string csv_file = filename + ".csv";
    std::string r_file   = filename + "_temp.r";

    x.reshape_col();
    y.reshape_col();
    z.reshape_col();

    auto df = ejovo::df({x, y, z}, {"x", "y", "z"});

    df.to_csv(csv_file);

    std::ofstream my_file;

    my_file.open(r_file);
    my_file << ejovo::create_contour_plot_breaks(filename, rexp_breaks);
    my_file.close();

    system((std::string("Rscript ") + filename + "_temp.r").c_str());
    remove(r_file.c_str());
    remove(csv_file.c_str());

}

bool contour(Matrix<double> x, Matrix<double> y, std::function<double (double, double)> f, std::string filename = "test", std::string rexp_breaks = "", int width = 5, int height = 5, std::string units = "cm") {

    if (x.isnt_same_shape(y)) return false;

    auto z = Matrix<double>::zeros(x); // make zeros same size as x

    z.loop_ij([&] (int i, int j) {
        z(i, j) = f(x(i, j), y(i, j));
    });

    // Coerce these matrices into vectors that can be used in the data frame.
    std::string csv_file = filename + ".csv";
    std::string r_file   = filename + "_temp.r";

    x.reshape_col();
    y.reshape_col();
    z.reshape_col();

    auto df = ejovo::df({x, y, z}, {"x", "y", "z"});

    df.to_csv(csv_file);

    std::ofstream my_file;

    my_file.open(r_file);
    my_file << ejovo::create_contour_plot_breaks(filename, rexp_breaks, width, height);
    my_file.close();

    system((std::string("Rscript ") + filename + "_temp.r").c_str());
    // remove(r_file.c_str());
    remove(csv_file.c_str());

}

};