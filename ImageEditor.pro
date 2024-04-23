TEMPLATE = app
TARGET = ImageEditor
DESTDIR = ./x64/Debug
CONFIG += debug
QT = core gui widgets openglwidgets opengl network svg
android {
   QT += core-private
}
IMAGEEDITOR_PATH = $$PWD

target.path = $$IMAGEEDITOR_PATH
INSTALLS += target

IMAGE_EDITOR_THIRDPARTY = /Users/nshcherbakova/Documents/dev/Thirdparty

INCLUDEPATH +=$$IMAGEEDITOR_PATH/Core/Gears/StdAfx/ \
    $$IMAGEEDITOR_PATH \
    $$IMAGE_EDITOR_THIRDPARTY/uniassert/include/ \
    $$IMAGE_EDITOR_THIRDPARTY/Boost/ \
    $$IMAGE_EDITOR_THIRDPARTY/spdlog/include/

LIBS += -L"."
PRECOMPILED_HEADER = Core/Gears/StdAfx/stdafx.h
DEPENDPATH += .
MOC_DIR += .
OBJECTS_DIR += debug
UI_DIR += .
RCC_DIR += .
win32:QMAKE_CXXFLAGS += /std:c++17
unix:QMAKE_CXXFLAGS += -std=c++17

DEFINES += IMAGE_EDITOR_NO_UPLPAD

android {

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/res/xml/filepaths.xml \
    android/src/org/nshcherbakova/activity/QShareActivity.java \
    android/src/org/nshcherbakova/utils/QSharePathResolver.java \
    android/src/org/nshcherbakova/utils/QShareUtils.java
}

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

contains(ANDROID_TARGET_ARCH,x86_64) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

include(ImageEditor.pri)

!android {
HEADERS -= $$IMAGEEDITOR_PATH/Core/shareutils/AndroidShareUtils.h
SOURCES -= $$IMAGEEDITOR_PATH/Core/shareutils/AndroidShareUtils.cpp
}
