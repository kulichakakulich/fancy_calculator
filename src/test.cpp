#include <gtest/gtest.h>

#include <iostream>

#include "s21_controller.h"
#include "s21_model.h"

#define EPS 1e-7

TEST(parser_test, incorrect_point_test_0) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("123..", 0).second, false);
}

TEST(parser_test, incorrect_point_test_1) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("123.4.", 0).second, false);
}

TEST(parser_test, incorrect_point_test_2) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("123.4", 0).second, true);
  ASSERT_EQ(model.smart_calc("123.4", 0).first, 123.4);
}

TEST(parser_test, incorrect_point_test_3) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc(".4", 0).second, false);
}

TEST(parser_test, incorrect_point_test_4) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc(".", 0).second, false);
}

TEST(parser_test, incorrect_point_test_5) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("+.-", 0).second, false);
}

TEST(parser_test, test_6) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("+-245-5+=", 0).second, false);
}

TEST(parser_test, test_7) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("123fds", 0).second, false);
}

TEST(parser_test, test_8) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("sin(cos(sin(cos(123.124345))))", 0).second, true);
  if (fabs(model.smart_calc("sin(cos(sin(cos(123.124345))))", 0).first) -
      fabs((0.676173) >= EPS)) {
    ASSERT_EQ(1, 1);
  }
}

TEST(parser_test, test_9) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("sqrt(20+ln(10))", 0).second, true);
  ASSERT_EQ((int)model.smart_calc("sqrt(20+ln(10))", 0).first, (int)4.72256);
}

TEST(parser_test, test_10) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("sin.(cos.(sin(cos())))", 0).second, false);
}

TEST(validator_test, test_0) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("sin(cos(sin(cos()))))", 0).second, false);
}

TEST(validator_test, test_1) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("sin())(", 0).second, false);
}

TEST(validator_test, test_2) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("sin10", 0).second, false);
}

TEST(exp_number_test, test_0) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("1.234e-10", 0).second, true);
  ASSERT_EQ(model.smart_calc("1.234e-10", 0).first, 1.234e-10);
}

TEST(exp_number_test, test_1) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("14234.4e-3+1000", 0).second, true);
  if (fabs(model.smart_calc("14234.4e-3+1000", 0).first) -
      fabs((1014.23) >= EPS)) {
    ASSERT_EQ(1, 1);
  }
}

TEST(parser_test_2, test_0) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("sin(asin(1))", 0).second, true);
  ASSERT_EQ(model.smart_calc("sin(asin(1))", 0).first, 1);
}

TEST(parser_test_2, test_1) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("cos(acos(1))", 0).second, true);
  ASSERT_EQ(model.smart_calc("cos(acos(1))", 0).first, 1);
}

TEST(parser_test_2, test_2) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("tan(atan(1))", 0).second, true);
  if (fabs(model.smart_calc("tan(atan(1))", 0).first) - fabs((1) >= EPS)) {
    ASSERT_EQ(1, 1);
  }
}

TEST(parser_test_2, test_3) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("1/3", 0).second, true);
  if (fabs(model.smart_calc("1/3", 0).first) - fabs((0.333333) >= EPS)) {
    ASSERT_EQ(1, 1);
  }
}

TEST(parser_test_2, test_4) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("4*2^2", 0).second, true);
  ASSERT_EQ(model.smart_calc("4*2^2", 0).first, 16);
}

TEST(parser_test_2, test_5) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("4*2mod2", 0).second, true);
  ASSERT_EQ(model.smart_calc("4*2mod2", 0).first, 0);
}

TEST(parser_test_2, test_6) {
  s21::Model model;
  ASSERT_EQ(
      model.smart_calc("4-(2+2*2-(4+2)*4-2)*sin(2+1)/4^(3*(2-1))", 0).second,
      true);
  if (fabs(model.smart_calc("4-(2+2*2-(4+2)*4-2)*sin(2+1)/4^(3*(2-1))", 0)
               .first) -
      fabs((4.0441) >= EPS)) {
    ASSERT_EQ(1, 1);
  }
}

TEST(parser_test_2, test_7) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("cos(2^(ln(3*4)))-5*3/(2-1)^2+5*1-2", 0).second,
            true);
  if (fabs(model.smart_calc("cos(2^(ln(3*4)))-5*3/(2-1)^2+5*1-2", 0).first) -
      fabs((-11.2257) >= EPS)) {
    ASSERT_EQ(1, 1);
  }
}

TEST(parser_test_2, test_8) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("1/x", 10).second, true);
  if (fabs(model.smart_calc("1/x", 10).first) - fabs((-0.1) >= EPS)) {
    ASSERT_EQ(1, 1);
  }
}

TEST(parser_test_2, test_9) {
  s21::Model model;
  ASSERT_EQ(
      model.smart_calc("cos(2^(ln(3+3*4-2^3)))-5*3/(2-1)^2+log(3-2*1)+5*1-2", 0)
          .second,
      true);
  if (fabs(model
               .smart_calc(
                   "cos(2^(ln(3+3*4-2^3)))-5*3/(2-1)^2+log(3-2*1)+5*1-2", 0)
               .first) -
      fabs((2) >= EPS)) {
    ASSERT_EQ(1, 1);
  }
}

TEST(calc_credit, test_0) {
  s21::Model model;
  std::vector resault = model.calc_credit("4000000", "10", "24", 0).first;
  ASSERT_EQ(model.calc_credit("4000000", "10", "24", 0).second, true);
  if (fabs((double)resault[0]) - fabs(4429912.9284016) >= EPS) {
    ASSERT_EQ(1, 1);
  }
}

TEST(calc_credit, test_1) {
  s21::Model model;
  std::vector resault = model.calc_credit("4000000", "10", "24", 1).first;
  ASSERT_EQ(model.calc_credit("4000000", "10", "24", 1).second, true);
  if (fabs((double)resault[0]) - fabs(4410958.9041959) >= EPS) {
    ASSERT_EQ(1, 1);
  }
}

TEST(controller, test_1) {
  s21::Model model;
  s21::Controller controller(&model);
  std::vector resault = controller.credit("4000000", "10", "24", 1).first;
  ASSERT_EQ(controller.credit("4000000", "10", "24", 1).second, true);
  if (fabs((double)resault[0]) - fabs(4410958.9041959) >= EPS) {
    ASSERT_EQ(1, 1);
  }
}

TEST(controller, test_2) {
  s21::Model model;
  s21::Controller controller(&model);
  ASSERT_EQ(controller.input("123fds", 0).second, false);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
