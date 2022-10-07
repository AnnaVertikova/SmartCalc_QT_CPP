#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_
#include "../Model/model.h"

namespace s21 {
class Controller {
 public:
  Controller() {}
  explicit Controller(const s21::Model *m) : model_(*m) {}

 private:
  Model model_;

 public:
  double make_result(std::string expression) {
    model_.Model::TokExpression(expression);
    return model_.getResult();
  }

  std::map<double, double> make_map_for_chart(
      std::map<double, std::string> *x_expression) {
    model_.Model::TokChartExpressions(x_expression);
    return model_.getPoints();
  }
};
}  //  namespace s21
#endif  // SRC_CONTROLLER_CONTROLLER_H_
