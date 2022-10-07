#include "credit.h"

#include "qmessagebox.h"
#include "ui_credit.h"
#include "ui_paymentschedule.h"

Credit::Credit(QWidget *parent) : QWidget(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  schedule_ = new PaymentSchedule();
  ui->radioButton_annuitet->setChecked(true);
  connect(ui->pushButton_calc_credit, SIGNAL(clicked()), this,
          SLOT(CalcCreditClicked()));
  connect(ui->pushButton_reset_credit, SIGNAL(clicked()), this,
          SLOT(ResetCreditClicked()));
  connect(ui->pushButton_payment_schedule, SIGNAL(clicked()), this,
          SLOT(PaymentScheduleClicked()));
}

Credit::~Credit() { delete ui; }

void Credit::CalcCreditClicked() {
  month_payment_display_string_.clear();
  total_payment_display_string_.clear();
  overpayment_display_string_.clear();

  if (CheckInput()) {
    if (ui->radioButton_annuitet->isChecked()) {
      AnnuitetCreditCalc();
    } else {
      DifferentiatedCreditCalc();
    }
  } else {
    QMessageBox msgBox;
    msgBox.setText("Некорректный ввод!\t");
    msgBox.exec();
  }
}

void Credit::AnnuitetCreditCalc() {
  MakeAnnuitetFormula();
  AnnuitetConvertAndSet();
  SetScheduleDisplays(schedule_string_);
  SetScheduleOverpaymentDisplays();
}

void Credit::MakeAnnuitetFormula() {
  QString month_rate = ui->loan_rate_display->text() + " / 12 / 100";
  ConvertAndCalcRate(&month_rate);
  static const QString annuitet_month_payment_formula =
      "( i * ( 1 + i ) ^ n / ( ( 1 + i ) ^ n - 1 ) ) * S";

  for (int i = 0; i < annuitet_month_payment_formula.size(); i++) {
    if (annuitet_month_payment_formula[i] == 'i') {
      month_payment_display_string_ =
          month_payment_display_string_ + month_rate;
      continue;
    } else if (annuitet_month_payment_formula[i] == 'S') {
      month_payment_display_string_ =
          month_payment_display_string_ + ui->loan_sum_display->text();
    } else if (annuitet_month_payment_formula[i] == 'n') {
      month_payment_display_string_ =
          month_payment_display_string_ + ui->loan_term_display->text();
    } else {
      month_payment_display_string_ =
          month_payment_display_string_ + annuitet_month_payment_formula[i];
    }
  }
}

void Credit::AnnuitetConvertAndSet() {
  ConvertAndCalcTempString(&month_payment_display_string_);
  ui->month_payment_display->setText(month_payment_display_string_);

  total_payment_display_string_ =
      month_payment_display_string_ + " * " + ui->loan_term_display->text();
  ConvertAndCalcTempString(&total_payment_display_string_);
  ui->total_payment_display->setText(total_payment_display_string_);

  overpayment_display_string_ =
      total_payment_display_string_ + " - " + ui->loan_sum_display->text();
  ConvertAndCalcTempString(&overpayment_display_string_);
  ui->overpayment_display->setText(overpayment_display_string_);

  int term = ui->loan_term_display->text().toInt();
  schedule_string_.clear();
  for (int i = 1; i <= term; i++) {
    schedule_string_ = schedule_string_ + QString::number(i) + "\t" +
                       month_payment_display_string_ + "\n";
  }
}

void Credit::DifferentiatedCreditCalc() {
  CalcBasePayments();
  CalcAllPaymentsAndSchedule();
  SetScheduleOverpaymentDisplays();
}

void Credit::CalcBasePayments() {
  base_payment_ =
      ui->loan_sum_display->text() + " / " + ui->loan_term_display->text();
  ConvertAndCalcTempString(&base_payment_);

  current_loan_remainning_ =
      ui->loan_sum_display->text() + " - " + base_payment_ + " * " + "0";
  ConvertAndCalcTempString(&current_loan_remainning_);

  current_rate_ = current_loan_remainning_ + " * " +
                  ui->loan_rate_display->text() + " / 100 / 12";
  ConvertAndCalcTempString(&current_rate_);

  first_payment_ = base_payment_ + " + " + current_rate_;
  ConvertAndCalcTempString(&first_payment_);
  total_payment_ = first_payment_;
}

void Credit::CalcAllPaymentsAndSchedule() {
  schedule_string_.clear();
  schedule_string_ = schedule_string_ + "1\t" + first_payment_ + "\n";
  CalcAllPayments();
  SetScheduleDisplays(schedule_string_);

  if (ui->loan_term_display->text().toInt() > 1) {
    ui->month_payment_display->setText(first_payment_ + " - " + last_payment_);
  } else {
    ui->month_payment_display->setText(first_payment_);
  }
  ui->total_payment_display->setText(total_payment_);
  overpayment_ = total_payment_ + " - " + ui->loan_sum_display->text();
  ConvertAndCalcTempString(&overpayment_);
  ui->overpayment_display->setText(overpayment_);
}

void Credit::CalcAllPayments() {
  int payments = ui->loan_term_display->text().toInt();
  for (int i = 1; i < payments; i++) {
    QString payment_done = QString::number(i);
    current_loan_remainning_ = ui->loan_sum_display->text() + " - " +
                               base_payment_ + " * " + payment_done;
    ConvertAndCalcTempString(&current_loan_remainning_);
    current_rate_ = current_loan_remainning_ + " * " +
                    ui->loan_rate_display->text() + " / 100 / 12";
    ConvertAndCalcTempString(&current_rate_);
    last_payment_ = base_payment_ + " + " + current_rate_;
    ConvertAndCalcTempString(&last_payment_);
    total_payment_ = total_payment_ + " + " + last_payment_;
    ConvertAndCalcTempString(&total_payment_);
    schedule_string_ =
        schedule_string_ + QString::number(i + 1) + "\t" + last_payment_ + "\n";
  }
}

void Credit::SetScheduleDisplays(const QString &schedule_string) {
  schedule_->ui->schedule_term_display->setText(ui->loan_term_display->text());
  schedule_->ui->schedule_sum_display->setText(ui->loan_sum_display->text());
  schedule_->ui->schedule_rate_display->setText(ui->loan_rate_display->text());
  schedule_->ui->payment_schedule_display->setText(schedule_string);
}

void Credit::SetScheduleOverpaymentDisplays() {
  schedule_->ui->schedule_overpayment_display->setText(
      ui->overpayment_display->text());
  schedule_->ui->schedule_total_payment_display->setText(
      ui->total_payment_display->text());
}

void Credit::ResetCreditClicked() {
  month_payment_display_string_.clear();
  total_payment_display_string_.clear();
  overpayment_display_string_.clear();
  ui->total_payment_display->setText("0");
  ui->month_payment_display->setText("0");
  ui->total_payment_display->setText("0");
  ui->loan_rate_display->clear();
  ui->loan_sum_display->clear();
  ui->loan_term_display->clear();
}

void Credit::ConvertAndCalcTempString(QString *temp_string) {
  std::string expression_string = temp_string->toStdString();
  credit_controller_ = new s21::Controller();
  double result = credit_controller_->s21::Controller::make_result(expression_string);
  *temp_string =
      QString::number(QString::number(result, 'f', 2).toDouble(), 'g', 10);
}

void Credit::ConvertAndCalcRate(QString *temp_string) {
  std::string expression_string = temp_string->toStdString();
  credit_controller_ = new s21::Controller;
  double result = credit_controller_->s21::Controller::make_result(expression_string);
  *temp_string =
      QString::number(QString::number(result, 'f', 10).toDouble(), 'g', 10);
}

void Credit::PaymentScheduleClicked() { schedule_->show(); }

bool Credit::CheckInput() {
  bool check_result = false;
  if (!ui->loan_sum_display->text().isEmpty() &&
      !ui->loan_term_display->text().isEmpty() &&
      !ui->loan_rate_display->text().isEmpty()) {
    if (ui->loan_sum_display->text().toDouble() > 0) {
      if (ui->loan_term_display->text().toDouble() > 0) {
        if (ui->loan_rate_display->text().toDouble() > 0) {
          check_result = true;
        }
      }
    }
  }

  return check_result;
}
