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
  
  //find most negative value in negative cost vector (to determine pivot column)
  const std::vector<float> cost = table_.at(0);
  const int pivot_column_index = std::min_element(cost.begin(), cost.end()) - cost.begin();



  //perform ratio test to find pivot variable
  std::vector<float> ratio_values;
  float table_element;
  for (size_t i = 1; i < vector_.size(); ++i){
    table_element = table_[i][pivot_column_index];

    if(table_element !=0){
      ratio_values.push_back(vector_.at(i) / table_element);
    }else{
      ratio_values.push_back(__FLT_MAX_EXP__);
    }
  }

  int pivot_row_index = std::min_element(ratio_values.begin(), ratio_values.end()) - ratio_values.begin(); 
  //since we don't iterate over objective function when searching for minimum ratio
  pivot_row_index += 1;
  const float pivot_value = table_[pivot_row_index][pivot_column_index];

  //update basis
  basic_variables_[pivot_row_index-1] = pivot_column_index;

  //gaussian eleimination on remaining rows to zero column
  const std::vector<float> pivot_row = table_.at(pivot_row_index);
  std::vector<float> temp_pivot_row;
  const int row_length = table_.at(0).size();
  float pivot_multiplier;
  float temp_vector_element;
  
  for(size_t i = 0; i < table_.size(); ++i){
    if(i != pivot_row_index){

      pivot_multiplier = table_[i][pivot_column_index];
      temp_pivot_row = pivot_row;

      //actually multiplies rows and cancels
      for(size_t j = 0; j < row_length; ++j){
        temp_pivot_row.at(j) = temp_pivot_row.at(j)*pivot_multiplier;
        table_[i][j] = -1*pivot_value * table_[i][j];

        table_[i][j] = table_[i][j] + temp_pivot_row.at(j);
      }

      //multiplies rows and cancels for vector

      temp_vector_element = pivot_multiplier * vector_.at(pivot_row_index);
      vector_.at(i) = -1*pivot_value * vector_.at(i); 

      vector_.at(i) = vector_.at(i) + temp_vector_element;
      

      //clear vector
      temp_pivot_row.clear();
    }

    
  }

}

bool Primal::checkOptimal(){
  //check if all values in negative cost function are positive
  std::vector<float> cost = table_.at(0);
  for (size_t i = 0; i < cost.size(); ++i){
    if(cost.at(i) <= 0){
      return false;
    }
  }
  return true;
}


void Primal::solve(std::string path_to_problem_file){
  path_to_problem_file_ = path_to_problem_file;

  setTableandVector();
  initialiseBasis();

  //doIteration();
  

  int i = 0;
  std::vector<float> cost;

  while(checkOptimal() == false){
    doIteration();

    cost = table_.at(0);

    for (size_t i = 0; i < cost.size(); i++){
      std::cout << cost.at(i) << ",";
    }
    
    std::cout << std::endl;

    
    i += 1;
    if(i > 10){
      break;
    }
  }



  //getOptimalValue();
}


}//namsepace solvers