#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <vector>

namespace s21 {

class Model {
 public:
  Model() : result_(0) {}

  using Operator = std::pair<std::string, int>;
  using DoublesStack = std::stack<double>;
  using OperatorsStack = std::stack<Operator>;

 private:
  enum Priority {
    kLbracket = 0,
    kRbracket = 0,
    kAdd = 1,
    kSub = 1,
    kMult = 2,
    kDiv = 2,
    kMod = 2,
    kPow = 3,
    kUnaryMinus = 4,
    kUnaryPlus = 4,
    kCos = 5,
    kSin = 5,
    kTan = 5,
    kAcos = 5,
    kAsin = 5,
    kAtan = 5,
    kSqrt = 5,
    kLn = 5,
    kLog = 5,
    kX = 6
  };

  Operator next_op_;
  Operator previous_op_;
  DoublesStack values_;
  OperatorsStack operators_;
  int left_bracket_ = 0;
  double result_;
  std::map<double, double> points_;

  std::map<std::string, int> operations_ = {
      {"(", kLbracket},   {")", kRbracket}, {"+", kAdd},
      {"-", kSub},        {"*", kMult},     {"/", kDiv},
      {"%", kMod},        {"^", kPow},      {"cos(", kCos},
      {"sin(", kSin},     {"tan(", kTan},   {"acos(", kAcos},
      {"asin(", kAsin},   {"atan(", kAtan}, {"sqrt(", kSqrt},
      {"ln(", kLn},       {"log(", kLog},   {"x", kX},
      {"~", kUnaryMinus}, {"#", kUnaryPlus}};

 public:
  std::map<double, double> TokChartExpressions(
      std::map<double, std::string> *x_expression);
  double TokExpression(std::string expression_string);
  double getResult() { return result_; }
  std::map<double, double> getPoints() { return points_; }

 private:
  double ExpressionParser(const std::vector<std::string> &expression_stack);
  bool IsDigit(const std::string &token);
  int CheckPriority();
  void PriorityOrder();
  void PriorityLessOrEqual();
  void PriorityGreater();
  void PreCalc();
  void Calculate(const std::string &action);
  void FunctionCalculate(const std::string &function);
  void FinalCalculation();
  int PrefixExprFlag(const std::string &token);
  void MatchFound(const std::string &token,
                  std::map<std::string, int>::iterator it);
  void CaseRightBracket();
  void ClearClassDataMembers();
};

}  // namespace s21
#endif  // SRC_MODEL_MODEL_H_
