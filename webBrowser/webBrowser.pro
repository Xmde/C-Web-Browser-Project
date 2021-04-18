QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++99
#windows
#LIBS += -lwsock32 -lws2_32
#linux
LIBS += -LL"$$_PRO_FILE_PWD_/../libraries" -lssl -lcrypto

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    filedownloader.cpp \
    htmldata.cpp \
    main.cpp \
    mainwindow.cpp \
    parser.cpp \
    renderer.cpp

HEADERS += \
    filedownloader.h \
    htmldata.h \
    httplib.h \
    mainwindow.h \
    parser.h \
    renderer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ca-bundle.crt \
    webBrowser.pro.user

SUBDIRS += \
