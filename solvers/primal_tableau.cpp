#include "primal_tableau.hpp"
#include "../utils/formatter.hpp"
#include <iostream>

namespace solvers{

Primal::Primal(){}

void Primal::setTableandVector(){
  utils::Formatter format;
  format.formatFullProblem(path_to_problem_file_, "primal_tableau");

  table_ = format.formattedMatrix_;
  vector_ = format.formattedVector_;
}

void Primal::initialiseBasis(){
  utils::Formatter format;
  format.formatFullProblem(path_to_problem_file_, "primal_tableau");

  int number_nonbasic_columns = format.kNumCols_;
  int total_number_columns = table_.at(0).size();

  for(size_t i = number_nonbasic_columns; i < total_number_columns; ++i){
    basic_variables_.push_back(i);
  }
}



void Primal::solve(std::string path_to_problem_file){
  path_to_problem_file_ = path_to_problem_file;
  setTableandVector();

  initialiseBasis();

/*
  while(checkOptimal() == false){
    doIteration();
  }

*/
}


}