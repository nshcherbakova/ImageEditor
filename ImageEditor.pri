HEADERS += ./UI/QtConverts.h \
    $$PWD/Modules/Network/INetwork.h \
    $$PWD/Modules/Network/Network.h \
    $$PWD/Modules/Network/NetworkModule.h \
    ./UI/types.h \
    ./UI/UIString.h \
    ./UI/MainWindow.h \
    ./UI/Widgets/IWidget.h \
    ./UI/Widgets/WidgetsModule.h \
    ./UI/Widgets/MenuDialog.h \
    ./UI/Widgets/FiltersWidget.h \
    ./Core/types.h \
    ./Core/Gears/Asserts.h \
    ./Core/Gears/Injector.h \
    ./Core/Gears/StdAfx/stdafx.h \
    ./Core/Filters/FilterBase.h \
    ./Core/Filters/SepiaFilter.h \
    ./Core/Filters/SmoothFilter.h \
    ./Core/Filters/GrayFilter.h \
    ./Core/Filters/TessFilter.h \
    ./Core/Filters/WatercolorFilter.h \
    ./Core/Filters/IFilter.h \
    ./Core/Filters/FiltersModule.h \
    ./Core/Filters/OpenGL/OpenGLFilterBase.h \
    ./Core/Filters/OpenGL/OpenGLGrayFilter.h \
    ./Core/Filters/OpenGL/OpenGLBlurFilter.h \
    ./Core/Filters/OpenGL/OpenGLDropsFilter.h \
    ./Core/Filters/OpenGL/OpenGLWatercolorFilter.h \
    ./Core/Filters/OpenGL/OpenGLTessFilter.h \
    ./Core/Filters/OpenGL/OpenGLSepiaFilter.h \
    ./Core/Image/Image.h \
    ./Core/Image/IImage.h \
    ./Core/Image/ImageModule.h \
    ./Modules/types.h \
    ./Modules/Frames/FiltersFrame.h \
    ./Modules/Frames/IControl.h \
    ./Modules/Frames/IFrame.h \
    ./Modules/Frames/FramesModule.h \
    ./Modules/Frames/Tags.h \
    ./Modules/EditableImage/EditableImage.h \
    ./Modules/EditableImage/IEditableImage.h \
    ./Modules/EditableImage/EditableImageModule.h
SOURCES += ./UI/QtConverts.cpp \
    $$PWD/Modules/Network/Network.cpp \
    $$PWD/Modules/Network/NetworkModule.cpp \
    ./UI/MainWindow.cpp \
    ./UI/main.cpp \
    ./UI/Widgets/FiltersWidget.cpp \
    ./UI/Widgets/MenuDialog.cpp \
    ./UI/Widgets/WidgetsModule.cpp \
    ./Core/Gears/StdAfx/stdafx.cpp \
    ./Core/Filters/FilterBase.cpp \
    ./Core/Filters/FiltersModule.cpp \
    ./Core/Filters/SepiaFilter.cpp \
    ./Core/Filters/SmoothFilter.cpp \
    ./Core/Filters/GrayFilter.cpp \
    ./Core/Filters/TessFilter.cpp \
    ./Core/Filters/WatercolorFilter.cpp \
    ./Core/Filters/OpenGL/OpenGLFilterBase.cpp \
    ./Core/Filters/OpenGL/OpenGLGrayFilter.cpp \
    ./Core/Filters/OpenGL/OpenGLBlurFilter.cpp \
    ./Core/Filters/OpenGL/OpenGLDropsFilter.cpp \
    ./Core/Filters/OpenGL/OpenGLWatercolorFilter.cpp \
    ./Core/Filters/OpenGL/OpenGLTessFilter.cpp \
    ./Core/Filters/OpenGL/OpenGLSepiaFilter.cpp \
    ./Core/Image/ImageModule.cpp \
    ./Core/Image/Image.cpp \
    ./Modules/Frames/FramesModule.cpp \
    ./Modules/Frames/FiltersFrame.cpp \
    ./Modules/EditableImage/EditableImageModule.cpp \
    ./Modules/EditableImage/EditableImage.cpp
FORMS += ./UI/ImageEditor.ui
RESOURCES += UI/ImageEditor.qrc
