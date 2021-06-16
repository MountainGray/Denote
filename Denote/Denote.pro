QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Framework/ToolMenus/erasermenu.cpp \
    Framework/ToolMenus/penmenu.cpp \
    Framework/ToolMenus/toolmenu.cpp \
    Framework/ToolMenus/toolmenuviewer.cpp \
    Framework/document.cpp \
    Framework/documentgraphics.cpp \
    Framework/documentview.cpp \
    Framework/drawevent.cpp \
    Framework/subwindow.cpp \
    Tools/eraser.cpp \
    Tools/pressurepoint.cpp \
    Tools/pen.cpp \
    Tools/stroke.cpp \
    Tools/tool.cpp \
    main.cpp \
    mainwindow.cpp \
    Graphics/page.cpp \
    Graphics/pagebackground.cpp \
    Ui/ui.cpp

HEADERS += \
    Framework/ToolMenus/erasermenu.h \
    Framework/ToolMenus/penmenu.h \
    Framework/ToolMenus/toolmenu.h \
    Framework/ToolMenus/toolmenuviewer.h \
    Framework/document.h \
    Framework/documentgraphics.h \
    Framework/documentview.h \
    Framework//subwindow.h \
    Framework/drawevent.h \
    Tools/eraser.h \
    Tools/pressurepoint.h \
    Tools/pen.h \
    Tools/stroke.h \
    Tools/tool.h \
    mainwindow.h \
    Graphics/page.h \
    Graphics/pagebackground.h \
    Ui/ui.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
