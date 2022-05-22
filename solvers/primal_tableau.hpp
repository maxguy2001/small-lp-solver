
#include <vector>
#include <string>
#include <stdint.h>


namespace solvers{

  class Primal{
  public:
  Primal();

/**
 * @brief sets full table including objective function and 
 * b vector
 * 
 */
  void setTableandVector();

/**
 * @brief completes one iteration of tableau simplex algorithm
 * 
 */
  void doIteration();

/**
 * @brief checks if solution is optimal
 * 
 */
  bool checkOptimal();

/**
 * @brief formats and solves problem
 * 
 */
  void solve(std::string path_to_problem_file);

  private:

  std::string path_to_problem_file_;

  std::vector<std::vector<int32_t>> table_;

  std::vector<int32_t> vector_;

};
}