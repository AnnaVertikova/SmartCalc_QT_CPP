#include "chart.h"

#include "ui_chart.h"

Chart::Chart(QWidget *parent, QStringList elements)
    : QWidget(parent), ui(new Ui::Chart) {
  ui->setupUi(this);
  connect(ui->pushButton_rebuild, SIGNAL(clicked()), this,
          SLOT(PushButtonRebuildClicked()));
  local_elements_ = elements;
  BuildChart();
}

Chart::~Chart() { delete ui; }

void Chart::ConvertStringForChart(
    std::map<double, double> *points,
    std::map<double, std::string> *x_expressions) {
    chart_controller_ = new s21::Controller;
  *points = chart_controller_->s21::Controller::make_map_for_chart(x_expressions);
}

void Chart::MakeXExpressionMap(std::map<double, std::string> *x_expressions) {
  QString temp_string_for_chart_;
  double minX = ui->setMinX->value();
  double maxX = ui->setMaxX->value();
  x_expressions->clear();

  QStringList local_x_elements = local_elements_;
  if (minX != 0 || maxX != 0) {
    double h = 0.0005 * (abs(minX) + abs(maxX));

    for (double x = minX; x <= maxX; x += h) {
      local_elements_ = local_x_elements;
      for (int i = 0; i < local_elements_.size(); i++) {
        if (local_elements_[i] == "x") {
          if (i != 0 && local_elements_[i - 1] == "~") {
            local_elements_.removeAt(i - 1);
            --i;
            local_elements_[i] = QString::number(0 - x, 'g', 7);
          } else if (i != 0 && local_elements_[i - 1] == "#") {
            local_elements_.removeAt(i - 1);
            --i;
            local_elements_[i] = QString::number(x, 'g', 7);
          } else {
            local_elements_[i] = QString::number(x, 'g', 7);
          }
        }
      }

      temp_string_for_chart_.clear();
      for (int i = 0; i < local_elements_.size(); i++) {
        temp_string_for_chart_ =
            temp_string_for_chart_ + local_elements_[i] + " ";
      }
      temp_string_for_chart_.chop(1);
      x_expressions->insert(
          std::make_pair(x, temp_string_for_chart_.toStdString()));
    }
    local_elements_ = local_x_elements;
  }
}

void Chart::MakePointsMap(std::map<double, double> *points) {
  std::map<double, double>::iterator it = points->begin();
  while (it != points->end()) {
    if (it->second == it->second) {  // check for NaN
      series_->append(it->first, it->second);
    }
    ++it;
  }
}

void Chart::BuildChart() {
  make_chart_ = new QChart;
  series_ = new QScatterSeries;
  series_->setMarkerSize(2);
  series_->setPen(QPen(Qt::NoPen));

  std::map<double, double> points;
  std::map<double, std::string> x_expressions;

  MakeXExpressionMap(&x_expressions);
  ConvertStringForChart(&points, &x_expressions);
  MakePointsMap(&points);

  make_chart_->addSeries(series_);
  make_chart_->legend()->hide();
  make_chart_->setAnimationOptions(QChart::AllAnimations);

  axisX_ = new QValueAxis;
  axisX_->setMin(ui->setMinX->value());
  axisX_->setMax(ui->setMaxX->value());
  make_chart_->addAxis(axisX_, Qt::AlignBottom);

  axisY_ = new QValueAxis;
  axisY_->setMin(ui->setMinY->value());
  axisY_->setMax(ui->setMaxY->value());
  make_chart_->addAxis(axisY_, Qt::AlignLeft);

  ui->chart_display->setRenderHint(QPainter::Antialiasing);
  series_->attachAxis(axisX_);
  series_->attachAxis(axisY_);
  ui->chart_display->setChart(make_chart_);
}

void Chart::PushButtonRebuildClicked() { BuildChart(); }
