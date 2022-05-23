#include <cassert>
#include <iostream>
#include <vector>

#include "test.hpp"
#include "utils/formatter.hpp"


void testFormatter(){
  utils::Formatter format;


//test problem 1
  std::string problem_1 = "../problems/problem1.txt";
  format.formatFullProblem(problem_1, "primal_tableau");

  assert(format.kNumCols_ == 3);
  assert(format.kNumRows_ == 3);
  
  std::vector<std::vector<float>> formatted_matrix_1 = format.formattedMatrix_;
  std::vector<std::vector<float>> correct_matrix_1 
  = {{7,7,7,0,0,0},{1,2,3,1,0,0},{4,5,6,0,1,0},{7,8,9,0,0,1}};
  
  for(size_t i = 0; i < formatted_matrix_1.size(); ++i){
    for (size_t j = 0; j < formatted_matrix_1.at(0).size(); ++j){
      assert(formatted_matrix_1[i][j] == correct_matrix_1[i][j]);
    }
  }

  std::vector<float> formatted_vector_1 = format.formattedVector_;
  std::vector<float> correct_vector_1 = {10,10,11};

  for (size_t i = 0; i < formatted_vector_1.size(); ++i){
    assert(formatted_vector_1.at(i) == correct_vector_1.at(i));
  }
  
  format.clearAll();

  //test problem 2
  std::string problem_2 = "../problems/problem2.txt";
  format.formatFullProblem(problem_2, "primal_tableau");

  assert(format.kNumCols_ == 2);
  assert(format.kNumRows_ == 2);
  
  std::vector<std::vector<float>> formatted_matrix_2 = format.formattedMatrix_;
  std::vector<std::vector<float>> correct_matrix_2 = {{-1,-10,0,0},{1,20,1,0},{0,1,0,1}};
  
  for(size_t i = 0; i < formatted_matrix_2.size(); ++i){
    for (size_t j = 0; j < formatted_matrix_2.at(0).size(); ++j){
      assert(formatted_matrix_2[i][j] == correct_matrix_2[i][j]);
    }
  }

  std::vector<float> formatted_vector_2 = format.formattedVector_;
  std::vector<float> correct_vector_2 = {100,1};

  for (size_t i = 0; i < formatted_vector_2.size(); ++i){
    assert(formatted_vector_2.at(i) == correct_vector_2.at(i));
  }

  format.clearAll();

}

int main(){
  testFormatter();
  std::cout << "formatter passed all tests" << std::endl;

  return 0;
}