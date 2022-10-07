#ifndef SRC_VIEW_FORM_H_
#define SRC_VIEW_FORM_H_

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget {
  Q_OBJECT

 public:
  explicit Form(QWidget *parent = nullptr);
  ~Form();

 private:
  Ui::Form *ui;

 private slots:
  void PushButtonOKClicked();

 signals:
  void DefineXSignal(QString x_string);
  void MakeChartSignal();
};

#endif  // SRC_VIEW_FORM_H_
