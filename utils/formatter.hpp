#include <string>
#include <array>
#include<vector>

namespace utils{

class Formatter{
  public:
  Formatter();

  int kNumRows_;
  int kNumCols_;

  void formatFullProblem(const std::string path_to_problem_file, const std::string solver);
  void clearAll();


  std::vector<std::vector<float>> formattedMatrix_;
  std::vector<float> formattedVector_;

  private:
  
  std::string path_to_problem_file_;

  void getNumRowsAndCols();

  void addSlack();
  void addObjectiveFunction();

  void makeFormattedMatrix();
  void makeFormattedVector();

};

}