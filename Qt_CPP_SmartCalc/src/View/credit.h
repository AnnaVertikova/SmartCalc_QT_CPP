#ifndef SRC_VIEW_CREDIT_H_
#define SRC_VIEW_CREDIT_H_
#include <QDialog>
#include <QWidget>

#include "Controller/controller.h"
#include "paymentschedule.h"

namespace Ui {
class Credit;
}

class Credit : public QWidget {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void CalcCreditClicked();
  void AnnuitetCreditCalc();
  void MakeAnnuitetFormula();
  void AnnuitetConvertAndSet();
  void DifferentiatedCreditCalc();
  void CalcBasePayments();
  void CalcAllPaymentsAndSchedule();
  void CalcAllPayments();
  void SetScheduleDisplays(const QString &temp_string);
  void SetScheduleOverpaymentDisplays();
  void ResetCreditClicked();
  void ConvertAndCalcTempString(QString *temp_string);
  void ConvertAndCalcRate(QString *temp_string);
  void PaymentScheduleClicked();
  bool CheckInput();

 private:
  Ui::Credit *ui;
  PaymentSchedule *schedule_;

  s21::Controller *credit_controller_;
  QString month_payment_display_string_;
  QString total_payment_display_string_;
  QString overpayment_display_string_;
  QString schedule_string_;

  QString base_payment_;
  QString current_loan_remainning_;
  QString current_rate_;
  QString first_payment_;
  QString last_payment_;
  QString total_payment_;
  QString overpayment_;
};

#endif  // SRC_VIEW_CREDIT_H_
