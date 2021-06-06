QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Framework/document.cpp \
    Framework/documentgraphics.cpp \
    Framework/documentview.cpp \
    main.cpp \
    mainwindow.cpp \
    Graphics/page.cpp \
    Graphics/pagebackground.cpp \
    Tools/pen.cpp \
    Tools/stroke.cpp \
    Framework/subwindow.cpp \
    Tools/tool.cpp \
    Ui/ui.cpp \
    test.cpp

HEADERS += \
    Framework/document.h \
    Framework/documentgraphics.h \
    Framework/documentview.h \
    mainwindow.h \
    Graphics/page.h \
    Graphics/pagebackground.h \
    Tools/pen.h \
    Tools/stroke.h \
    Framework//subwindow.h \
    Tools/tool.h \
    Ui/ui.h \
    test.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
