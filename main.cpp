#include "main.hpp"
#include "solvers/primal_tableau.hpp"
#include "utils/formatter.hpp"

#include <iostream>

void formatProblem(const std::string path_to_problem, const std::string solver){
  utils::Formatter format;
  format.formatFullProblem(path_to_problem, solver);
  std::vector<std::vector<int32_t>> mat = format.formattedMatrix_;
  std::vector<int32_t> vec = format.formattedVector_;

  for(size_t i = 0; i < mat.size(); ++i){
    for(size_t j = 0; j < mat.at(1).size(); ++j){
    //std::cout << mat[i][j] << std::endl;
  }
  }

  for(size_t i = 0; i < vec.size(); ++i){
    //std::cout << vec.at(i) << std::endl;
  }
}

void checkSolver(const std::string path_to_problem){
  solvers::Primal primal;
  primal.solve(path_to_problem);

}

int main(){
  const std::string problem_path = "../problems/problem2.txt";
  const std::string solver = "primal_tableau";
  formatProblem(problem_path, solver);
  checkSolver(problem_path);

  return 0;
}

