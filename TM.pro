QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwidget.cpp \
    mainwindow.cpp \
    optioneditbox.cpp \
    prograsslist.cpp \
    prograssnode.cpp \
    stopwatch.cpp

HEADERS += \
    mainwidget.h \
    mainwindow.h \
    optioneditbox.h \
    prograsslist.h \
    prograssnode.h \
    stopwatch.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    TM_ko_KR.ts

LIBS += -lsapi -lOle32

QMAKE_CXXFLAGS += /utf-8

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
