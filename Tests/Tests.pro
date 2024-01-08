HEADERS += \
    ../Core/Image/Image.h \
    CoreImageTests.h

SOURCES += \
    ../Core/Image/Image.cpp \
    main.cpp

QT = core gui widgets openglwidgets opengl network

IMAGEEDITOR_PATH = ../
IMAGE_EDITOR_THIRDPARTY = /Users/nshcherbakova/Documents/dev/Thirdparty

INCLUDEPATH +=$$IMAGE_EDITOR_THIRDPARTY/googletest/googletest/include/ \
    $$IMAGEEDITOR_PATH/Core/Gears/StdAfx/ \
    $$IMAGEEDITOR_PATH \
    $$IMAGE_EDITOR_THIRDPARTY/uniassert/include/ \
    $$IMAGE_EDITOR_THIRDPARTY/Boost/ \
    $$IMAGE_EDITOR_THIRDPARTY/spdlog/include/

LIBS += $$IMAGE_EDITOR_THIRDPARTY/googletest/build/lib/lib*.a
unix:QMAKE_CXXFLAGS += -std=c++17

