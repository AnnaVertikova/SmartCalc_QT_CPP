#include <QApplication>
#include <QDebug>

#include "smartcalc.h"

QT_USE_NAMESPACE

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  setlocale(LC_NUMERIC, "C");

  s21::Model model;
  s21::Controller controller(&model);
  SmartCalc view(&controller);
  view.show();
  return a.exec();
}
