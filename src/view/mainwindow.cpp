#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "custom_plot/qcustomplot.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent, Controller *controller)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller(controller) {
  ui->setupUi(this);
  this->resize(430, 400);
  ui->widget->setBackground(QColor(100, 100, 100));
  ui->widget->xAxis->setTickLabelColor(QColor(239, 239, 239));
  ui->widget->yAxis->setTickLabelColor(QColor(239, 239, 239));
  ui->widget->xAxis->setTickLabelFont(QFont("Comic Sans MS", 8, 50));
  ui->widget->yAxis->setTickLabelFont(QFont("Comic Sans MS", 8, 50));
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_delete, SIGNAL(clicked()), this,
          SLOT(digits_number()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_left, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_right, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_percent, SIGNAL(clicked()), this,
          SLOT(digits_number()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_number()));
}

MainWindow::~MainWindow() { delete ui; }

QString MainWindow::set_result() {
  QString input = ui->outputWindow->text();
  QByteArray res_bit = input.toLocal8Bit();
  std::string res_str = res_bit.data();
  std::pair<double, bool> result =
      controller->input(res_str, ui->inputX->text().toDouble());
  QString string_res;
  if (result.second == false) {
    string_res = "Incorrect input!";
  } else {
    string_res = QString::number(result.first);
  }

  return string_res;
}
void MainWindow::digits_number() {
  QPushButton *button = (QPushButton *)sender();

  QString new_result;
  if (button->text() == "C") {
    new_result = "";
  } else if (button->text() == "=") {
    new_result = set_result();
  } else if (ui->outputWindow->text().size() < 255) {
    new_result = ui->outputWindow->text() + button->text();
    if (button->text() == "cos" || button->text() == "sin" ||
        button->text() == "tan" || button->text() == "acos" ||
        button->text() == "asin" || button->text() == "atan" ||
        button->text() == "sqrt" || button->text() == "ln" ||
        button->text() == "log") {
      new_result = new_result + "(";
    }
  }
  ui->outputWindow->setText(new_result);
}

void MainWindow::on_pushButton_graph_clicked() {
  if (ui->pushButton_graph->text() == "Graph") {
    ui->pushButton_graph->setText("Grаph");
    this->resize(860, 400);
  } else {
    ui->pushButton_graph->setText("Graph");
    this->resize(430, 400);
  }
}

void MainWindow::create_graphs(std::string res_string, double x_start,
                               double x_end) {
  QVector<double> x_tmp;
  QVector<double> y_tmp;
  double h = (fabs(x_start) + fabs(x_end)) / 10000;
  bool false_ind = true;
  for (double x = x_start; x <= x_end; x += h) {
    std::pair<double, bool> result = controller->input(res_string, x);
    if (result.second != false) {
      x_tmp.push_back(x);
      y_tmp.push_back(result.first);
      false_ind = true;
    }
    if ((result.second == false && false_ind == true) || x + h > x_end) {
      x_array.push_back(x_tmp);
      y_array.push_back(y_tmp);
      x_tmp.clear();
      y_tmp.clear();
      false_ind = false;
    }
  }
}

void MainWindow::draw_graph(QString res_str) {
  double x_start = -10, y_start = -10, x_end = 10, y_end = 10;
  if (ui->inputXleft->text().toDouble() != ui->inputXright->text().toDouble() &&
      ui->inputYleft->text().toDouble() != ui->inputYright->text().toDouble()) {
    x_start = ui->inputXleft->text().toDouble();
    y_start = ui->inputYleft->text().toDouble();
    x_end = ui->inputXright->text().toDouble();
    y_end = ui->inputYright->text().toDouble();
  }
  ui->widget->clearGraphs();
  ui->widget->xAxis->setRange(x_start, x_end);
  ui->widget->yAxis->setRange(y_start, y_end);
  QByteArray res_bit = res_str.toLocal8Bit();
  std::string res_string = res_bit.data();
  create_graphs(res_string, x_start, x_end);
  for (int i = 0; i < (int)x_array.size(); ++i) {
    ui->widget->addGraph();
    ui->widget->graph(i)->setPen(QPen(QColor(243, 114, 32)));
    ui->widget->graph(i)->addData(x_array[i], y_array[i]);
  }
  ui->widget->replot();

  x_array.clear();
  y_array.clear();
}

void MainWindow::on_pushButton_draw_clicked() {
  draw_graph(ui->outputWindow->text());
}

void MainWindow::on_pushButton_credit_clicked() {
  hide();
  creditWindow = new credit(nullptr, this, controller);
  creditWindow->show();
}

}  // namespace s21
