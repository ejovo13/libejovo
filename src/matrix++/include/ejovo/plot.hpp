#pragma once

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
    std::size_t nrows;


    // Have a vector of matrices
    // Dataframe(std::initializer_list<Matrix<T>> list, std::initializer_list<std::string> names);
    Dataframe(std::vector<Matrix<T>> data, std::vector<std::string> names);

    bool to_csv(const std::string filename);


private:





};

// template <class T>
// Dataframe<T>::Dataframe(std::initializer_list<Matrix<T>> data, std::initializer_list<std::string> names) : cols{}, cols_names{}, nrows{0} {

//     int len_mat = list.begin()->size();
//     int n_added = 0;

//     for (auto mat : list) {
//         if (mat.size() != len_mat) continue;
//         cols.push_back(mat);
//         n_added ++;
//     }

//     nrows = n_added;

// }

template <class T>
Dataframe<T>::Dataframe(std::vector<Matrix<T>> data, std::vector<std::string> names) : cols{data}, col_names{names}, nrows{data.begin()->size()} {}

Dataframe<double> df(std::initializer_list<Matrix<double>> data, std::initializer_list<std::string> names) {

    // check to make sure that all of the vectors have the same size
    std::vector<Matrix<double>> cols;
    std::vector<std::string> col_names;

    int size = data.begin()->size();

    for (auto mat : data) {
        if (mat.size() != size) throw "You a dumb bitch";
        cols.push_back(mat);
    }

    for (auto n : names) {
        col_names.push_back(n);
    }

    Dataframe<double> out (cols, col_names);
    return out;
}


template <class T>
bool Dataframe<T>::to_csv(const std::string filename) {

    std::ofstream my_file;

    my_file.open(filename);
    const int ncols = cols.size();

    for (int i = 0; i < ncols - 1; i++) {
        my_file << col_names.at(i) << ",";
    }

    my_file << col_names.at(ncols - 1) << "\n";

    // iterate through length of the elements of mat
    for (int i = 1; i <= nrows; i++) {

        // Now add a row
        for (int j = 0; j < ncols - 1; j++) {

            my_file << cols.at(j).at(i) << ",";
        }

        my_file << cols.at(ncols - 1).at(i) << "\n";
    }

    my_file.close();


    return true;
}


std::string create_r_plot(std::string filename) {

    return std::string(R"(

library(ggplot2)
library(tibble)
df <- as_tibble(read.csv(')") + filename + ".csv'" + R"())

p <- df |> ggplot(aes(x, y)) + geom_line()

ggsave(')" + filename + ".png" + R"(', p, device = 'png')

)";
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

};