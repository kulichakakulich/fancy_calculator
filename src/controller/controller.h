#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>

#include "model/model.h"

namespace s21 {

class Controller {
 public:
  Controller(Model *m) : model(m){};
  std::pair<double, bool> input(const std::string &str, const double &x);
  std::pair<const std::vector<double>, const bool> credit(
      const std::string &sum_str, const std::string &percent_str,
      const std::string &months_str, bool type);

 private:
  Model *model;
};

}  // namespace s21

#endif  // CONTROLLER_H
