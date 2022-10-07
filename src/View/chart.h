#ifndef SRC_VIEW_CHART_H_
#define SRC_VIEW_CHART_H_

#include <QObject>
#include <QStringList>
#include <QWidget>
#include <QtCharts>
#include <QtCharts/QCategoryAxis>
#include <QScatterSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <cstdlib>
#include <string>

#include "Controller/controller.h"

QT_USE_NAMESPACE

namespace Ui {

class Chart;
}

class Chart : public QWidget {
  Q_OBJECT

 public:
  explicit Chart(QWidget *parent, QStringList elements);
  ~Chart();


 private slots:
  void PushButtonRebuildClicked();

 private:
  Ui::Chart *ui;
  QChart *make_chart_;
  s21::Controller *chart_controller_;
  QScatterSeries *series_;
  QChartView *chart_view_;
  QValueAxis *axisX_;
  QValueAxis *axisY_;
  QStringList local_elements_;



 private:
  void ConvertStringForChart(std::map<double, double> *points, std::map<double, std::string> *x_expressions);
  void MakeXExpressionMap(std::map<double, std::string> *x_expressions);
  void MakePointsMap(std::map<double, double> *points);
  void BuildChart();
};

#endif  // SRC_VIEW_CHART_H_
