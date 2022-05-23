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
  const std::vector<float> cost = table_.at(0);
  const float min_cost_value = *std::min_element(cost.begin(), cost.end());
  const int min_cost_index = std::min_element(cost.begin(), cost.end()) - cost.begin();



  //perform ratio test to find pivot variable
  std::vector<float> ratio_values;
  float table_element;
  for (size_t i = 0; i < vector_.size(); ++i){
    table_element = table_[i+1][min_cost_index];

    if(table_element !=0){
      ratio_values.push_back(vector_.at(i) / table_element);
    }else{
      ratio_values.push_back(__FLT_MAX_EXP__);
    }
  }

  float min_ratio_value = *std::min_element(ratio_values.begin(), ratio_values.end());
  int min_ratio_index = std::min_element(ratio_values.begin(), ratio_values.end()) - ratio_values.begin(); 

  float pivot_value = table_[min_ratio_index+1][min_cost_index];

  //update basis
  




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
  doIteration();

/*
  while(checkOptimal() == false){
    doIteration();
  }

*/
}


}