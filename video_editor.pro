QT += qml quick widgets

CONFIG += c++17

INCLUDEPATH += /usr/include/opencv
LIBS += `pkg-config --cflags --libs opencv`

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
        include/overlaybase.h \
        include/overlayfactory.h \
        include/overlaynumber.h \
        include/overlayrect.h \
        include/overlayslider.h \
        include/videomodel.h \
        include/videothread.h

SOURCES += \
        src/main.cpp \
        src/overlaybase.cpp \
        src/overlayfactory.cpp \
        src/overlaynumber.cpp \
        src/overlayrect.cpp \
        src/overlayslider.cpp \
        src/videomodel.cpp \
        src/videothread.cpp

RESOURCES += qml/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
