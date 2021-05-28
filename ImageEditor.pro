TEMPLATE = app
TARGET = ImageEditor
DESTDIR = ./x64/Debug
CONFIG += debug
QT = core gui widgets androidextras
IMAGEEDITOR_PATH = $$PWD

target.path = $$IMAGEEDITOR_PATH
INSTALLS += target

INCLUDEPATH +=$$IMAGEEDITOR_PATH/Core/Gears/StdAfx/ \
    $$IMAGEEDITOR_PATH \
    $$(IMAGE_EDITOR_THIRDPARTY)/uniassert/include/ \
    $$(IMAGE_EDITOR_THIRDPARTY)/Boost/
LIBS += -L"."
PRECOMPILED_HEADER = Core/Gears/StdAfx/stdafx.h
DEPENDPATH += .
MOC_DIR += .
OBJECTS_DIR += debug
UI_DIR += .
RCC_DIR += .
win32:QMAKE_CXXFLAGS += /std:c++17
unix:QMAKE_CXXFLAGS += -std=c++17
ANDROID_ABIS = armeabi-v7a
include(ImageEditor.pri)


