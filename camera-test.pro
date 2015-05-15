TARGET = camera-test

QT += multimedia

CONFIG += sailfishapp

SOURCES += \
    src/camerahelper.cpp \
    src/main.cpp

OTHER_FILES += \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    rpm/camera-test.spec \
    camera-test.desktop \
    qml/main.qml

HEADERS += \
    src/camerahelper.h
