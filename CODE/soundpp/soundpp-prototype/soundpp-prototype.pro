QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databaseconnection.cpp \
    displayplaylistmodel.cpp \
    main.cpp \
    metadatareader.cpp \
    modeldatamanagement.cpp \
    modeldisplayalbums.cpp \
    modeldisplayartists.cpp \
    modeldisplaysongs.cpp \
    modelhistorylistl.cpp \
    modelqueuelist.cpp \
    modelsong.cpp \
    musikplayerqt.cpp \
    playlistdialog.cpp \
    soundppmanagement.cpp \
    uieditsongdialog.cpp \
    uimainwindow.cpp

HEADERS += \
    databaseconnection.h \
    displayplaylistmodel.h \
    metadatareader.h \
    modeldatamanagement.h \
    modeldisplayalbums.h \
    modeldisplayartists.h \
    modeldisplaysongs.h \
    modelhistorylistl.h \
    modelqueuelist.h \
    modelsong.h \
    musikplayerqt.h \
    playlistdialog.h \
    soundppmanagement.h \
    uieditsongdialog.h \
    uimainwindow.h

FORMS += \
    editsongdialog.ui \
    mainwindow.ui \
    playlistdialog.ui

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
