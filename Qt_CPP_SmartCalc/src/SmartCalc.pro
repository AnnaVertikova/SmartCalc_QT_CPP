QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QMAKE_LFLAGS +=

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/model.cpp \
    View/chart.cpp \
    View/credit.cpp \
    View/form.cpp \
    View/main.cpp \
    View/paymentschedule.cpp \
    View/smartcalc.cpp


HEADERS += \
    Controller/controller.h \
    Model/model.h \
    View/chart.h \
    View/credit.h \
    View/form.h \
    View/paymentschedule.h \
    View/smartcalc.h



FORMS += \
    View/chart.ui \
    View/credit.ui \
    View/form.ui \
    View/paymentschedule.ui \
    View/smartcalc.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
