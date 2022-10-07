#include "form.h"

#include "ui_form.h"

Form::Form(QWidget *parent) : QWidget(parent), ui(new Ui::Form) {
  ui->setupUi(this);
  PushButtonOKClicked();
  connect(ui->pushButton_OK, SIGNAL(clicked()), this,
          SLOT(PushButtonOKClicked()));
}

Form::~Form() { delete ui; }

void Form::PushButtonOKClicked() {
  if (ui->radioButton_2->isChecked()) {
    emit DefineXSignal(ui->def_x_display->text());
  } else if (ui->radioButton_1->isChecked()) {
    emit MakeChartSignal();
  }
}
