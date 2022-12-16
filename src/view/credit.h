#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>
#include <QMainWindow>
#include <QWidget>

#include "controller/controller.h"

namespace Ui {
class credit;
}

namespace s21 {

class credit : public QDialog {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr, QMainWindow *main = nullptr,
                  Controller *control = nullptr);
  ~credit();

 private slots:
  void on_pushButton_clicked();

  void on_pushButton_result_clicked();

 private:
  Ui::credit *ui;
  QMainWindow *main;
  Controller *controller;
};

}  // namespace s21

#endif  // CREDIT_H
