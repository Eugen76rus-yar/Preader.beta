#-------------------------------------------------
#
# Project created by QtCreator 2020-01-22T18:47:31
#
#-------------------------------------------------

QT       += core gui androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled23
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    autocomplite.cpp \
    file_dialog_android.cpp \
    setting_widget.cpp \
    save_ass.cpp

HEADERS += \
        mainwindow.h \
    autocomplite.h \
    file_dialog_android.h \
    setting_widget.h \
    save_ass.h

FORMS += \
        mainwindow.ui \
    file_dialog_android.ui \
    setting_widget.ui \
    save_ass.ui

CONFIG += mobility
MOBILITY = 


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/assets/filebaza.txt \
    android/assets/Setting.png

RESOURCES += \
    words_base_autocomplite.qrc



ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

android
{
my_files.path = /assets
my_files.files = $$PWD/assets/*
INSTALLS += my_files
}
