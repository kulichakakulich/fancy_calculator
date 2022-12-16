#include "credit.h"
#include "ui_credit.h"

namespace s21 {

credit::credit(QWidget *parent, QMainWindow *main, Controller *control)
    : QDialog(parent), ui(new Ui::credit), controller(control) {
  this->main = main;
  ui->setupUi(this);
  this->resize(430, 400);
  this->setWindowTitle("Credit Calulator");
}

credit::~credit() { delete ui; }

void credit::on_pushButton_clicked() {
  hide();
  main->show();
}

void credit::on_pushButton_result_clicked() {
  if (ui->input_sum->text().toDouble() > 0 &&
      ui->input_term->text().toDouble() > 0 &&
      ui->input_percent->text().toDouble() > 0) {
    QByteArray sum_bit = ui->input_sum->text().toLocal8Bit();
    std::string sum = sum_bit.data();
    QByteArray time_bit = ui->input_term->text().toLocal8Bit();
    std::string time = time_bit.data();
    QByteArray percent_bit = ui->input_percent->text().toLocal8Bit();
    std::string percent = percent_bit.data();
    bool type = false;
    if (ui->radioButton_Diff->isChecked()) {
      type = true;
    }
    std::pair<const std::vector<double>, const bool> result =
        controller->credit(sum, percent, time, type);
    if (result.second) {
      QString string_monthly_payment = QString::number(result.first[0], 'f', 2);
      QString string_term = QString::number(result.first[1], 'f', 2);
      QString string_total_payment = QString::number(result.first[2], 'f', 2);
      ui->output_monthly->setText(string_monthly_payment);
      ui->output_percent->setText(string_term);
      ui->output_total->setText(string_total_payment);
    } else {
      ui->output_monthly->setText("Incorrect input!");
      ui->output_percent->setText("Incorrect input!");
      ui->output_total->setText("Incorrect input!");
    }
  } else {
    ui->output_monthly->setText("Incorrect input!");
    ui->output_percent->setText("Incorrect input!");
    ui->output_total->setText("Incorrect input!");
  }
}

}  // namespace s21
