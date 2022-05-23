#include "primal_tableau.hpp"
#include "../utils/formatter.hpp"
#include <iostream>
#include <algorithm>

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

void Primal::doIteration(){
  
  //find most negative value in negative cost vector
  std::vector<float> cost = table_.at(0);
  int32_t min_index = std::min_element(cost.begin(), cost.end()) - cost.end();
}

bool Primal::checkOptimal(){
  //check if all values in negative cost function are positive
  std::vector<float> cost = table_.at(0);
  for (size_t i = 0; i < cost.size(); ++i){
    if(cost.at(i) < 0){
      return false;
    }
  }
  return true;
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