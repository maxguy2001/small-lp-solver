#include "formatter.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

//TODO:tidy up and optimize code!
namespace utils{

Formatter::Formatter(){}

void Formatter::getNumRowsAndCols(){
  std::string temp_str;
  std::string numrows_string;
  std::string numcols_string;
  std::fstream newfile;

  newfile.open(path_to_problem_file_, std::ios::in);

  for(size_t i = 0; i < 5; ++i){
    getline(newfile, temp_str);
    if(i == 0){
      numrows_string = temp_str;
    }
    if(i == 1){
      numcols_string = temp_str;
    }
  }
  newfile.close();

  const int8_t numrows = atoi(numrows_string.c_str());
  const int8_t numcols = atoi(numcols_string.c_str());

  kNumRows_ = numrows;
  kNumCols_ = numcols;  
}

void Formatter::makeFormattedMatrix(){

//read matrix from file and store in a string
  std::string matstring;
  std::string temp_str;
  std::fstream newfile;

  newfile.open(path_to_problem_file_, std::ios::in);

  for(size_t i = 0; i < 7; ++i){
    getline(newfile, temp_str);
    if(i == 2){
      matstring = temp_str;
    }
  }

  newfile.close();


//convert string into vector of strings
  std::stringstream ss(matstring);
  std::string s;
  std::vector<std::string> matstringvec;

  while(std::getline(ss, s, ',')){
    matstringvec.push_back(s);
  }

//convert vector of strings into array of ints and reshape to 2d
  int32_t mat1d[matstringvec.size()];

  for(size_t i = 0; i < matstringvec.size(); ++i){
    mat1d[i] = static_cast<int32_t>(atoi(matstringvec.at(i).c_str()));
  }

  int mat2d[kNumRows_][kNumCols_];

  for(size_t i = 0; i < kNumCols_; ++i){
    for(size_t j = 0; j < kNumRows_; ++j){
      int mat1d_index = (i*kNumCols_) + j;
      mat2d[i][j] = mat1d[mat1d_index];
    }
  }

//store values from 2d array as 2d vector class attribute
  std::vector<int32_t> temp_vec;

  for(size_t i = 0; i < kNumCols_; ++i){
    for(size_t j = 0; j < kNumRows_; ++j){
      temp_vec.push_back(mat2d[i][j]);
    }
    formattedMatrix_.push_back(temp_vec);
    temp_vec.clear();
  }
}

void Formatter::addSlack(){

  for(size_t i = 0; i < kNumRows_; ++i){
    for(size_t j = 0 ; j < kNumRows_; ++j){
      if(i == j){
        formattedMatrix_[i].push_back(1);
      }else{
        formattedMatrix_[i].push_back(0);
      }
    }
  }
}

void Formatter::addObjectiveFunction(){
  std::string objective_coeffs_string;
  std::string temp_str;
  std::fstream newfile;

  newfile.open(path_to_problem_file_, std::ios::in);

  for(size_t i = 0; i < 7; ++i){
    getline(newfile, temp_str);
    if(i == 4){
      objective_coeffs_string = temp_str;
    }
  }
  newfile.close();

  //convert string into vector of strings
  std::stringstream ss(objective_coeffs_string);
  std::string s;
  std::vector<std::string> obj_string_vec;

  while(std::getline(ss, s, ',')){
    obj_string_vec.push_back(s);
  }

  std::vector<int32_t> objective_vector;

  //switch to int32_t and add to vector
  for(size_t i = 0; i < obj_string_vec.size(); ++i){
    int32_t element = static_cast<int32_t>(atoi(obj_string_vec.at(i).c_str()));
    objective_vector.push_back(element);
  }

  //add objective to existing matrix
  int32_t target_row_length = formattedMatrix_.at(1).size();
  int32_t diff = target_row_length - objective_vector.size();
  for(size_t i = 0; i < diff; ++i){
    objective_vector.push_back(0);
  }

  formattedMatrix_.insert(formattedMatrix_.begin(), objective_vector);
}


void Formatter::makeFormattedVector(){

//read matrix from file and store in a string
  std::string vecstring;
  std::string temp_str;
  std::fstream newfile;

  newfile.open(path_to_problem_file_, std::ios::in);

  for(size_t i = 0; i < 5; ++i){
    getline(newfile, temp_str);
    if(i == 3){
      vecstring = temp_str;
    }
  }
  newfile.close();

//convert string into vector of strings
  std::stringstream ss(vecstring);
  std::string s;
  std::vector<std::string> stringvec;

  while(std::getline(ss, s, ',')){
    stringvec.push_back(s);
  }

//convert vector of strings into vector of int32_t and assign to class attribute
  for(size_t i = 0; i < stringvec.size(); ++i){
    int32_t element = static_cast<int32_t>(atoi(stringvec.at(i).c_str()));
    formattedVector_.push_back(element);
  }
}

void Formatter::clearAll(){
  formattedMatrix_.clear();
  formattedVector_.clear();
  path_to_problem_file_.clear();
  kNumCols_ = 0;
  kNumRows_ = 0;
}

void Formatter::formatFullProblem(const std::string path_to_problem_file, const std::string solver){
  path_to_problem_file_ = path_to_problem_file;
  if(solver == "primal_tableau"){
    getNumRowsAndCols();
    makeFormattedVector();
    makeFormattedMatrix();
    addSlack();
    addObjectiveFunction();
  }
}

}//namespace utils