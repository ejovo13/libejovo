#include "ejovotest.hpp"

int main() {

    using namespace ejovo;

    std::cout << "Hello MCMC\n";
    std::cout << "Wassup?\n";

    auto prob = ejovo::rcat(100, ejovo::vec({0.7, 0.2, 0.1}));

    // prob.print();
    prob.print();

    auto transition_matrix = Matrix<double>::from({0.7, 0.2, 0.1, 0.15, 0.5, 0.35, 0.05, 0.2, 0.75}, 3, 3, true);
    MarkovChain m(transition_matrix);

    transition_matrix.print();


    auto sim = m.simulate(100000);

    m.pow(100).print();

    auto stat_mat = m.pow(100);

    (stat_mat.get_row(1) * transition_matrix).print();

    auto df = ejovo::df({sim}, {"sim"});

    df.to_csv("markov_sim.csv");


    histogram_counts_discrete(sim, seq<int>(3)).print();
    histogram_freq_discrete(sim, seq<int>(3)).print();

    // std::cout << "mean: " << rnorm(100000).mean() << "\n";

    // std::vector<int> my_vec_FUNCTION();
    // std::vector<int> my_vec_OBJECT{};

    return 0;
}