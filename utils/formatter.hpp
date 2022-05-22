#include <string>
#include <array>
#include<vector>

namespace utils{

class Formatter{
  public:
  Formatter();

  int kNumRows_ = 100;
  int kNumCols_ = 100;

  void formatFullProblem(const std::string path_to_problem_file, const std::string solver);


  std::vector<std::vector<int32_t>> formattedMatrix_;
  std::vector<int32_t> formattedVector_;

  private:
  
  std::string path_to_problem_file_;

  void getNumRowsAndCols();

  void addSlack();
  void addObjectiveFunction();

  void makeFormattedMatrix();
  void makeFormattedVector();

};

}