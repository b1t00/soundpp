QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    artist.cpp \
    databaseconnection.cpp \
    display_artist_model.cpp \
    display_song_model.cpp \
    main.cpp \
    mainwindow.cpp \
    metadataitem.cpp \
    metadatareader.cpp \
    modeldatamanagement.cpp \
    modelsong.cpp \
    musikplayerqt.cpp \
    soundppmanagement.cpp

HEADERS += \
    artist.h \
    databaseconnection.h \
    display_artist_model.h \
    display_song_model.h \
    mainwindow.h \
    metadataitem.h \
    metadatareader.h \
    modeldatamanagement.h \
    modelsong.h \
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
