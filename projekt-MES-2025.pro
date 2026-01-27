QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/GaussTable.cpp \
    src/grid.cpp \
    src/functions.cpp \
    src/readFromFile.cpp \
    src/simulation.cpp

HEADERS += \
    include/config.h \
    include/mainwindow.h \
    include/GaussTable.h \
    include/grid.h \
    include/functions.h \
    include/readFromFile.h \
    include/simulation.h

FORMS += \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
