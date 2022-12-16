#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "credit.h"
#include "controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr, Controller *controller = nullptr);

  ~MainWindow();

 private slots:
  void digits_number();
  void draw_graph(QString res_str);
  void create_graphs(std::string res_string, double x_start, double x_end);

  void on_pushButton_graph_clicked();

  void on_pushButton_draw_clicked();

  void on_pushButton_credit_clicked();

 private:
  Ui::MainWindow *ui;
  Controller *controller;
  credit *creditWindow;
  QString set_result();

  QVector<QVector<double>> x_array, y_array;
};

}  // namespace s21
#endif  // MAINWINDOW_H
