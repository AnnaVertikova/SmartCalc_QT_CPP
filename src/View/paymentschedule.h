#ifndef SRC_VIEW_PAYMENTSCHEDULE_H_
#define SRC_VIEW_PAYMENTSCHEDULE_H_

#include <QWidget>

namespace Ui {
class PaymentSchedule;
}
class Credit;

class PaymentSchedule : public QWidget {
  Q_OBJECT

 public:
  explicit PaymentSchedule(QWidget *parent = nullptr);
  ~PaymentSchedule();

 private:
  Ui::PaymentSchedule *ui;

  friend class Credit;
};

#endif  // SRC_VIEW_PAYMENTSCHEDULE_H_
