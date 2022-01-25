QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databaseconnection.cpp \
    datamanagement.cpp \
    main.cpp \
    mainwindow.cpp \
    metadataitem.cpp \
    metadatareader.cpp \
    musikplayerqt.cpp \
    soundppmanagement.cpp

HEADERS += \
    databaseconnection.h \
    datamanagement.h \
    mainwindow.h \
    metadataitem.h \
    metadatareader.h \
    musikplayerqt.h \
    soundppmanagement.h

FORMS += \
    mainwindow.ui

#taglib library funktioniert mit dem minGW 64 compiler
LIBS += -L$$PWD/libs/taglib/bin -ltag
INCLUDEPATH += $$PWD/libs/taglib/include
DEPENDPATH += $$PWD/libs/taglib/include/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
