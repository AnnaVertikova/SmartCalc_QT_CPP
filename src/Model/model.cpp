#include "model.h"

namespace s21 {
std::map<double, double> Model::TokChartExpressions(
    std::map<double, std::string> *x_expression) {
  std::map<double, std::string>::iterator it_x_expr = x_expression->begin();

  while (it_x_expr != x_expression->end()) {
    ClearClassDataMembers();
    std::string temp_expression = it_x_expr->second;
    double y = TokExpression(temp_expression);
    points_.insert(std::make_pair(it_x_expr->first, y));
    ++it_x_expr;
  }
  return points_;
}

double Model::TokExpression(std::string expression_string) {
  std::vector<std::string> expression_stack;
  std::istringstream stream(expression_string);
  std::string part;
  while (getline(stream, part, ' ')) {
    expression_stack.push_back(part);
  }
  result_ = ExpressionParser(expression_stack);
  return result_;
}

double Model::ExpressionParser(
    const std::vector<std::string> &expression_stack) {
  double expr_result = 0;
  left_bracket_ = 0;

  for (size_t j = 0; j < expression_stack.size(); j++) {
    std::map<std::string, int>::iterator it = operations_.begin();

    if (!IsDigit(expression_stack[j])) {
      while (it != operations_.end()) {
        if (it->first == expression_stack[j]) {
          MatchFound(expression_stack[j], it);
          break;
        } else {
          ++it;
        }
      }
    } else {
      values_.push(stof(expression_stack[j]));
    }
  }
  FinalCalculation();
  expr_result = values_.top();
  values_.pop();
  return expr_result;
}

void Model::MatchFound(const std::string &token,
                       std::map<std::string, int>::iterator it) {
  if (PrefixExprFlag(token)) {
    left_bracket_++;
  }
  if (operators_.empty()) {
    operators_.push(*it);
  } else {
    next_op_ = *it;
    previous_op_ = operators_.top();
    operators_.pop();

    if (token == "(") {
      operators_.push(previous_op_);
      operators_.push(next_op_);
    } else if (token == ")") {
      CaseRightBracket();
    } else {
      PriorityOrder();
    }
  }
}

void Model::CaseRightBracket() {
  if (previous_op_.second != 5 && previous_op_.second != 4) {
    if (previous_op_.first != "(") {
      while (previous_op_.first != "(" && previous_op_.second != 5 &&
             previous_op_.second != 4 && values_.size() != 1) {
        PreCalc();
      }
      left_bracket_--;
      if (previous_op_.second == 5 && next_op_.first == ")") {
        PreCalc();
        left_bracket_--;
      }
      if (previous_op_.first == "(" && next_op_.first == ")" &&
          !operators_.empty()) {
        PriorityOrder();
      }
    } else {
      PriorityOrder();
    }
  } else {
    PreCalc();
    left_bracket_--;
    if (previous_op_.second != 4 && previous_op_.first != "(") {
      operators_.push(previous_op_);
    } else {
      PriorityOrder();
    }
  }
}

void Model::ClearClassDataMembers() {
  values_ = std::stack<double>();
  operators_ = std::stack<std::pair<std::string, int>>();
  next_op_ = std::pair<std::string, int>();
  previous_op_ = std::pair<std::string, int>();
}

bool Model::IsDigit(const std::string &token) {
  return (std::isdigit(token[0]) || std::isdigit(token[1]));
}

int Model::CheckPriority() { return next_op_.second - previous_op_.second; }

void Model::PriorityOrder() {
  if (previous_op_.second == 5) {
    PriorityGreater();
  } else {
    if (CheckPriority() > 0) {
      PriorityGreater();
    } else {
      PriorityLessOrEqual();
    }
  }
}

void Model::PriorityLessOrEqual() {
  if (CheckPriority() == 0) {
    if (previous_op_.first != "(") {
      while ((CheckPriority() == 0) && values_.size() != 1) {
        PreCalc();
      }

    } else {
      if (operators_.size()) {
        previous_op_ = operators_.top();
        operators_.pop();
      }
      if (previous_op_.second == kUnaryPlus ||
          previous_op_.second == kUnaryMinus) {
        PreCalc();
      }
    }
  } else if (CheckPriority() < 0) {
    if (previous_op_.second == 4) {
      PreCalc();
    }
    while (CheckPriority() < 0 && values_.size() != 1) {
      PreCalc();
    }
  }
  operators_.push(previous_op_);
  if (next_op_.first != ")") {
    operators_.push(next_op_);
  }
}

void Model::PriorityGreater() {
  operators_.push(previous_op_);
  if (next_op_.first != ")") {
    operators_.push(next_op_);
  }
}

void Model::PreCalc() {
  if (previous_op_.second == 5 || previous_op_.second == 4) {
    FunctionCalculate(previous_op_.first);
    if (!operators_.empty()) {
      previous_op_ = operators_.top();
      operators_.pop();
    }
  } else {
    Calculate(previous_op_.first);
    if (operators_.size() != 0) {
      previous_op_ = operators_.top();
      operators_.pop();
    } else {
      previous_op_ = next_op_;
    }
  }
}

void Model::Calculate(const std::string &action) {
  double result = 0;
  double b = values_.top();
  values_.pop();
  double a = values_.top();
  values_.pop();

  if (action == "+") {
    result = a + b;
  } else if (action == "-") {
    result = a - b;
  } else if (action == "*") {
    result = a * b;
  } else if (action == "/") {
    result = a / b;
  } else if (action == "%") {
    result = fmod(a, b);
  } else if (action == "^") {
    result = pow(a, b);
  }

  values_.push(result);
}

void Model::FunctionCalculate(const std::string &function) {
  double result = 0;
  double a = values_.top();
  values_.pop();
  if (function == "cos(") {
    result = cos(a);
  } else if (function == "sin(") {
    result = sin(a);
  } else if (function == "tan(") {
    result = tan(a);
  } else if (function == "acos(") {
    result = acos(a);
  } else if (function == "asin(") {
    result = asin(a);
  } else if (function == "atan(") {
    result = atan(a);
  } else if (function == "sqrt(") {
    result = sqrt(a);
  } else if (function == "ln(") {
    result = log(a);
  } else if (function == "log(") {
    result = log10(a);
  } else if (function == "~") {
    result = a * -1;
  } else if (function == "#") {
    result = a;
  }
  values_.push(result);
}

void Model::FinalCalculation() {
  while (operators_.size() != 0 && (values_.size() != 1)) {
    previous_op_ = operators_.top();
    operators_.pop();
    if (previous_op_.second == kUnaryPlus ||
        previous_op_.second == kUnaryMinus) {
      FunctionCalculate(previous_op_.first);
    } else {
      Calculate(previous_op_.first);
    }
  }
}

int Model::PrefixExprFlag(const std::string &token) {
  int flag = 0;

  if (token == "(" || token == "sin(" || token == "cos(" || token == "tan(" ||
      token == "asin(" || token == "acos(" || token == "atan(" ||
      token == "log(" || token == "ln(" || token == "sqrt(") {
    flag = 1;
  }

  return flag;
}

}  // namespace s21
