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
ANDROID_VERSION_NAME = "1.0"

ANDROID_VERSION_CODE = "06413"


ANDROID_TARGET_SDK_VERSION = "33" 
ANDROID_MIN_SDK_VERSION = "26"

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

#include(ImageEditor.pri)

HEADERS += \
    Core/Filters/FilterBase.h \
    Core/Filters/FiltersModule.h \
    Core/Filters/GrayFilter.h \
    Core/Filters/IFilter.h \
    Core/Filters/OpenGL/OpenGLBlurFilter.h \
    Core/Filters/OpenGL/OpenGLDitheringFilter.h \
    Core/Filters/OpenGL/OpenGLDropsFilter.h \
    Core/Filters/OpenGL/OpenGLFilterBase.h \
    Core/Filters/OpenGL/OpenGLGrayFilter.h \
    Core/Filters/OpenGL/OpenGLSepiaFilter.h \
    Core/Filters/OpenGL/OpenGLTessFilter.h \
    Core/Filters/OpenGL/OpenGLWatercolorFilter.h \
    Core/Filters/OpenGL/platform/GLPlatform.h \
    Core/Filters/SepiaFilter.h \
    Core/Filters/SmoothFilter.h \
    Core/Filters/TessFilter.h \
    Core/Filters/WatercolorFilter.h \
    Core/Gears/Asserts.h \
    Core/Gears/Injector.h \
    Core/Image/IImage.h \
    Core/Image/Image.h \
    Core/Image/ImageModule.h \
    Core/shareutils/AndroidShareUtils.h \
    Core/shareutils/IPlatformShareUtils.h \
    Core/shareutils/ShareUtilsCpp.h \
    Core/shareutils/DummyShareUtils.h \
    Core/types.h \
    Modules/EditableImage/EditableImage.h \
    Modules/EditableImage/EditableImageModule.h \
    Modules/EditableImage/IEditableImage.h \
    Modules/Frames/FiltersFrame.h \
    Modules/Frames/FramesModule.h \
    Modules/Frames/IControl.h \
    Modules/Frames/IFrame.h \
    Modules/Frames/Tags.h \
    Modules/Network/INetwork.h \
    Modules/Network/Network.h \
    Modules/Network/NetworkModule.h \
    Modules/types.h \
    UI/MainWindow.h \
    UI/QtConverts.h \
    UI/UIString.h \
    UI/Widgets/Controls/ImageButton.h \
    UI/Widgets/Controls/RadioButton.h \
    UI/Widgets/FiltersScrollWidget.h \
    UI/Widgets/FiltersWidget.h \
    UI/Widgets/IWidget.h \
    UI/Widgets/MenuDialog.h \
    UI/Widgets/SplashScreen.h \
    UI/Widgets/UICommand.h \
    UI/Widgets/WidgetsModule.h \
    UI/types.h

SOURCES += \
    Core/Filters/FilterBase.cpp \
    Core/Filters/FiltersModule.cpp \
    Core/Filters/GrayFilter.cpp \
    Core/Filters/OpenGL/OpenGLBlurFilter.cpp \
    Core/Filters/OpenGL/OpenGLDitheringFilter.cpp \
    Core/Filters/OpenGL/OpenGLDropsFilter.cpp \
    Core/Filters/OpenGL/OpenGLFilterBase.cpp \
    Core/Filters/OpenGL/OpenGLGrayFilter.cpp \
    Core/Filters/OpenGL/OpenGLSepiaFilter.cpp \
    Core/Filters/OpenGL/OpenGLTessFilter.cpp \
    Core/Filters/OpenGL/OpenGLWatercolorFilter.cpp \
    Core/Filters/SepiaFilter.cpp \
    Core/Filters/SmoothFilter.cpp \
    Core/Filters/TessFilter.cpp \
    Core/Filters/WatercolorFilter.cpp \
    Core/Gears/StdAfx/stdafx.cpp \
    Core/Image/Image.cpp \
    Core/Image/ImageModule.cpp \
    Core/shareutils/AndroidShareUtils.cpp \
    Core/shareutils/ShareUtilsCpp.cpp \
    Modules/EditableImage/EditableImage.cpp \
    Modules/EditableImage/EditableImageModule.cpp \
    Modules/Frames/FiltersFrame.cpp \
    Modules/Frames/FramesModule.cpp \
    Modules/Network/Network.cpp \
    Modules/Network/NetworkModule.cpp \
    UI/MainWindow.cpp \
    UI/QtConverts.cpp \
    UI/Widgets/Controls/ImageButton.cpp \
    UI/Widgets/Controls/RadioButton.cpp \
    UI/Widgets/FiltersScrollWidget.cpp \
    UI/Widgets/FiltersWidget.cpp \
    UI/Widgets/MenuDialog.cpp \
    UI/Widgets/SplashScreen.cpp \
    UI/Widgets/UICommand.cpp \
    UI/Widgets/WidgetsModule.cpp \
    UI/main.cpp

!android {
HEADERS -= Core/shareutils/AndroidShareUtils.h
SOURCES -= Core/shareutils/AndroidShareUtils.cpp
}

RESOURCES += \
    UI/ImageEditor.qrc

FORMS += \
    UI/ImageEditor.ui

