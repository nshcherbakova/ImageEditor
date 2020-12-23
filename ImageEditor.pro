TEMPLATE = app
TARGET = ImageEditor
DESTDIR = ./x64/Release
CONFIG += release
QT = core gui widgets
IMAGEEDITOR_PATH = $$PWD

INCLUDEPATH +=$$IMAGEEDITOR_PATH/Core/Gears/StdAfx/ \
    $$IMAGEEDITOR_PATH \
    $$(IMAGE_EDITOR_THIRDPARTY)/uniassert/include/ \
    $$(IMAGE_EDITOR_THIRDPARTY)/Boost/
LIBS += -L"."
PRECOMPILED_HEADER = Core/Gears/StdAfx/stdafx.h
DEPENDPATH += .
MOC_DIR += .
OBJECTS_DIR += release
UI_DIR += .
RCC_DIR += .
win32:QMAKE_CXXFLAGS += /std:c++17
unix:QMAKE_CXXFLAGS += -std=c++17
include(ImageEditor.pri)

ANDROID_ABIS = armeabi-v7a
