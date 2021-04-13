QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++99
#QMAKE_CXXFLAGS += -lwsock32 -lws2_32
#QMAKE_LFLAGS += -lwsock32 -lws2_32
#LIBS += -lwsock32 -lws2_32
LIBS += -LL"$$_PRO_FILE_PWD_/../libraries" -lssl -lcrypto

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    htmldata.cpp \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    Parser.h \
    htmldata.h \
    httplib.h \
    mainwindow.h \

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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/openssl/ -lcrypto

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/openssl/ -lssl

INCLUDEPATH += $$PWD/openssl/include
DEPENDPATH += $$PWD/openssl/include

#windows is hell
win32: LIBS += -lWldap32
win32: LIBS += -lCrypt32
win32: LIBS += -lWs2_32
