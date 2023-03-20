QT       += core gui
QT       += xml
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/adminpage.cpp \
    src/comboboxdelegate.cpp \
    src/database.cpp \
    src/menu.cpp \
    main.cpp \
    src/XLMParser.cpp \
    src/connexionpage.cpp \
    src/mainpage.cpp \
    src/mainwindow.cpp \
    src/profile.cpp \
    src/user.cpp


HEADERS += \
    headers/XMLParser.h \
    headers/adminpage.h \
    headers/comboboxdelegate.h \
    headers/connexionpage.h \
    headers/database.h \
    headers/mainpage.h \
    headers/mainwindow.h \
    headers/menu.h \
    headers/user.h \
    headers/profile.h

FORMS += \
    forms/adminpage.ui \
    forms/connexionpage.ui \
    forms/database.ui \
    forms/mainpage.ui \
    forms/mainwindow.ui \
    forms/profile.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
