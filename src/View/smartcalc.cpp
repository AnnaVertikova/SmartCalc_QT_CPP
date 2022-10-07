#include "smartcalc.h"

#include "./ui_smartcalc.h"

SmartCalc::SmartCalc(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SmartCalc) {
  ui_->setupUi(this);
  SetButtonsandSlots();
}

SmartCalc::~SmartCalc() { delete ui_; }

void SmartCalc::Digits() {
  QPushButton *digit_button = (QPushButton *)sender();
  QString digit_string;
  ResetEqFlag();
  if (ui_->digit_input_display->text() != "Incorrect expression." &&
      ui_->digit_input_display->text() != "0") {
    if (ui_->digit_input_display->text().isEmpty()) {
      if (ui_->main_display->text().isEmpty() ||
          (!ui_->main_display->text().isEmpty() &&
           !ui_->main_display->text().endsWith(')') &&
           !ui_->main_display->text().endsWith('x'))) {
        if (!digit_button->text().contains('E')) {
          digit_string = ui_->digit_input_display->text();
          digit_string = digit_string + digit_button->text();
          ui_->digit_input_display->setText(digit_string);
        }
      }
    } else {
      digit_string = ui_->digit_input_display->text();
      if (!digit_button->text().contains('E')) {
        digit_string = digit_string + digit_button->text();
      } else if (!ui_->digit_input_display->text().contains('E')) {
        digit_string = digit_string + digit_button->text();
      }
      ui_->digit_input_display->setText(digit_string);
    }
  } else {
    if (ui_->digit_input_display->text() != "0") {
      ClearClicked();
    }
  }
}

void SmartCalc::ActionClicked() {
  QPushButton *button = (QPushButton *)sender();
  current_action_ = button->text();
  if (ui_->digit_input_display->text() != "Incorrect expression.") {
    if (DigitOk()) {
      if (ui_->main_display->text().contains('=')) {
        expression_list_.clear();
        expression_list_.append(ui_->digit_input_display->text());
        ui_->main_display->setText(ui_->digit_input_display->text());
        ui_->digit_input_display->clear();
        ResetEqFlag();
      }
      ResetEqFlag();
      if (!(ui_->digit_input_display->text().isEmpty())) {
        expression_list_.append(ui_->digit_input_display->text());
        ui_->main_display->setText(ui_->main_display->text() +
                                   ui_->digit_input_display->text());
        ui_->digit_input_display->clear();
      }

      if (current_action_ == "+") {
        ActionIsPlus();
      } else if (IsPrefix(current_action_)) {
        ActionIsPrefix();
      } else if (current_action_ == "x") {
        ActionIsX();
      } else if (current_action_ == ")") {
        ActionIsRigntBracket();
      } else {
        ActionIsSimple();
      }
    }
  } else {
    ClearClicked();
  }
}

bool SmartCalc::DigitOk() {
  if (!ui_->digit_input_display->text().isEmpty()) {
    if (ui_->digit_input_display->text().endsWith('.')) {
      ui_->digit_input_display->setText(ui_->digit_input_display->text() + '0');
    }

    return !ui_->digit_input_display->text().endsWith('E') &&
           !ui_->digit_input_display->text().endsWith('-');
  } else {
    return true;
  }
}

void SmartCalc::ResetEqFlag() {
  if (eq_flag_) {
    eq_flag_ = 0;
  }
}

void SmartCalc::ActionIsPlus() {
  main_display_temp_string_ = ui_->main_display->text();
  if (!expression_list_.endsWith("#")) {
    if (EndsWithDigit(main_display_temp_string_) ||
        EndsWithX(main_display_temp_string_) ||
        EndsWithRightBracket(main_display_temp_string_)) {
      AppendString(current_action_);
    } else if (ui_->main_display->text().isEmpty() ||
               EndsWithPrefix(ui_->main_display->text()) ||
               (EndsWithAriphmetic(main_display_temp_string_))) {
      AppendString("#");
    }
  }
}

void SmartCalc::ActionIsPrefix() {
  main_display_temp_string_ = ui_->main_display->text();
  if (EndsWithAriphmetic(main_display_temp_string_) ||
      EndsWithPrefix(main_display_temp_string_) ||
      main_display_temp_string_.isEmpty()) {
    left_bracket_++;
    AppendString(current_action_);
  }
}

void SmartCalc::ActionIsX() {
  main_display_temp_string_ = ui_->main_display->text();
  if (EndsWithAriphmetic(main_display_temp_string_) ||
      EndsWithPrefix(main_display_temp_string_) ||
      main_display_temp_string_.isEmpty()) {
    AppendString(current_action_);
  }
}

void SmartCalc::ActionIsRigntBracket() {
  main_display_temp_string_ = ui_->main_display->text();
  if (left_bracket_ >= right_bracket_ + 1) {
    if (!EndsWithAriphmetic(main_display_temp_string_) &&
        !EndsWithPrefix(main_display_temp_string_)) {
      right_bracket_++;
      AppendString(current_action_);
    }
  }
}

void SmartCalc::ActionIsSimple() {
  main_display_temp_string_ = ui_->main_display->text();
  if (!ui_->main_display->text().isEmpty()) {
    if (!EndsWithAriphmetic(main_display_temp_string_) &&
        !EndsWithPrefix(main_display_temp_string_)) {
      AppendString(current_action_);
    }
  }
}

void SmartCalc::AppendString(const QString &new_item) {
  expression_list_.append(new_item);
  if (new_item == "#") {
    ui_->main_display->setText(ui_->main_display->text() + "+");
  } else {
    ui_->main_display->setText(ui_->main_display->text() + new_item);
  }
  ui_->digit_input_display->clear();
}

bool SmartCalc::IsPrefix(const QString &check_action) {
  return (check_action == "(" || check_action == "sin(" ||
          check_action == "cos(" || check_action == "tan(" ||
          check_action == "asin(" || check_action == "acos(" ||
          check_action == "atan(" || check_action == "ln(" ||
          check_action == "log(" || check_action == "sqrt(");
}

bool SmartCalc::EndsWithPrefix(const QString &check_string) {
  return (check_string.endsWith("(") || check_string.endsWith("sin(") ||
          check_string.endsWith("cos(") || check_string.endsWith("tan(") ||
          check_string.endsWith("asin(") || check_string.endsWith("acos(") ||
          check_string.endsWith("atan(") || check_string.endsWith("ln(") ||
          check_string.endsWith("log(") || check_string.endsWith("sqrt("));
}

bool SmartCalc::EndsWithDigit(const QString &check_string) {
  return (check_string.endsWith('0') || check_string.endsWith('1') ||
          check_string.endsWith('2') || check_string.endsWith('3') ||
          check_string.endsWith('4') || check_string.endsWith('5') ||
          check_string.endsWith('6') || check_string.endsWith('7') ||
          check_string.endsWith('8') || check_string.endsWith('9'));
}

bool SmartCalc::EndsWithAriphmetic(const QString &check_string) {
  return (check_string.endsWith('+') || check_string.endsWith('-') ||
          check_string.endsWith('*') || check_string.endsWith('/') ||
          check_string.endsWith('%') || check_string.endsWith('^'));
}

bool SmartCalc::EndsWithRightBracket(const QString &check_string) {
  return (check_string.endsWith(')'));
}

bool SmartCalc::EndsWithX(const QString &check_string) {
  return (check_string.endsWith('x'));
}

void SmartCalc::EqualsClicked() {
  QString temp = ui_->main_display->text();
  static const int expression_max_size = 255;
  if (eq_flag_ == 0) {
    if (left_bracket_ == right_bracket_) {
      if (!ui_->main_display->text().isEmpty()) {
        if (!ui_->digit_input_display->text().isEmpty()) {
          if (DigitOk()) {
            ui_->main_display->setText(ui_->main_display->text() +
                                       ui_->digit_input_display->text());
            expression_list_.append(ui_->digit_input_display->text());
          }
          temp = ui_->main_display->text();
        }

        if (((EndsWithX(temp) || EndsWithRightBracket(temp) ||
              EndsWithDigit(temp)) &&
             (ui_->main_display->text().size() < expression_max_size))) {
          if (expression_list_.contains("x")) {
            ui_->digit_input_display->clear();
            choose_x_action_->show();
          } else {
            ui_string_.clear();
            for (int i = 0; i < expression_list_.size(); i++) {
              ui_string_ = ui_string_ + expression_list_[i] + " ";
            }
            ConvertString();
            expression_list_.append("=");
          }
          eq_flag_ = 1;
        } else {
          SetIncorrect();
        }
      }
    }
  }
}

void SmartCalc::SetIncorrect() {
  ui_->main_display->setText(ui_->main_display->text() +
                             ui_->digit_input_display->text());
  ui_->digit_input_display->setText("Incorrect expression.");
  ui_->main_display->clear();
}

void SmartCalc::DotClicked() {
  if (ui_->digit_input_display->text() != "Incorrect expression.") {
    if (!(ui_->digit_input_display->text().contains('.')) &&
        !(ui_->digit_input_display->text().contains('E'))) {
      if (ui_->digit_input_display->text().size()) {
        ui_->digit_input_display->setText(ui_->digit_input_display->text() +
                                          ".");
      } else {
        ui_->digit_input_display->setText(ui_->digit_input_display->text() +
                                          "0.");
      }
    }
  } else {
    ClearClicked();
  }
}

void SmartCalc::SignClicked() {
  QString sign_str = "-";
  QString sign_str_pars = "~";
  if (ui_->digit_input_display->text() != "Incorrect expression.") {
    QString number_to_string;
    if ((IsPrefix(current_action_) || current_action_ == "x") &&
        ui_->digit_input_display->text().isEmpty()) {
      QString temp_display = ui_->main_display->text();
      temp_display.replace(current_action_, (sign_str + current_action_));
      ui_->main_display->setText(temp_display);
      expression_list_.removeAt(expression_list_.size() - 1);
      expression_list_.append(sign_str_pars);
      expression_list_.append(current_action_);
    } else {
      if (!ui_->digit_input_display->text().isEmpty()) {
        double display_number = 0;
        display_number = (ui_->digit_input_display->text().toDouble());
        display_number = display_number * -1;
        number_to_string = QString::number(display_number, 'g', 12);
        ui_->digit_input_display->setText(number_to_string);
      }
    }
  } else {
    ClearClicked();
  }
}

void SmartCalc::ConvertString() {
  double result = 0;
  ui_string_.chop(1);
  std::string expression_string = ui_string_.toStdString();
  controller_ = new s21::Controller;
  result = controller_->s21::Controller::make_result(expression_string);
  QString result_to_string = QString::number(result, 'g', 12);
  ui_string_.replace("#", "");
  ui_string_.replace("~", "-");

  ui_->main_display->setText(ui_string_ + " = ");
  ui_->digit_input_display->setText(result_to_string);
}

void SmartCalc::DefineXSlot(const QString &x_string) {
  choose_x_action_->close();
  for (int i = 0; i < expression_list_.size(); i++) {
    if (expression_list_[i] == "x") {
      expression_list_[i] = x_string;
    }
  }
  ui_string_.clear();
  for (int i = 0; i < expression_list_.size(); i++) {
    ui_string_ = ui_string_ + expression_list_[i] + " ";
  }
  ConvertString();
}

void SmartCalc::MakeChartSlot() {
  choose_x_action_->close();
  chart_ = new Chart(nullptr, expression_list_);
  chart_->show();
  ClearClicked();
}

void SmartCalc::ClearClicked() {
  ui_->digit_input_display->clear();
  ui_->main_display->clear();
  expression_list_.clear();
  ui_string_.clear();
  left_bracket_ = 0;
  right_bracket_ = 0;
}

void SmartCalc::BackspaceClicked() {
  QString backsp_string = "";
  if (!ui_->main_display->text().contains('=')) {
    if (ui_->digit_input_display->text().size() ||
        ui_->main_display->text().size()) {
      if (ui_->digit_input_display->text().size()) {
        BackspaceDisplaysNotEmpty(&backsp_string);
      } else {
        BackspaceDisplaysEmpty(&backsp_string);
      }
    }
  }
}

void SmartCalc::BackspaceDisplaysNotEmpty(QString *backsp_string) {
  *backsp_string = ui_->digit_input_display->text();
  backsp_string->chop(1);
  ui_->digit_input_display->setText(*backsp_string);
}

void SmartCalc::BackspaceDisplaysEmpty(QString *backsp_string) {
  backsp_string->clear();
  *backsp_string = ui_->main_display->text();
  backsp_string->chop(1);
  if (backsp_string->size()) {
    if (backsp_string->endsWith(' ') || backsp_string->endsWith('=')) {
      backsp_string->chop(1);
    }
  }
  ui_->main_display->setText(*backsp_string);
  if (expression_list_.size()) {
    expression_list_.last().chop(1);
    if (!expression_list_.last().size()) {
      expression_list_.removeLast();
    }
  }
}

void SmartCalc::PushButtonCreditClicked() { credit_->show(); }

void SmartCalc::SetButtonsandSlots() {
  choose_x_action_ = new Form();
  credit_ = new Credit();

  connect(choose_x_action_, &Form::DefineXSignal, this,
          &SmartCalc::DefineXSlot);
  connect(choose_x_action_, &Form::MakeChartSignal, this,
          &SmartCalc::MakeChartSlot);

  connect(ui_->pushButton_0, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui_->pushButton_1, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui_->pushButton_2, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui_->pushButton_3, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui_->pushButton_4, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui_->pushButton_5, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui_->pushButton_6, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui_->pushButton_7, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui_->pushButton_8, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui_->pushButton_9, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui_->pushButton_E, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui_->pushButton_Em, SIGNAL(clicked()), this, SLOT(Digits()));
  connect(ui_->pushButton_dot, SIGNAL(clicked()), this, SLOT(DotClicked()));
  connect(ui_->pushButton_sign, SIGNAL(clicked()), this, SLOT(SignClicked()));
  connect(ui_->pushButton_add, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_sub, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_div, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_mult, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_mod, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_pow, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_l_br, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_r_br, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_sin, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_cos, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_tan, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_asin, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_acos, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_atan, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_ln, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_log, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_clear, SIGNAL(clicked()), this, SLOT(ClearClicked()));
  connect(ui_->pushButton_backspace, SIGNAL(clicked()), this,
          SLOT(BackspaceClicked()));
  connect(ui_->pushButton_eq, SIGNAL(clicked()), this, SLOT(EqualsClicked()));
  connect(ui_->pushButton_x, SIGNAL(clicked()), this, SLOT(ActionClicked()));
  connect(ui_->pushButton_credit, SIGNAL(clicked()), this,
          SLOT(PushButtonCreditClicked()));
}
