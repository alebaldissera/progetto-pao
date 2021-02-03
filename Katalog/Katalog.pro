QT       += core gui multimedia xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Catalogo.cpp \
    BaseNode.cpp \
    Controller.cpp \
    DeselectableTreeView.cpp \
    Directory.cpp \
    IOManager.cpp \
    LoadingView.cpp \
    MainWindow.cpp \
    Photo.cpp \
    Audio.cpp \
    Video.cpp \
    main.cpp

HEADERS += \
    Controller.h \
    DeepPtr.h \
    DeselectableTreeView.h \
    IOManager.h \
    LoadingView.h \
    MainWindow.h \
    Vector.h \
    Catalogo.h \
    BaseNode.h \
    Directory.h \
    Photo.h \
    Audio.h \
    Video.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Resources/Resources.qrc
