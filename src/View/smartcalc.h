#ifndef SRC_VIEW_SMARTCALC_H_
#define SRC_VIEW_SMARTCALC_H_

#include <QDebug>
#include <QDir>
#include <QList>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <iostream>

#include "../Controller/controller.h"
#include "chart.h"
#include "credit.h"
#include "form.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SmartCalc;
}
QT_END_NAMESPACE

class SmartCalc : public QMainWindow {
  Q_OBJECT

 public:
  explicit SmartCalc(QWidget *parent = nullptr);
  explicit SmartCalc(s21::Controller *c): SmartCalc() {
    controller_ = c;
    }

  ~SmartCalc();

 private:
  Ui::SmartCalc *ui_;
  Form *choose_x_action_;
  Chart *chart_;
  Credit *credit_;
  s21::Controller *controller_;

  QStringList expression_list_;
  QString ui_string_;
  QString current_action_;
  QString main_display_temp_string_;

  int left_bracket_ = 0;
  int right_bracket_ = 0;
  int eq_flag_ = 0;

 private slots:
  void SetButtonsandSlots();
  void Digits();
  void DotClicked();
  void SignClicked();
  void BackspaceClicked();
  void BackspaceDisplaysNotEmpty(QString *backsp_string);
  void BackspaceDisplaysEmpty(QString *backsp_string);
  void EqualsClicked();
  void SetIncorrect();
  void ClearClicked();
  void ActionClicked();
  bool DigitOk();
  void ResetEqFlag();
  void ActionIsPlus();
  void ActionIsPrefix();
  void ActionIsX();
  void ActionIsRigntBracket();
  void ActionIsSimple();
  void AppendString(const QString &new_item);
  void ConvertString();
  bool IsPrefix(const QString &check_action);
  bool EndsWithPrefix(const QString &check_string);
  bool EndsWithDigit(const QString &check_string);
  bool EndsWithAriphmetic(const QString &check_string);
  bool EndsWithRightBracket(const QString &check_string);
  bool EndsWithX(const QString &check_string);
  void PushButtonCreditClicked();

 public slots:
  void DefineXSlot(const QString &x_string);
  void MakeChartSlot();
};
#endif  // SRC_VIEW_SMARTCALC_H_
