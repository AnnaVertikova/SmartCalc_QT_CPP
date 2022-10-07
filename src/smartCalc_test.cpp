#include <gtest/gtest.h>

#include "./Model/model.h"

TEST(SmartCalc_2, calc_1) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "( 7 + 5 ) + ( 6 + 7 ) + 5";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 30.0);
}

TEST(SmartCalc_2, calc_2) {
  double result = 0;
  s21::Model model;
  std::string expression = "( 7 + 5 ) + ( 6 + 7 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 25.0);
}

TEST(SmartCalc_2, calc_3) {
  double result = 0;
  s21::Model model;
  std::string expression = "( 7 + 5 ) + ( 6 + 7 ) * 5";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 77.0);
}

TEST(SmartCalc_2, calc_4) {
  double result = 0;
  s21::Model model;
  std::string expression = "( 7 + 5 ) + sin( 5 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 12.0 + sin(5));
}

TEST(SmartCalc_2, calc_5) {
  float result = 0;
  s21::Model model;
  std::string expression = "sin( 5 + 7 + 5 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, sin(17));
}

TEST(SmartCalc_2, calc_6) {
  float result = 0;
  s21::Model model;
  std::string expression = "sin( 5 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, sin(5));
}

TEST(SmartCalc_2, calc_7) {
  float result = 0;
  s21::Model model;
  std::string expression = "5 * 7 + 5";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 40);
}

TEST(SmartCalc_2, calc_8) {
  float result = 0;
  s21::Model model;
  std::string expression = "( 7 + 5 ) + cos( 5 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 12 + cos(5));
}

TEST(SmartCalc_2, calc_8_) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "7 + 5 + 6";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 18.0);
}

TEST(SmartCalc_2, calc_9) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "5 + cos( 5 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 5 + cos(5));
}

TEST(SmartCalc_2, calc_10) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "5 * 7 / 5";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 7);
}

TEST(SmartCalc_2, calc_11) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "5 - 7 / 5";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 3.5999999);
}

TEST(SmartCalc_2, calc_12) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "5 ^ tan( 5 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, pow(5, tan(5)));
}

TEST(SmartCalc_2, calc_13) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "5 % tan( 5 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, fmod(5, tan(5)));
}

TEST(SmartCalc_2, calc_14) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "5 / 0";
  result = model.TokExpression(expression);
  ASSERT_EQ((result == result), 1);
}

TEST(SmartCalc_2, calc_15) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "5 + acos( 5 )";
  result = model.TokExpression(expression);
  ASSERT_EQ((result != result), 1);
}

TEST(SmartCalc_2, calc_16) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "5 + acos( 1 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 5 + acos(1));
}

TEST(SmartCalc_2, calc_17) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "5 + asin( 1 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 5 + asin(1));
}

TEST(SmartCalc_2, calc_18) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "5 + atan( 1 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 5 + atan(1));
}

TEST(SmartCalc_2, calc_19) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "5 + ln( 1 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 5 + log(1));
}

TEST(SmartCalc_2, calc_20) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "5 + log( 1 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 5 + log10(1));
}

TEST(SmartCalc_2, calc_21) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "5 + sqrt( 25 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 5 + sqrt(25));
}

TEST(SmartCalc_2, calc_22) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "cos( 5 ) + 10";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, cos(5) + 10);
}

TEST(SmartCalc_2, calc_23) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "sin( sin( 5 ) )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, -0.818574);
}

TEST(SmartCalc_2, calc_24) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "sin( sin( 5 ) + sin( 5 ) )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, -0.9403794);
}

TEST(SmartCalc_2, calc_25) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "sin( sin( 5 ) + sin( 5 ) + cos( 2 ) )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, -0.72262841);
}

TEST(SmartCalc_2, calc_26) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression =
      "( 0.00083333333333 * ( 1 + 0.0008333333333 ) ^ 12 / ( ( 1 + "
      "0.000833333333 ) ^ 12 - 1 ) ) * 100000";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 8378.5411555);
}

TEST(SmartCalc_2, calc_27) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "1 / 12 / 100";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 0.00083333335);
}

TEST(SmartCalc_2, calc_28) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "( 1 + 1 / 12 / 100 ) ^ 12";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 1.010046);
}

TEST(SmartCalc_2, calc_29) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "1 / 12 / 100 * ( 1 + 1 / 12 / 100 ) ^ 12";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 0.00084170495);
}

TEST(SmartCalc_2, calc_30) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression =
      "( 1 / 12 / 100 * ( 1 + 1 / 12 / 100 ) ^ 12 / ( ( 1 + 1 / 12 / 100 ) ^ "
      "12 - 1 ) ) * 100000";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 8378.5411555);
}

TEST(SmartCalc_2, calc_31) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "( # 1 + 1 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 2);
}

TEST(SmartCalc_2, calc_32) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "~ sin( 5 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 0.95892427466);
}

TEST(SmartCalc_2, calc_33) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "~ sin( sin( 5 ) )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 0.81857414446);
}

TEST(SmartCalc_2, calc_34) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "~ sin( ~ sin( 5 ) )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, -0.81857414446);
}

TEST(SmartCalc_2, calc_35) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "~ sin( # sin( 5 ) )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 0.81857414446);
}

TEST(SmartCalc_2, calc_36) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "# sin( # sin( 5 ) )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, -0.81857414446);
}

TEST(SmartCalc_2, calc_37) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "5E3 + 500";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 5500);
}

TEST(SmartCalc_2, calc_38) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "5E-6 + 500";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 500.000005);
}

TEST(SmartCalc_2, calc_39) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "-3 + ( sin( 5 ) )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, -3.95892427466);
}

TEST(SmartCalc_2, calc_40) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "-3 + ( 5 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 2);
}

TEST(SmartCalc_2, calc_41) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "-3 + ( 5 + 3 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 5);
}

TEST(SmartCalc_2, calc_42) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "-3 + ( # 5 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 2);
}

TEST(SmartCalc_2, calc_43) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "3 + # 6 ";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 9);
}

TEST(SmartCalc_2, calc_44) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "3 + ~ 6 ";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, -3);
}

TEST(SmartCalc_2, calc_45) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "~ ( 6 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, -6);
}

TEST(SmartCalc_2, calc_46) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "~ ( 6 + 3 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, -9);
}

TEST(SmartCalc_2, calc_47) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "# ( 6 + 3 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 9);
}

TEST(SmartCalc_2, calc_48) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "# ( -6 + 3 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, -3);
}

TEST(SmartCalc_2, calc_49) {
  s21::Model model;
  std::map<double, std::string> x_expr = {
      {1.0, "1.0 + 3"}, {1.1, "1.1 + 3"}, {1.2, "1.2 + 3"}};
  std::map<double, double> result;
  result = model.TokChartExpressions(&x_expr);

  ASSERT_EQ(result.size(), x_expr.size());
}

TEST(SmartCalc_2, calc_51) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "( ( 6 + 3 ) )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 9);
}

TEST(SmartCalc_2, calc_50) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "( ( ( 6 + 3 ) ) )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 9);
}

TEST(SmartCalc_2, calc_52) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "( ( ( 6 + 3 ) ) + 3 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 12);
}

TEST(SmartCalc_2, calc_53) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "( ( ( 6 + 3 ) + 3 ) + 3 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 15);
}

TEST(SmartCalc_2, calc_54) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "( ( ( 6 + 3 ) * 3 ) + 3 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 30);
}

TEST(SmartCalc_2, calc_55) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "( ( ( 6 + 3 ) * 3 ) + 3 / 3)";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 28);
}

TEST(SmartCalc_2, calc_56) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "( 7 + ( ( 6 + 3 ) * 3 ) + 3 / 3)";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 35);
}

TEST(SmartCalc_2, calc_57) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "( 7 + sqrt( 36 ) ) * ( ( 6 + 3 ) * 3 ) + 3 / 3";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 352);
}

TEST(SmartCalc_2, calc_58) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "7 + sqrt( 36 ) * ( 6 + 3 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 61);
}

TEST(SmartCalc_2, calc_59) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "7 + 6 * ( 6 + 3 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 61);
}

TEST(SmartCalc_2, calc_60) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "7 + 6 * sin( 5 ) + ( 6 + 3 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, 10.246454352);
}

TEST(SmartCalc_2, calc_61) {
  double result = 0;
  std::string expression;
  s21::Model model;
  expression = "7 + 6 * sin( 5 ) * ( 6 + 3 )";
  result = model.TokExpression(expression);
  ASSERT_FLOAT_EQ(result, -44.7819108318);
}

TEST(SmartCalc_2, calc_62) {
  s21::Model model;
  std::map<double, std::string> x_expr = {
      {1.0, "~ ( 1.0 ^ 2 )"}, {3, "~ ( 3 ^ 2 )"}, {1.2, "~ ( 1.2 ^ 2 )"}};
  std::map<double, double> result;
  result = model.TokChartExpressions(&x_expr);

  ASSERT_EQ(result.size(), x_expr.size());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
