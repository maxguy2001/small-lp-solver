#include "primal_tableau.hpp"
#include "../utils/formatter.hpp"

namespace solvers{

Primal::Primal(){}

void Primal::setTableandVector(){
  utils::Formatter format;
  format.formatFullProblem(path_to_problem_file_, "primal_tableau");

  table_ = format.formattedMatrix_;
  vector_ = format.formattedVector_;
}



void Primal::solve(std::string path_to_problem_file){
  path_to_problem_file_ = path_to_problem_file;
  setTableandVector();

  while(checkOptimal() == false){
    doIteration();
  }

}
}