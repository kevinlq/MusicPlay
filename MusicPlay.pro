#-------------------------------------------------
#
# Project created by QtCreator 2016-03-11T12:18:07
#
#-------------------------------------------------
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MusicPlayV2
TEMPLATE = app


include($$PWD/src/application/MusicApplication.pri)
include($$PWD/src/ui/Music_ui.pri)
include($$PWD/src/helper/helper.pri)
#include($$PWD/src/musicControl/musicControl.pri)

INCLUDEPATH +=$$PWD/src/application
INCLUDEPATH +=$$PWD/src/ui
INCLUDEPATH +=$$PWD/src/ui/BottomBar
INCLUDEPATH +=$$PWD/src/ui/ContentWidget
INCLUDEPATH +=$$PWD/src/ui/TitleBar
INCLUDEPATH +=$$PWD/src/ui/DesktopLrc
INCLUDEPATH +=$$PWD/vlc/include
INCLUDEPATH +=$$PWD/src/helper
#INCLUDEPATH +=$$PWD/src/musicControl

#针对不同平台加载不同的动态库
win32 {
LIBS += -lws2_32
LIBS += $$PWD/vlc/lib/libvlc.dll
LIBS += $$PWD/vlc/lib/libvlccore.dll
}

unix{
LIBS    += -ldl
LIBS    += $$PWD/vlc/lib/libvlc.so
}

#对中间文件和生成文件进行分类管理
MOC_DIR       = temp/moc
RCC_DIR       = temp/rcc
UI_DIR        = temp/ui
OBJECTS_DIR   = temp/obj
DESTDIR       = bin

RESOURCES += \
    image.qrc

#可执行程序图标
RC_FILE = main.rc
