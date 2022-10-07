#include "paymentschedule.h"

#include "ui_paymentschedule.h"

PaymentSchedule::PaymentSchedule(QWidget *parent)
    : QWidget(parent), ui(new Ui::PaymentSchedule) {
  ui->setupUi(this);
}

PaymentSchedule::~PaymentSchedule() { delete ui; }
