#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  s21::Model model;
  s21::Controller controller(&model);
  QApplication a(argc, argv);
  s21::MainWindow w(nullptr, &controller);
  w.setWindowTitle("Smart Calculator");
  w.setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
  w.show();
  return a.exec();
}
