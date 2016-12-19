#-------------------------------------------------
#
# Project created by QtCreator 2016-12-19T10:27:12
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RSSClient
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
    AddFeedDialog.cpp \
    JsonParser.cpp \
    FeedModel.cpp \
    RssModel.cpp

HEADERS  += MainWindow.h \
    AddFeedDialog.h \
    JsonParser.h \
    FeedModel.h \
    RssModel.h

FORMS    += MainWindow.ui \
    AddFeedDialog.ui

RESOURCES += \
    resourse.qrc
