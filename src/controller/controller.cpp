#include "controller.h"

namespace s21 {

std::pair<double, bool> Controller::input(const std::string &str,
                                          const double &x) {
  return model->smart_calc(str, x);
}

std::pair<const std::vector<double>, const bool> Controller::credit(
    const std::string &sum_str, const std::string &percent_str,
    const std::string &months_str, bool type) {
  return model->calc_credit(sum_str, percent_str, months_str, type);
}

}  // namespace s21
