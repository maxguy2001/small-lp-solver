#include "main.hpp"
#include "solvers/primal_tableau.hpp"
#include "utils/formatter.hpp"

#include <iostream>

void formatProblem(const std::string path_to_problem, const std::string solver){
  utils::Formatter format;
  format.formatFullProblem(path_to_problem, solver);
  std::vector<std::vector<int32_t>> mat = format.formattedMatrix_;

//test output on specific problem
  for(size_t i = 0; i < 4; ++i){
    for(size_t j = 0; j < 6; ++j){
      std::cout << mat[i][j] << std::endl;
    }
  }

}

int main(){
  const std::string problem_path = "../problems/problem1.txt";
  const std::string solver = "primal_tableau";
  formatProblem(problem_path, solver);
  return 0;
}

