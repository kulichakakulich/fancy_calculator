#include "model.h"

namespace s21 {

double Model::create_number(const std::string &number_string) {
  double result = 0;
  bool point = false;
  int stepen = -1;
  for (auto it = number_string.begin();
       it != number_string.end() && error == true; ++it) {
    if (!((*it >= '0' && *it <= '9') || (*it == '.'))) {
      error = false;
    }
    if (*it == '.') {
      if (point == false) {
        point = true;
        if ((it + 1 == number_string.end()) || (it == number_string.begin())) {
          error = false;
          break;
        }
      } else {
        error = false;
        break;
      }
    } else {
      if (point == false) {
        result *= 10;
        result += (*it - '0');
      } else {
        result += (*it - '0') * pow(10, stepen--);
      }
    }
  }
  return result;
}

double Model::from_exp_to_double(const std::string &number_string) {
  bool sign;
  std::string mantisa_string;
  std::string stepen_string;
  bool borders = true;
  for (auto it = number_string.begin(); it != number_string.end(); ++it) {
    if (*it == 'e') {
      borders = false;
    } else if (*it == '+') {
      sign = true;
    } else if (*it == '-') {
      sign = false;
    } else if (borders == true) {
      mantisa_string.push_back(*it);
    } else {
      stepen_string.push_back(*it);
    }
  }
  return sign ? create_number(mantisa_string) *
                    pow(10, create_number(stepen_string))
              : create_number(mantisa_string) *
                    pow(10, (-1) * create_number(stepen_string));
}

void Model::number_processing(int &i, const std::string &str) {
  std::string number_string;
  bool stop = true;
  int e_col = 0;
  while (((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == 'e') &&
         i < (int)str.size() && error == true) {
    if (str[i] == '.' && stop == true) {
      stop = false;
    } else if (str[i] == '.' && stop == false) {
      error = false;
    } else if (str[i] == 'e' && e_col < 2) {
      e_col++;
      if (i + 2 < (int)str.size()) {
        if ((str[i + 1] == '+' || str[i + 1] == '-') ||
            (str[i + 2] >= 0 && str[i + 2] <= 9)) {
          number_string.push_back(str[i]);
          i++;
        } else {
          error = false;
        }
      }
    } else if (str[i] == 'e') {
      error = false;
    }
    number_string.push_back(str[i]);
    i++;
  }
  i--;
  if (e_col == 0) {
    array_of_tokens.push_back(
        lexeme_struct(create_number(number_string), NUMBER));
  } else {
    array_of_tokens.push_back(
        lexeme_struct(from_exp_to_double(number_string), NUMBER));
  }
}

void Model::parser(const std::string &str) {
  for (int i = 0; i < (int)str.length() && error == true; ++i) {
    if (str[i] >= '0' && str[i] <= '9') {
      number_processing(i, str);
    } else if (str[i] == '+') {
      array_of_tokens.push_back(lexeme_struct(0, UNARY_PLUS));
    } else if (str[i] == '-') {
      array_of_tokens.push_back(lexeme_struct(0, UNARY_MINUS));
    } else if (str[i] == '/') {
      array_of_tokens.push_back(lexeme_struct(0, DIV));
    } else if (str[i] == '*') {
      array_of_tokens.push_back(lexeme_struct(0, MULT));
    } else if (str[i] == '(') {
      array_of_tokens.push_back(lexeme_struct(0, OPEN_BRACKET));
    } else if (str[i] == ')') {
      array_of_tokens.push_back(lexeme_struct(0, CLOSE_BRACKET));
    } else if (str[i] == '^') {
      array_of_tokens.push_back(lexeme_struct(0, DEGREE));
    } else if (str[i] == 'x') {
      array_of_tokens.push_back(lexeme_struct(0, IKS));
    } else if (str[i] == '=' || str[i] == ' ') {
      array_of_tokens.push_back(lexeme_struct(0, NT));
    } else if (str[i] == 'l' && str[i + 1] == 'n') {
      array_of_tokens.push_back(lexeme_struct(0, LN));
      i += 1;
    } else if (str[i] == 'm' && str[i + 1] == 'o') {
      array_of_tokens.push_back(lexeme_struct(0, MOD));
      i += 2;
    } else if (str[i] == 'c' && str[i + 1] == 'o') {
      array_of_tokens.push_back(lexeme_struct(0, COS));
      i += 2;
    } else if (str[i] == 's' && str[i + 1] == 'i') {
      array_of_tokens.push_back(lexeme_struct(0, SIN));
      i += 2;
    } else if (str[i] == 't' && str[i + 1] == 'a') {
      array_of_tokens.push_back(lexeme_struct(0, TAN));
      i += 2;
    } else if (str[i] == 'l' && str[i + 1] == 'o') {
      array_of_tokens.push_back(lexeme_struct(0, LOG));
      i += 2;
    } else if (str[i] == 's' && str[i + 1] == 'q') {
      array_of_tokens.push_back(lexeme_struct(0, SQRT));
      i += 3;
    } else if (str[i] == 'a' && str[i + 1] == 'c') {
      array_of_tokens.push_back(lexeme_struct(0, ACOS));
      i += 3;
    } else if (str[i] == 'a' && str[i + 1] == 's') {
      array_of_tokens.push_back(lexeme_struct(0, ASIN));
      i += 3;
    } else if (str[i] == 'a' && str[i + 1] == 't') {
      array_of_tokens.push_back(lexeme_struct(0, ATAN));
      i += 3;
    } else {
      error = false;
      break;
    }
  }
}

void Model::input_validation() {
  std::stack<bool> brackes;
  for (int i = 0; i < (int)array_of_tokens.size() && error == true; i++) {
    if (array_of_tokens[i].type_ == OPEN_BRACKET) {
      brackes.push(true);
      if (i + 1 < (int)array_of_tokens.size()) {
        if (array_of_tokens[i + 1].type_ == CLOSE_BRACKET) {
          error = false;
        }
      }
    } else if (array_of_tokens[i].type_ == CLOSE_BRACKET) {
      if (brackes.empty()) {
        error = false;
      } else {
        brackes.pop();
      }
    } else if (array_of_tokens[i].type_ >= COS &&
               array_of_tokens[i].type_ <= LOG) {
      if (i + 1 < (int)array_of_tokens.size()) {
        if (array_of_tokens[i + 1].type_ != OPEN_BRACKET) {
          error = false;
        }
      }
    } else if (array_of_tokens[i].type_ == UNARY_MINUS && i > 0) {
      if (array_of_tokens[i - 1].type_ != OPEN_BRACKET) {
        array_of_tokens[i].type_ = BINARY_MINUS;
      }
    } else if (array_of_tokens[i].type_ == UNARY_PLUS && i > 0) {
      if (array_of_tokens[i - 1].type_ != OPEN_BRACKET) {
        array_of_tokens[i].type_ = BINARY_PLUS;
      }
    }
  }
  if (!brackes.empty()) {
    error = false;
  }
}

void Model::dublicat_validation() {
  for (int i = 0; i < (int)array_of_tokens.size() && error == true; i++) {
    if (array_of_tokens[i].type_ >= UNARY_PLUS &&
        array_of_tokens[i].type_ <= BINARY_MINUS &&
        i + 1 < (int)array_of_tokens.size()) {
      if (array_of_tokens[i + 1].type_ >= CLOSE_BRACKET &&
          array_of_tokens[i + 1].type_ <= BINARY_MINUS) {
        error = false;
      }
    }
  }
}

void Model::create_operators_stack(const int &i) {
  while (!operation_stack.empty()) {
    int first = operation_priority(operation_stack.top().type_);
    int second = operation_priority(array_of_tokens[i].type_);
    if (first >= second && operation_stack.top().type_ >= UNARY_PLUS &&
        operation_stack.top().type_ <= BINARY_MINUS) {
      if (first == second &&
          !operator_associativity(array_of_tokens[i].type_)) {
        break;
      } else {
        output_array.push_back(operation_stack.top());
        operation_stack.pop();
      }
    } else {
      break;
    }
  }
  operation_stack.push(array_of_tokens[i]);
}

void Model::from_stack_to_output_array() {
  if (!operation_stack.empty()) {
    while (operation_stack.top().type_ != OPEN_BRACKET &&
           operation_stack.top().type_ >= UNARY_PLUS &&
           operation_stack.top().type_ <= BINARY_MINUS) {
      output_array.push_back(operation_stack.top());
      operation_stack.pop();
    }
    if (operation_stack.top().type_ == OPEN_BRACKET) {
      operation_stack.pop();
    } else {
      error = false;
    }
  }
  if (!operation_stack.empty()) {
    if (operation_stack.top().type_ >= COS &&
        operation_stack.top().type_ <= LOG) {
      output_array.push_back(operation_stack.top());
      operation_stack.pop();
    }
  }
}

void Model::deicstra_algorithm() {
  for (int i = 0; i < (int)array_of_tokens.size() && error == true; i++) {
    if (array_of_tokens[i].type_ == NUMBER) {
      output_array.push_back(array_of_tokens[i]);
    } else if (array_of_tokens[i].type_ == IKS) {
      array_of_tokens[i].data_ = x_;
      array_of_tokens[i].type_ = NUMBER;
      output_array.push_back(array_of_tokens[i]);
    } else if ((array_of_tokens[i].type_ >= COS &&
                array_of_tokens[i].type_ <= LOG) ||
               (array_of_tokens[i].type_ == OPEN_BRACKET)) {
      operation_stack.push(array_of_tokens[i]);
    } else if (array_of_tokens[i].type_ >= UNARY_PLUS &&
               array_of_tokens[i].type_ <= BINARY_MINUS) {
      create_operators_stack(i);
    } else if (array_of_tokens[i].type_ == CLOSE_BRACKET) {
      from_stack_to_output_array();
    }
  }
  while (!operation_stack.empty()) {
    if (operation_stack.top().type_ == OPEN_BRACKET ||
        operation_stack.top().type_ == CLOSE_BRACKET) {
      error = false;
    }
    output_array.push_back(operation_stack.top());
    operation_stack.pop();
  }
}

int Model::operation_priority(const int &type) {
  int res;
  if (type == 9 || type == 10) {
    res = 0;
  } else if (type == 5 || type == 6) {
    res = 1;
  } else if (type == 3 || type == 4) {
    res = 4;
  } else {
    res = 3;
  }
  return res;
}

bool Model::operator_associativity(const int &type) {
  bool res;
  if (type == 9 || type == 10 || type == 5 || type == 6) {
    res = true;
  } else {
    res = false;
  }
  return res;
}

void Model::auxiliary_calculations(const bool &type, const int &operators) {
  if (type == false) {
    if (!operation_stack.empty()) {
      if (operators == UNARY_MINUS) {
        operation_stack.top().data_ = -1 * (operation_stack.top().data_);
      } else if (operators == COS) {
        operation_stack.top().data_ = cos(operation_stack.top().data_);
      } else if (operators == SIN) {
        operation_stack.top().data_ = sin(operation_stack.top().data_);
      } else if (operators == TAN) {
        operation_stack.top().data_ = tan(operation_stack.top().data_);
      } else if (operators == ACOS) {
        operation_stack.top().data_ = acos(operation_stack.top().data_);
      } else if (operators == ASIN) {
        operation_stack.top().data_ = asin(operation_stack.top().data_);
      } else if (operators == ATAN) {
        operation_stack.top().data_ = atan(operation_stack.top().data_);
      } else if (operators == SQRT) {
        operation_stack.top().data_ = sqrt(operation_stack.top().data_);
      } else if (operators == LN) {
        operation_stack.top().data_ = log(operation_stack.top().data_);
      } else if (operators == LOG) {
        operation_stack.top().data_ = log10(operation_stack.top().data_);
      }
    }
  } else {
    if (operation_stack.size() >= 2) {
      double second = operation_stack.top().data_;
      operation_stack.pop();
      if (operators == MULT) {
        operation_stack.top().data_ *= (second);
      } else if (operators == DIV) {
        operation_stack.top().data_ /= (second);
      } else if (operators == DEGREE) {
        operation_stack.top().data_ = pow(operation_stack.top().data_, second);
      } else if (operators == MOD) {
        operation_stack.top().data_ = fmod(operation_stack.top().data_, second);
      } else if (operators == BINARY_PLUS) {
        operation_stack.top().data_ += second;
      } else if (operators == BINARY_MINUS) {
        operation_stack.top().data_ -= second;
      }
    }
  }
}

double Model::calculation() {
  for (int i = 0; i < (int)output_array.size() && error == true; i++) {
    if (output_array[i].type_ == NUMBER) {
      operation_stack.push(output_array[i]);
    } else if (output_array[i].type_ == UNARY_MINUS ||
               (output_array[i].type_ >= COS && output_array[i].type_ <= LOG)) {
      auxiliary_calculations(false, output_array[i].type_);
    } else {
      auxiliary_calculations(true, output_array[i].type_);
    }
  }
  return !operation_stack.empty() ? operation_stack.top().data_ : 0;
}

const std::pair<double, bool> Model::smart_calc(const std::string &str,
                                                const double &x) {
  x_ = x;
  error = true;
  parser(str);
  input_validation();
  dublicat_validation();
  deicstra_algorithm();
  const std::pair<double, bool> result(calculation(), error);
  array_of_tokens.clear();
  output_array.clear();
  error = true;
  for (int i = 0; i < (int)operation_stack.size(); i++) {
    operation_stack.pop();
  }
  return result;
}

std::vector<double> Model::calc_annuity(double sum, double percent,
                                        int months) {
  double res = 0;
  if (percent > 0 && sum > 0 && months > 0) {
    double months_percent = percent / 12;
    double annuity_ratio =
        (months_percent * pow((1 + months_percent), months)) /
        (pow((1 + months_percent), months) - 1);
    res = sum * annuity_ratio;
  } else {
    error = false;
  }
  return {res, (months * res) - sum, months * res};
}

double Model::calc_total_payout(double sum, double percent, int months) {
  double res = calc_mounth_payout(sum, percent, months);
  return months > 0 ? res + calc_total_payout(sum - (sum / months), percent,
                                              months - 1)
                    : 0;
}

double Model::calc_mounth_payout(double sum, double percent, int months) {
  double part_of_the_principal = sum / months;
  double interest_amount = sum * percent * (30.0 / 365.0);
  return part_of_the_principal + interest_amount;
}

std::vector<double> Model::calc_differentiated(double sum, double percent,
                                               int months) {
  double res = 0;
  double total_payout = 0;
  if (percent > 0 && sum > 0 && months > 0) {
    res = calc_mounth_payout(sum, percent, months);
    total_payout = calc_total_payout(sum, percent, months);
  } else {
    error = false;
  }
  return {res, total_payout - sum, total_payout};
}

std::pair<const std::vector<double>, const bool>
Model::calc_credit(const std::string &sum_str, const std::string &percent_str,
                   const std::string &months_str, bool type) {
  double sum = create_number(sum_str);
  double percent = create_number(percent_str) / 100.0;
  int months = (int)create_number(months_str);
  std::pair<std::vector<double>, bool> result;
  if (type == true) {
    result.first = calc_differentiated(sum, percent, months);
  } else {
    result.first = calc_annuity(sum, percent, months);
  }
  result.second = true;
  return result;
}

} // namespace s21
